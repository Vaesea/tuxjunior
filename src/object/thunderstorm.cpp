//  $Id: thunderstorm.cpp 4661 2007-01-23 12:33:50Z matzeb $
//
//  SuperTux - Thunderstorm Game Object
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
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#include <config.h>

#include "thunderstorm.hpp"
#include "scripting/squirrel_util.hpp"
#include "audio/sound_manager.hpp"
#include "video/drawing_context.hpp"
#include "object_factory.hpp"
#include "object/electrifier.hpp"

#include <stdexcept>
#include <iostream>
#include "main.hpp"
#include "resources.hpp"
#include "sector.hpp"
#include "gettext.hpp"
#include "object/player.hpp"
#include "lisp/list_iterator.hpp"
#include "log.hpp"

namespace {
	const float LIGHTNING_DELAY = 2.0f;
	const float FLASH_DISPLAY_TIME = 0.1f;
}

Thunderstorm::Thunderstorm(const lisp::Lisp& reader)
  : running(true), interval(10.0f)
{
  reader.get("name", name);
  reader.get("running", running);
  reader.get("interval", interval);
  if(interval <= 0) {
    log_warning << "Running a thunderstorm with non-positive time interval is a bad idea" << std::endl;
  }

  sound_manager->preload("sounds/explosion.wav");
  sound_manager->preload("sounds/upgrade.wav");

  if (running) {
    running = false; // else start() is ignored
    start();
  }
}

void
Thunderstorm::update(float )
{
  if (!running) return;
  if (time_to_thunder.check()) {
    thunder();
    time_to_lightning.start(LIGHTNING_DELAY);
  }
  if (time_to_lightning.check()) {
    lightning();
    time_to_thunder.start(interval);
  }
}

void
Thunderstorm::draw(DrawingContext& context)
{
  if (!flash_display_timer.started()) return;

  float alpha = 0.33f;
  context.push_transform();
  context.set_translation(Vector(0, 0));
  context.draw_filled_rect(Vector(0, 0), Vector(SCREEN_WIDTH, SCREEN_HEIGHT), Color(1, 1, 1, alpha), LAYER_BACKGROUNDTILES-1);
  context.pop_transform();

}

void
Thunderstorm::expose(HSQUIRRELVM vm, SQInteger table_idx)
{
  if (name == "") return;
  Scripting::Thunderstorm* interface = new Scripting::Thunderstorm(this);
  expose_object(vm, table_idx, interface, name, true);
}

void
Thunderstorm::unexpose(HSQUIRRELVM vm, SQInteger table_idx)
{
  if (name == "") return;
  Scripting::unexpose_object(vm, table_idx, name);
}

void
Thunderstorm::start()
{
  if (running) return;
  running = true;
  time_to_thunder.start(interval);
  time_to_lightning.stop();
}

void
Thunderstorm::stop()
{
  if (!running) return;
  running = false;
  time_to_thunder.stop();
  time_to_lightning.stop();
}

void
Thunderstorm::thunder()
{
  sound_manager->play("sounds/explosion.wav");
}

void
Thunderstorm::lightning()
{
  flash();
  electrify();
}

void
Thunderstorm::flash()
{
  sound_manager->play("sounds/upgrade.wav");
  sound_manager->play("sounds/explosion.wav");
  flash_display_timer.start(FLASH_DISPLAY_TIME);
}

void
Thunderstorm::electrify()
{
  Sector::current()->add_object(new Electrifier(75, 1421, 0.5));
  Sector::current()->add_object(new Electrifier(76, 1422, 0.5));
}

IMPLEMENT_FACTORY(Thunderstorm, "thunderstorm");
