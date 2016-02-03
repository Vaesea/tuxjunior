//  $Id: mole_rock.cpp 4603 2007-01-19 13:37:44Z anmaster $
//
//  MoleRock - Rock thrown by "Mole" Badguy
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
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
//  02111-1307, USA.

#include <config.h>

#include "mole_rock.hpp"

MoleRock::MoleRock(const lisp::Lisp& reader)
	: BadGuy(reader, "images/creatures/mole/mole_rock.sprite", LAYER_TILES - 2), parent(0), initial_velocity(Vector(0, -400))
{
  physic.enable_gravity(true);
  countMe = false;
}

MoleRock::MoleRock(const Vector& pos, const Vector& velocity, const BadGuy* parent = 0)
	: BadGuy(pos, LEFT, "images/creatures/mole/mole_rock.sprite", LAYER_TILES - 2), parent(parent), initial_velocity(velocity)
{
  physic.enable_gravity(true);
  countMe = false;
}

MoleRock::MoleRock(const MoleRock& other)
	: BadGuy(other), parent(other.parent), initial_velocity(Vector(0, -400))
{
}

MoleRock::~MoleRock()
{
}

bool
MoleRock::updatePointers(const GameObject* from_object, GameObject* to_object)
{
  if (from_object == parent) {
    parent = dynamic_cast<MoleRock*>(to_object);
    return true;
  }
  return false;
}

void
MoleRock::write(lisp::Writer& writer)
{
  writer.start_list("mole_rock");
  writer.write_float("x", start_position.x);
  writer.write_float("y", start_position.y);
  writer.end_list("mole_rock");
}

void
MoleRock::activate()
{
  physic.set_velocity(initial_velocity);
  sprite->set_action("default");
}

void
MoleRock::deactivate()
{
  remove_me();
}

void
MoleRock::active_update(float elapsed_time)
{
  BadGuy::active_update(elapsed_time);
}

void
MoleRock::collision_solid(const CollisionHit& )
{
  sound_manager->play("sounds/darthit.wav", get_pos());
  remove_me();
}

HitResponse
MoleRock::collision_badguy(BadGuy& badguy, const CollisionHit& )
{
  // ignore collisions with parent
  if (&badguy == parent) {
    return FORCE_MOVE;
  }
  sound_manager->play("sounds/stomp.wav", get_pos());
  remove_me();
  badguy.kill_fall();
  return ABORT_MOVE;
}

HitResponse
MoleRock::collision_player(Player& player, const CollisionHit& hit)
{
  sound_manager->play("sounds/stomp.wav", get_pos());
  remove_me();
  return BadGuy::collision_player(player, hit);
}

IMPLEMENT_FACTORY(MoleRock, "mole_rock")
