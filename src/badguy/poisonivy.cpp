//  $Id: poisonivy.cpp 4435 2006-11-04 14:13:27Z sommer $
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

#include "poisonivy.hpp"
#include "random_generator.hpp"
#include "object/sprite_particle.hpp"

PoisonIvy::PoisonIvy(const lisp::Lisp& reader)
	: WalkingBadguy(reader, "images/creatures/poison_ivy/poison_ivy.sprite", "left", "right")
{
  walk_speed = 80;
}

PoisonIvy::PoisonIvy(const Vector& pos, Direction d)
	: WalkingBadguy(pos, d, "images/creatures/poison_ivy/poison_ivy.sprite", "left", "right")
{
  walk_speed = 80;
}

void
PoisonIvy::write(lisp::Writer& writer)
{
  writer.start_list("poisonivy");
  WalkingBadguy::write(writer);
  writer.end_list("poisonivy");
}

bool
PoisonIvy::collision_squished(GameObject& object)
{
  sprite->set_action(dir == LEFT ? "squished-left" : "squished-right");
  // spawn some particles
  // TODO: provide convenience function in MovingSprite or MovingObject?
  for (int i = 0; i < 3; i++) {
    Vector ppos = bbox.get_middle();
    float angle = systemRandom.randf(-M_PI_2, M_PI_2);
    float velocity = systemRandom.randf(350, 400);
    float vx = sin(angle)*velocity;
    float vy = -cos(angle)*velocity;
    Vector pspeed = Vector(vx, vy);
    Vector paccel = Vector(0, 100);
    Sector::current()->add_object(new SpriteParticle("images/objects/particles/poisonivy.sprite", "default", ppos, ANCHOR_MIDDLE, pspeed, paccel, LAYER_OBJECTS-1));
  }
  kill_squished(object);
  return true;
}

IMPLEMENT_FACTORY(PoisonIvy, "poisonivy")
