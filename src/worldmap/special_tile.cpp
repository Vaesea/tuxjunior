//  $Id: special_tile.cpp 4063 2006-07-21 21:05:23Z anmaster $
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

#include "worldmap/special_tile.hpp"
#include "sprite/sprite_manager.hpp"
#include "sprite/sprite.hpp"
#include "video/drawing_context.hpp"

namespace WorldMapNS
{

SpecialTile::SpecialTile(const lisp::Lisp* lisp)
  : passive_message(false), invisible(false),
    apply_action_north(true), apply_action_east(true),
    apply_action_south(true), apply_action_west(true)
{
  lisp->get("x", pos.x);
  lisp->get("y", pos.y);
  lisp->get("invisible-tile", invisible);

  if(!invisible) {
    std::string spritefile = "";
    lisp->get("sprite", spritefile);
    sprite.reset(sprite_manager->create(spritefile));
  }

  lisp->get("map-message", map_message);
  lisp->get("passive-message", passive_message);
  lisp->get("script", script);

  std::string apply_direction;
  lisp->get("apply-to-direction", apply_direction);
  if(!apply_direction.empty()) {
    apply_action_north = false;
    apply_action_south = false;
    apply_action_east = false;
    apply_action_west = false;
    if(apply_direction.find("north") != std::string::npos)
      apply_action_north = true;
    if(apply_direction.find("south") != std::string::npos)
      apply_action_south = true;
    if(apply_direction.find("east") != std::string::npos)
      apply_action_east = true;
    if(apply_direction.find("west") != std::string::npos)
      apply_action_west = true;
  }
}

SpecialTile::~SpecialTile()
{
}

void
SpecialTile::draw(DrawingContext& context)
{
  if(invisible)
    return;

  sprite->draw(context, pos*32 + Vector(16, 16), LAYER_OBJECTS - 1);
}

void
SpecialTile::update(float )
{
}

}
