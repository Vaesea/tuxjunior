//  $Id: climbable.cpp 4762 2007-01-31 20:19:42Z sommer $
//
//  SuperTux - Climbable area
//  Copyright (C) 2007 Christoph Sommer <christoph.sommer@2007.expires.deltadevelopment.de>
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

#include "climbable.hpp"
#include "game_session.hpp"
#include "lisp/lisp.hpp"
#include "lisp/writer.hpp"
#include "object_factory.hpp"
#include "main.hpp"
#include "sector.hpp"
#include "level.hpp"
#include "gettext.hpp"
#include "object/tilemap.hpp"

namespace {
  const float GRACE_DX = 8; // how far off may the player's bounding-box be x-wise
  const float GRACE_DY = 8; // how far off may the player's bounding-box be y-wise
  const float ACTIVATE_TRY_FOR = 1; // how long to try correcting mis-alignment of player and climbable before giving up
  const float POSITION_FIX_AX = 50; // x-wise acceleration applied to player when trying to align player and Climbable
  const float POSITION_FIX_AY = 50; // y-wise acceleration applied to player when trying to align player and Climbable
}

Climbable::Climbable(const lisp::Lisp& reader)
  : climbed_by(0)
{
  reader.get("x", bbox.p1.x);
  reader.get("y", bbox.p1.y);
  float w = 32, h = 32;
  reader.get("width", w);
  reader.get("height", h);
  bbox.set_size(w, h);
}

Climbable::Climbable(const Rect& area)
  : climbed_by(0)
{
  bbox = area;
}

Climbable::~Climbable()
{
  if (climbed_by) {
    climbed_by->stop_climbing(*this);
    climbed_by = 0;
  }
}

void
Climbable::write(lisp::Writer& writer)
{
  writer.start_list("climbable");

  writer.write_float("x", bbox.p1.x);
  writer.write_float("y", bbox.p1.y);
  writer.write_float("width", bbox.get_width());
  writer.write_float("height", bbox.get_height());

  writer.end_list("climbable");
}

void 
Climbable::update(float /*elapsed_time*/)
{
  if (!climbed_by) return;

  if (!may_climb(*climbed_by)) {
    climbed_by->stop_climbing(*this);
    climbed_by = 0;
  }
}

void
Climbable::draw(DrawingContext& context)
{
  if (climbed_by) {
    context.push_transform();
    context.set_translation(Vector(0, 0));
    Vector pos = Vector(0, SCREEN_HEIGHT/2 - gold_text->get_height()/2);
    context.draw_center_text(gold_text, "Up we go...", pos, LAYER_GUI);
    context.pop_transform();
  }
}

void
Climbable::event(Player& player, EventType type)
{
  if ((type == EVENT_ACTIVATE) || (activate_try_timer.started())) {
    if (may_climb(player)) {
      climbed_by = &player;
      player.start_climbing(*this);
      activate_try_timer.stop();
    } else {
      if (type == EVENT_ACTIVATE) activate_try_timer.start(ACTIVATE_TRY_FOR);
      if (player.get_bbox().p1.x < get_bbox().p1.x - GRACE_DX) player.add_velocity(Vector(POSITION_FIX_AX,0));
      if (player.get_bbox().p2.x > get_bbox().p2.x + GRACE_DX) player.add_velocity(Vector(-POSITION_FIX_AX,0));
      if (player.get_bbox().p1.y < get_bbox().p1.y - GRACE_DY) player.add_velocity(Vector(0,POSITION_FIX_AY));
      if (player.get_bbox().p2.y > get_bbox().p2.y + GRACE_DY) player.add_velocity(Vector(0,-POSITION_FIX_AY));
    }
  }
  if(type == EVENT_LOSETOUCH) {
    player.stop_climbing(*this);
    climbed_by = 0;
  }
}

bool
Climbable::may_climb(Player& player) 
{
  if (player.get_bbox().p1.x < get_bbox().p1.x - GRACE_DX) return false;
  if (player.get_bbox().p2.x > get_bbox().p2.x + GRACE_DX) return false;
  if (player.get_bbox().p1.y < get_bbox().p1.y - GRACE_DY) return false;
  if (player.get_bbox().p2.y > get_bbox().p2.y + GRACE_DY) return false;
  return true;
}

IMPLEMENT_FACTORY(Climbable, "climbable");

