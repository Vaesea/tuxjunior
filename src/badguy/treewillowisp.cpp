//  $Id: treewillowisp.cpp 5059 2007-05-27 10:37:17Z wolfgangb $
//
//  SuperTux - "Will-O-Wisp" Badguy
//  Copyright (C) 2007 Matthias Braun
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

#include "treewillowisp.hpp"
#include "ghosttree.hpp"
#include "object/lantern.hpp"

static const std::string SOUNDFILE = "sounds/willowisp.wav";
static const float       SUCKSPEED = 25;

TreeWillOWisp::TreeWillOWisp(GhostTree* tree, const Vector& pos,
                             float radius, float speed)
  : BadGuy(Vector(0, 0), "images/creatures/willowisp/willowisp.sprite",
           LAYER_OBJECTS - 20), was_sucked(false), mystate(STATE_DEFAULT), tree(tree)
{
  treepos_delta = pos;
  sound_manager->preload(SOUNDFILE);

  this->radius = radius;
  this->angle  = 0;
  this->speed  = speed;
  start_position = tree->get_pos() + treepos_delta;
}

TreeWillOWisp::~TreeWillOWisp()
{
}

void
TreeWillOWisp::activate()
{
  sound_source.reset(sound_manager->create_sound_source(SOUNDFILE));
  sound_source->set_position(get_pos());
  sound_source->set_looping(true);
  sound_source->set_gain(2.0);
  sound_source->set_reference_distance(32);
  sound_source->play();

  set_group(COLGROUP_MOVING);
}

void
TreeWillOWisp::vanish()
{
  mystate = STATE_VANISHING;
  sprite->set_action("vanishing", 1);
  set_group(COLGROUP_DISABLED);
}

void
TreeWillOWisp::start_sucking(Vector suck_target)
{
  mystate = STATE_SUCKED;
  this->suck_target = suck_target;
  was_sucked = true;
}

HitResponse
TreeWillOWisp::collision_player(Player& player, const CollisionHit& hit)
{
  //TODO: basically a no-op. Remove if this doesn't change.
  return BadGuy::collision_player(player, hit);
}

bool
TreeWillOWisp::collides(GameObject& other, const CollisionHit& ) {
  Lantern* lantern = dynamic_cast<Lantern*>(&other);
  if (lantern && lantern->is_open())
    return true;
  if (dynamic_cast<Player*>(&other))
    return true;
  
  return false;
}

void
TreeWillOWisp::draw(DrawingContext& context)
{
  sprite->draw(context, get_pos(), layer);

  context.push_target();
  context.set_target(DrawingContext::LIGHTMAP);

  sprite->draw(context, get_pos(), layer);

  context.pop_target();
}

void
TreeWillOWisp::active_update(float elapsed_time)
{
  // remove TreeWillOWisp if it has completely vanished
  if (mystate == STATE_VANISHING) {
    if(sprite->animation_done()) {
      remove_me();
      tree->willowisp_died(this);
    }
    return;
  }

  if (mystate == STATE_SUCKED) {
    Vector dir = suck_target - get_pos();
    if(dir.norm() < 5) {
      vanish();
      return;
    }
    Vector newpos = get_pos() + dir * elapsed_time;
    movement = newpos - get_pos();
    return;
  }

  angle = fmodf(angle + elapsed_time * speed, (float) (2*M_PI));
  Vector newpos(tree->get_pos() + treepos_delta + Vector(sin(angle) * radius, 0));
  movement = newpos - get_pos();
  float sizemod = cos(angle) * 0.8f;
  /* TODO: modify sprite size */

  sound_source->set_position(get_pos());

  if(sizemod < 0) {
    layer = LAYER_OBJECTS + 5;
  } else {
    layer = LAYER_OBJECTS - 20;
  }
}

void
TreeWillOWisp::set_color(const Color& color)
{
  this->color = color;
  sprite->set_color(color);
}

Color
TreeWillOWisp::get_color() const
{
  return color;
}

