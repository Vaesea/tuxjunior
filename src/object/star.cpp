//  $Id: star.cpp 4059 2006-07-21 11:45:14Z matzebraun $
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

#include "star.hpp"
#include "resources.hpp"
#include "player.hpp"
#include "player_status.hpp"
#include "sprite/sprite_manager.hpp"
#include "video/drawing_context.hpp"

static const float INITIALJUMP = -400;
static const float SPEED = 150;
static const float JUMPSPEED = -300;

Star::Star(const Vector& pos, Direction direction)
	: MovingSprite(pos, "images/powerups/star/star.sprite", LAYER_OBJECTS, COLGROUP_MOVING)
{
  physic.set_velocity((direction == LEFT) ? -SPEED : SPEED, INITIALJUMP);
}

void
Star::update(float elapsed_time)
{
  movement = physic.get_movement(elapsed_time);
}

void
Star::collision_solid(const CollisionHit& hit)
{
  if(hit.bottom) {
    physic.set_velocity_y(JUMPSPEED);
  } else if(hit.top) {
    physic.set_velocity_y(0);
  } else if(hit.left || hit.right) {
    physic.set_velocity_x(-physic.get_velocity_x());
  }
}

HitResponse
Star::collision(GameObject& other, const CollisionHit& )
{
  Player* player = dynamic_cast<Player*> (&other);
  if(player) {
    player->make_invincible();
    remove_me();
    return ABORT_MOVE;
  }

  return FORCE_MOVE;
}
