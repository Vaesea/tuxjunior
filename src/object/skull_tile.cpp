//  $Id: skull_tile.cpp 4114 2006-08-02 22:23:22Z matzebraun $
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

#include "skull_tile.hpp"
#include "lisp/lisp.hpp"
#include "object_factory.hpp"
#include "player.hpp"
#include "sector.hpp"
#include "resources.hpp"
#include "sprite/sprite.hpp"
#include "random_generator.hpp"

static const float CRACKTIME = 0.3;
static const float FALLTIME = 0.8;

SkullTile::SkullTile(const lisp::Lisp& lisp)
	: MovingSprite(lisp, "images/objects/skull_tile/skull_tile.sprite", LAYER_TILES, COLGROUP_STATIC), hit(false), falling(false)
{
}

HitResponse
SkullTile::collision(GameObject& other, const CollisionHit& )
{
  Player* player = dynamic_cast<Player*> (&other);
  if(player)
    hit = true;

  return FORCE_MOVE;
}

void
SkullTile::draw(DrawingContext& context)
{
  Vector pos = get_pos();
  // shacking
  if(timer.get_timegone() > CRACKTIME) {
    pos.x += systemRandom.rand(-3, 3);
  }

  sprite->draw(context, pos, layer);
}

void
SkullTile::update(float elapsed_time)
{
  if(falling) {
    movement = physic.get_movement(elapsed_time);
    if(!Sector::current()->inside(bbox)) {
      remove_me();
      return;
    }
  } else if(hit) {
    if(timer.check()) {
      falling = true;
      physic.enable_gravity(true);
      timer.stop();
    } else if(!timer.started()) {
      timer.start(FALLTIME);
    }
  } else {
    timer.stop();
  }
  hit = false;
}

IMPLEMENT_FACTORY(SkullTile, "skull_tile");
