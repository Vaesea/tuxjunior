//  $Id: bouncing_snowball.cpp 4435 2006-11-04 14:13:27Z sommer $
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

#include "bouncing_snowball.hpp"

static const float JUMPSPEED = -450;
static const float WALKSPEED = 80;

BouncingSnowball::BouncingSnowball(const lisp::Lisp& reader)
	: BadGuy(reader, "images/creatures/bouncing_snowball/bouncing_snowball.sprite")
{
}

BouncingSnowball::BouncingSnowball(const Vector& pos, Direction d)
  : BadGuy(pos, d, "images/creatures/bouncing_snowball/bouncing_snowball.sprite")
{
}

void
BouncingSnowball::write(lisp::Writer& writer)
{
  writer.start_list("bouncingsnowball");

  writer.write_float("x", start_position.x);
  writer.write_float("y", start_position.y);

  writer.end_list("bouncingsnowball");
}

void
BouncingSnowball::activate()
{
  physic.set_velocity_x(dir == LEFT ? -WALKSPEED : WALKSPEED);
  sprite->set_action(dir == LEFT ? "left" : "right");
}

bool
BouncingSnowball::collision_squished(GameObject& object)
{
  sprite->set_action("squished");
  kill_squished(object);
  return true;
}

void
BouncingSnowball::collision_solid(const CollisionHit& hit)
{
  if(hit.bottom) {
    if(get_state() == STATE_ACTIVE) {
      physic.set_velocity_y(JUMPSPEED);
    } else {
      physic.set_velocity_y(0);
    }
  } else if(hit.top) {
    physic.set_velocity_y(0);
  }

  if(hit.left || hit.right) { // left or right collision
    dir = dir == LEFT ? RIGHT : LEFT;
    sprite->set_action(dir == LEFT ? "left" : "right");
    physic.set_velocity_x(-physic.get_velocity_x());
  }
}

HitResponse
BouncingSnowball::collision_badguy(BadGuy& , const CollisionHit& hit)
{
  collision_solid(hit);
  return CONTINUE;
}

IMPLEMENT_FACTORY(BouncingSnowball, "bouncingsnowball")
