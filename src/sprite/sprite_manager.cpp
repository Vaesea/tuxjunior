//  $Id: sprite_manager.cpp 4882 2007-02-28 18:16:37Z matzeb $
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
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#include <config.h>

#include <iostream>
#include <sstream>
#include <stdexcept>

#include "sprite_manager.hpp"
#include "sprite_data.hpp"
#include "sprite.hpp"
#include "lisp/lisp.hpp"
#include "lisp/parser.hpp"
#include "lisp/list_iterator.hpp"
#include "file_system.hpp"
#include "log.hpp"
#include <string>

SpriteManager* sprite_manager = NULL;

SpriteManager::SpriteManager()
{
}

SpriteManager::~SpriteManager()
{
  for(Sprites::iterator i = sprites.begin(); i != sprites.end(); ++i) {
    delete i->second;
  }
}

Sprite*
SpriteManager::create(const std::string& name)
{
  Sprites::iterator i = sprites.find(name);
  SpriteData* data;
  if(i == sprites.end()) {
    // try loading the spritefile
    data = load(name);
    if(data == NULL) {
      std::stringstream msg;
      msg << "Sprite '" << name << "' not found.";
      throw std::runtime_error(msg.str());
    }
  } else {
    data = i->second;
  }

  return new Sprite(*data);
}

SpriteData*
SpriteManager::load(const std::string& filename)
{
  lisp::Parser parser;
  const lisp::Lisp* root;

  try {
    root = parser.parse(filename);
  } catch(const std::exception& e) {
    std::ostringstream msg;
    msg << "Parse error when trying to load sprite '" << filename
        << "': " << e.what() << "\n";
    throw std::runtime_error(msg.str());
  }

  const lisp::Lisp* sprite = root->get_lisp("tuxjunior-sprite");
  if(!sprite) {
    std::ostringstream msg;
    msg << "'" << filename << "' is not a tuxjunior-sprite file";
    throw std::runtime_error(msg.str());
  }

  std::auto_ptr<SpriteData> data (
      new SpriteData(sprite, FileSystem::dirname(filename)) );
  sprites[filename] = data.release();

  return sprites[filename];
}
