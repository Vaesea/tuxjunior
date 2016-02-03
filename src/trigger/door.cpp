//  $Id: door.cpp 4059 2006-07-21 11:45:14Z matzebraun $
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

#include "door.hpp"
#include "game_session.hpp"
#include "resources.hpp"
#include "object_factory.hpp"
#include "sprite/sprite.hpp"
#include "sprite/sprite_manager.hpp"
#include "video/drawing_context.hpp"
#include "lisp/lisp.hpp"
#include "lisp/writer.hpp"
#include "audio/sound_manager.hpp"

Door::Door(const lisp::Lisp& reader)
	: state(CLOSED)
{
  reader.get("x", bbox.p1.x);
  reader.get("y", bbox.p1.y);
  reader.get("sector", target_sector);
  reader.get("spawnpoint", target_spawnpoint);

  sprite = sprite_manager->create("images/objects/door/door.sprite");
  sprite->set_action("closed");
  bbox.set_size(sprite->get_current_hitbox_width(), sprite->get_current_hitbox_height());
}

Door::Door(int x, int y, std::string sector, std::string spawnpoint)
	: state(CLOSED)
{
  bbox.set_pos(Vector(x, y));
  target_sector = sector;
  target_spawnpoint = spawnpoint;

  sprite = sprite_manager->create("images/objects/door/door.sprite");
  sprite->set_action("closed");
  bbox.set_size(sprite->get_current_hitbox_width(), sprite->get_current_hitbox_height());
}

Door::~Door()
{
  delete sprite;
}

void
Door::write(lisp::Writer& writer)
{
  writer.start_list("door");

  writer.write_float("x", bbox.p1.x);
  writer.write_float("y", bbox.p1.y);
  writer.write_float("width", bbox.get_width());
  writer.write_float("height", bbox.get_height());

  writer.write_string("sector", target_sector);
  writer.write_string("spawnpoint", target_spawnpoint);
  sound_manager->preload("sounds/door.wav");
  writer.end_list("door");
}

void
Door::update(float )
{
  switch (state) {
    case CLOSED:
      break;
    case OPENING:
      // if door has finished opening, start timer and keep door open
      if(sprite->animation_done()) {
	state = OPEN;
	sprite->set_action("open");
       stay_open_timer.start(1.0);
      }
      break;
    case OPEN:
      // if door was open long enough, start closing it
      if (stay_open_timer.check()) {
	state = CLOSING;
	sprite->set_action("closing", 1);
      }
      break;
    case CLOSING:
      // if door has finished closing, keep it shut
      if(sprite->animation_done()) {
	state = CLOSED;
	sprite->set_action("closed");
      }
      break;
  }
}

void
Door::draw(DrawingContext& context)
{
  sprite->draw(context, bbox.p1, LAYER_BACKGROUNDTILES+1);
}

void
Door::event(Player& , EventType type)
{
  switch (state) {
    case CLOSED:
      // if door was activated, start opening it
      if (type == EVENT_ACTIVATE) {
	state = OPENING;
        sound_manager->play("sounds/door.wav");
	sprite->set_action("opening", 1);
      }
      break;
    case OPENING:
      break;
    case OPEN:
      break;
    case CLOSING:
      break;
  }
}

HitResponse
Door::collision(GameObject& other, const CollisionHit& hit)
{
  switch (state) {
    case CLOSED:
      break;
    case OPENING:
      break;
    case OPEN:
      {
        // if door is open and was touched by a player, teleport the player
	Player* player = dynamic_cast<Player*> (&other);
	if (player) {
	  state = CLOSING;
	  sprite->set_action("closing", 1);
	  GameSession::current()->respawn(target_sector, target_spawnpoint);
	}
      }
      break;
    case CLOSING:
      break;
  }

  return TriggerBase::collision(other, hit);
}

IMPLEMENT_FACTORY(Door, "door");
