//  $Id: sprite_change.cpp 4063 2006-07-21 21:05:23Z anmaster $
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

#include "sprite_change.hpp"
#include "sprite/sprite_manager.hpp"
#include "sprite/sprite.hpp"
#include "video/drawing_context.hpp"

namespace WorldMapNS
{

SpriteChange::SpriteChange(const lisp::Lisp* lisp)
  : change_on_touch(false), in_stay_action(false)
{
  lisp->get("x", pos.x);
  lisp->get("y", pos.y);
  lisp->get("change-on-touch", change_on_touch);

  std::string spritefile = "";
  lisp->get("sprite", spritefile);
  sprite.reset(sprite_manager->create(spritefile));

  lisp->get("stay-action", stay_action);
  lisp->get("initial-stay-action", in_stay_action);

  lisp->get("stay-group", stay_group);

  all_sprite_changes.push_back(this);
}

SpriteChange::~SpriteChange()
{
  all_sprite_changes.remove(this);
}

void
SpriteChange::draw(DrawingContext& context)
{
  if(in_stay_action && stay_action != "") {
    sprite->set_action(stay_action);
    sprite->draw(context, pos * 32, LAYER_OBJECTS-1);
  }
}

void
SpriteChange::update(float )
{
}

void
SpriteChange::set_stay_action()
{
  in_stay_action = true;
}

void
SpriteChange::clear_stay_action()
{
  in_stay_action = false;

  // if we are in a stay_group, also clear all stay actions in this group
  if (stay_group != "") {
    for (std::list<SpriteChange*>::iterator i = all_sprite_changes.begin(); i != all_sprite_changes.end(); i++) {
      SpriteChange* sc = *i;
      if (sc->stay_group != stay_group) continue;
      sc->in_stay_action = false;
    }
  }
}

std::list<SpriteChange*> SpriteChange::all_sprite_changes;

}
