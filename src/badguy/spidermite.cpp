//  $Id: spidermite.cpp 4661 2007-01-23 12:33:50Z matzeb $
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
#include <stdio.h>

#include "spidermite.hpp"

static const float FLYTIME = 1.2f;
static const float FLYSPEED = -100.0f;

SpiderMite::SpiderMite(const lisp::Lisp& reader)
	: BadGuy(reader, "images/creatures/spidermite/spidermite.sprite")
{
  physic.enable_gravity(false);
}

SpiderMite::SpiderMite(const Vector& pos)
	: BadGuy(pos, "images/creatures/spidermite/spidermite.sprite")
{
  physic.enable_gravity(false);
}

void
SpiderMite::write(lisp::Writer& writer)
{
  writer.start_list("spidermite");

  writer.write_float("x", start_position.x);
  writer.write_float("y", start_position.y);

  writer.end_list("spidermite");
}

void
SpiderMite::activate()
{
  sprite->set_action(dir == LEFT ? "left" : "right");
  mode = FLY_UP;
  physic.set_velocity_y(FLYSPEED);
  timer.start(FLYTIME/2);
}

bool
SpiderMite::collision_squished(GameObject& object)
{
  sprite->set_action(dir == LEFT ? "squished-left" : "squished-right");
  kill_squished(object);
  return true;
}

void
SpiderMite::collision_solid(const CollisionHit& hit)
{
  if(hit.top || hit.bottom) { // hit floor or roof?
    physic.set_velocity_y(0);
  }
}

void
SpiderMite::active_update(float elapsed_time)
{
  if(timer.check()) {
    if(mode == FLY_UP) {
      mode = FLY_DOWN;
      physic.set_velocity_y(-FLYSPEED);
    } else if(mode == FLY_DOWN) {
      mode = FLY_UP;
      physic.set_velocity_y(FLYSPEED);
    }
    timer.start(FLYTIME);
  }
  movement=physic.get_movement(elapsed_time);

  Player* player = this->get_nearest_player();
  if (player) {
    dir = (player->get_pos().x > get_pos().x) ? RIGHT : LEFT;
    sprite->set_action(dir == LEFT ? "left" : "right");
  }
}

IMPLEMENT_FACTORY(SpiderMite, "spidermite")
