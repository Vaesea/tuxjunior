//  $Id: level.cpp 4609 2007-01-20 11:04:53Z matzeb $
//
//  SuperTux
//  Copyright (C) 2004 Ingo Ruhnke <grumbel@gmx.de>
//  Copyright (C) 2006 Christoph Sommer <christoph.sommer@2006.expires.deltadevelopment.de>
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

#include <stddef.h>
#include <physfs.h>
#include "worldmap/level.hpp"
#include "sprite/sprite_manager.hpp"
#include "sprite/sprite.hpp"
#include "video/drawing_context.hpp"
#include "log.hpp"
#include "file_system.hpp"

namespace WorldMapNS
{

LevelTile::LevelTile(const std::string& basedir, const lisp::Lisp* lisp)
  : solved(false), auto_play(false), basedir(basedir), picture_cached(false),
    picture(0)
{
  lisp->get("name", name);
  lisp->get("x", pos.x);
  lisp->get("y", pos.y);
  lisp->get("auto-play", auto_play);

  std::string spritefile = "images/worldmap/common/leveldot.sprite";
  lisp->get("sprite", spritefile);
  sprite.reset(sprite_manager->create(spritefile));

  lisp->get("extro-script", extro_script);

  if (!PHYSFS_exists((basedir + name).c_str()))
  {
    log_warning << "level file '" << name
      << "' does not exist and will not be added to the worldmap" << std::endl;
    return;
  }
}

LevelTile::~LevelTile()
{
  delete picture;
}

void
LevelTile::draw(DrawingContext& context)
{
  sprite->draw(context, pos*32 + Vector(16, 16), LAYER_OBJECTS - 1);
}

void
LevelTile::update(float )
{
}

const Surface*
LevelTile::get_picture()
{
  if (picture_cached) return picture;
  picture_cached = true;
  std::string fname = FileSystem::strip_extension(basedir + name)+".jpg";
  if (!PHYSFS_exists(fname.c_str())) {
  	return 0;
  }
  picture = new Surface(fname);
  return picture;
}

}
