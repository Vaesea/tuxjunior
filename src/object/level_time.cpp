//  $Id: level_time.cpp 4716 2007-01-28 19:45:34Z grumbel $
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

#include "level_time.hpp"

#include <stdexcept>
#include <iostream>
#include <sstream>
#include "main.hpp"
#include "resources.hpp"
#include "sector.hpp"
#include "gettext.hpp"
#include "object_factory.hpp"
#include "object/player.hpp"
#include "video/drawing_context.hpp"
#include "lisp/list_iterator.hpp"
#include "log.hpp"
#include "scripting/level_time.hpp"
#include "scripting/squirrel_util.hpp"

/** When to alert player they're low on time! */
static const float TIME_WARNING = 20;

LevelTime::LevelTime(const lisp::Lisp& reader)
: running(true), time_left(0)
{
  reader.get("name", name);
  reader.get("time", time_left);
  if(time_left <= 0) throw std::runtime_error("No or invalid leveltime specified");
  time_surface.reset(new Surface("images/engine/hud/time-0.png"));
}

void
LevelTime::expose(HSQUIRRELVM vm, SQInteger table_idx)
{
  if (name.empty()) return;
  Scripting::LevelTime* interface = new Scripting::LevelTime(this);
  expose_object(vm, table_idx, interface, name, true);
}

void
LevelTime::unexpose(HSQUIRRELVM vm, SQInteger table_idx)
{
  if (name.empty()) return;
  Scripting::unexpose_object(vm, table_idx, name);
}

void
LevelTime::update(float elapsed_time)
{
  if (!running) return;

  int prev_time = (int) floor(time_left*5);
  time_left -= elapsed_time;
  if(time_left <= 0) {
    if(time_left <= -5 || !Sector::current()->player->get_coins())
    {
      Sector::current()->player->kill(true);
      stop();
    }
    if(prev_time != (int) floor(time_left*5))
    {
      Sector::current()->player->add_coins(-1);
    }
  }
}

void
LevelTime::draw(DrawingContext& context)
{
  context.push_transform();
  context.set_translation(Vector(0, 0));

  if ((time_left > TIME_WARNING) || (int(game_time * 2.5) % 2)) {
    std::stringstream ss;
    ss << int(time_left);
    std::string time_text = ss.str();

    Surface* time_surf = time_surface.get();
    if (time_surf) {
      float all_width = time_surf->get_width() + white_text->get_text_width(time_text);
      context.draw_surface(time_surf, Vector((SCREEN_WIDTH - all_width)/2, BORDER_Y + 1), LAYER_FOREGROUND1);
      context.draw_text(gold_text, time_text, Vector((SCREEN_WIDTH - all_width)/2 + time_surf->get_width(), BORDER_Y), ALIGN_LEFT, LAYER_FOREGROUND1);
    }
  }

  context.pop_transform();
}

void
LevelTime::start()
{
  running = true;
}

void
LevelTime::stop()
{
  running = false;
}

float
LevelTime::get_time()
{
  return time_left;
}

void
LevelTime::set_time(float time_left)
{
  this->time_left = std::min(std::max(time_left, 0.0f), 999.0f);
}

IMPLEMENT_FACTORY(LevelTime, "leveltime");
