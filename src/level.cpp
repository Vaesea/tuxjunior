//  $Id: level.cpp 5265 2008-01-08 00:10:32Z matzeb $
//
//  SuperTux
//  Copyright (C) 2006 Matthias Braun <matze@braunis.de>
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
//  02111-1307, USA.
#include <config.h>

#include <map>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <stdexcept>

#include "log.hpp"
#include "lisp/parser.hpp"
#include "lisp/lisp.hpp"
#include "lisp/list_iterator.hpp"
#include "lisp/writer.hpp"
#include "level.hpp"
#include "physic.hpp"
#include "sector.hpp"
#include "tile.hpp"
#include "tile_set.hpp"
#include "tile_manager.hpp"
#include "resources.hpp"
#include "file_system.hpp"
#include "object/gameobjs.hpp"
#include "object/camera.hpp"
#include "object/tilemap.hpp"

#include "object/coin.hpp"
#include "object/block.hpp"

using namespace std;

Level::Level()
  : name("noname"), author("Mr. X"), tileset(NULL), free_tileset(false)
{
}

Level::~Level()
{
  for(Sectors::iterator i = sectors.begin(); i != sectors.end(); ++i)
    delete *i;
  if(free_tileset)
    delete tileset;
}

void
Level::load(const std::string& filepath)
{
  try {
    lisp::Parser parser;
    const lisp::Lisp* root = parser.parse(filepath);

    const lisp::Lisp* level = root->get_lisp("tuxjunior-level");
    if(!level)
      throw std::runtime_error("file is not a tuxjunior-level file.");

    int version = 1;
    level->get("version", version);
    if(version == 1) {
      load_old_format(*level);
      return;
    }

    const lisp::Lisp* tilesets_lisp = level->get_lisp("tilesets");
    if(tilesets_lisp != NULL) {
      tileset      = tile_manager->parse_tileset_definition(*tilesets_lisp);
      free_tileset = true;
    }
    std::string tileset_name;
    if(level->get("tileset", tileset_name)) {
      if(tileset != NULL) {
        log_warning << "multiple tilesets specified in level" << std::endl;
      } else {
        tileset = tile_manager->get_tileset(tileset_name);
      }
    }
    /* load default tileset */
    if(tileset == NULL) {
      tileset = tile_manager->get_tileset("images/tiles.strf");
    }
    current_tileset = tileset;

    contact = "";
    license = "";

    lisp::ListIterator iter(level);
    while(iter.next()) {
      const std::string& token = iter.item();
      if(token == "version") {
        iter.value()->get(version);
        if(version > 2) {
          log_warning << "level format newer than application" << std::endl;
        }
      } else if(token == "tileset" || token == "tilesets") {
        continue;
      } else if(token == "name") {
        iter.value()->get(name);
      } else if(token == "author") {
        iter.value()->get(author);
      } else if(token == "contact") {
        iter.value()->get(contact);
      } else if(token == "license") {
        iter.value()->get(license);
      } else if(token == "on-menukey-script") {
        iter.value()->get(on_menukey_script);
      } else if(token == "sector") {
        Sector* sector = new Sector(this);
        sector->parse(*(iter.lisp()));
        add_sector(sector);
      } else {
        log_warning << "Unknown token '" << token << "' in level file" << std::endl;
      }
    }

    if (license == "") {
      log_warning << "The level author did not specify a license for this level. You might not be allowed to share it." << std::endl;

    }
  } catch(std::exception& e) {
    std::stringstream msg;
    msg << "Problem when reading level '" << filepath << "': " << e.what();
    throw std::runtime_error(msg.str());
  }

  current_tileset = NULL;
}

void
Level::load_old_format(const lisp::Lisp& reader)
{
  reader.get("name", name);
  reader.get("author", author);

  Sector* sector = new Sector(this);
  sector->parse_old_format(reader);
  add_sector(sector);
}

void
Level::save(const std::string& filename)
{
  lisp::Writer* writer = new lisp::Writer(filename);

  writer->write_comment("Level made using TuxJunior's built-in Level Editor");

  writer->start_list("tuxjunior-level");

  int version = 2;
  writer->write_int("version", version);

  writer->write_string("name", name, true);
  writer->write_string("author", author);
  if(on_menukey_script != "")
    writer->write_string("on-menukey-script", on_menukey_script);

  for(Sectors::iterator i = sectors.begin(); i != sectors.end(); ++i) {
    Sector* sector = *i;
    writer->start_list("sector");
    sector->write(*writer);
    writer->end_list("sector");
  }

  writer->end_list("tuxjunior-level");

  delete writer;
}

void
Level::add_sector(Sector* sector)
{
  Sector* test = get_sector(sector->get_name());
  if(test != 0) {
    throw std::runtime_error("Trying to add 2 sectors with same name");
  }
  sectors.push_back(sector);
}

Sector*
Level::get_sector(const std::string& name)
{
  for(Sectors::iterator i = sectors.begin(); i != sectors.end(); ++i) {
    Sector* sector = *i;
    if(sector->get_name() == name)
      return sector;
  }

  return 0;
}

size_t
Level::get_sector_count()
{
  return sectors.size();
}

Sector*
Level::get_sector(size_t num)
{
  return sectors.at(num);
}

int
Level::get_total_coins()
{
  int total_coins = 0;
  for(Sectors::iterator i = sectors.begin(); i != sectors.end(); ++i) {
    Sector* sector = *i;
    for(Sector::GameObjects::iterator o = sector->gameobjects.begin();
        o != sector->gameobjects.end(); ++o) {
      Coin* coin = dynamic_cast<Coin*> (*o);
      if(coin)
      {
        total_coins++;
        continue;
      }
      BonusBlock *block = dynamic_cast<BonusBlock*> (*o);
      if(block)
      {
        if (block->contents == BonusBlock::CONTENT_COIN)
        {
          total_coins++;
          continue;
        }
#if 0
        // FIXME: do we want this? q.v. src/object/oneup.cpp
        else if (block->contents == BonusBlock::CONTENT_1UP)
        {
          total_coins += 100;
          continue;
        }
#endif
      }
    }
  }
  return total_coins;
}

int
Level::get_total_badguys()
{
  int total_badguys = 0;
  for(Sectors::iterator i = sectors.begin(); i != sectors.end(); ++i)
    total_badguys += (*i)->get_total_badguys();
  return total_badguys;
}
