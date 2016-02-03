//  $Id: secretarea_trigger.cpp 4095 2006-07-26 17:43:28Z sommer $
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

#include "secretarea_trigger.hpp"
#include "game_session.hpp"
#include "lisp/lisp.hpp"
#include "lisp/writer.hpp"
#include "object_factory.hpp"
#include "main.hpp"
#include "sector.hpp"
#include "level.hpp"
#include "gettext.hpp"
#include "object/tilemap.hpp"

static const float MESSAGE_TIME=3.5;

SecretAreaTrigger::SecretAreaTrigger(const lisp::Lisp& reader)
	: fade_tilemap("")
{
  reader.get("x", bbox.p1.x);
  reader.get("y", bbox.p1.y);
  float w = 32, h = 32;
  reader.get("width", w);
  reader.get("height", h);
  bbox.set_size(w, h);
  reader.get("fade-tilemap", fade_tilemap);

  message_displayed = false;
}

SecretAreaTrigger::SecretAreaTrigger(const Rect& area, std::string fade_tilemap)
	: fade_tilemap(fade_tilemap)
{
  bbox = area;
  message_displayed = false;
}

SecretAreaTrigger::~SecretAreaTrigger()
{
}

void
SecretAreaTrigger::write(lisp::Writer& writer)
{
  writer.start_list("secretarea");

  writer.write_float("x", bbox.p1.x);
  writer.write_float("y", bbox.p1.y);
  writer.write_float("width", bbox.get_width());
  writer.write_float("height", bbox.get_height());
  writer.write_string("fade-tilemap", fade_tilemap);

  writer.end_list("secretarea");
}

void
SecretAreaTrigger::draw(DrawingContext& context)
{
  if (message_timer.started()) {
    context.push_transform();
    context.set_translation(Vector(0, 0));
    Vector pos = Vector(0, SCREEN_HEIGHT/2 - gold_text->get_height()/2);
    context.draw_center_text(gold_text, _("You found a secret area!"), pos, LAYER_GUI);
    context.pop_transform();
  }
  if (message_timer.check()) {
    remove_me();
  }
}

void
SecretAreaTrigger::event(Player& , EventType type)
{
  if(type == EVENT_TOUCH) {
    if (!message_displayed) {
      message_timer.start(MESSAGE_TIME);
      message_displayed = true;
      Sector::current()->get_level()->stats.secrets++;

      if (fade_tilemap != "") {
	// fade away tilemaps
	Sector& sector = *Sector::current();
	for(Sector::GameObjects::iterator i = sector.gameobjects.begin(); i != sector.gameobjects.end(); ++i) {
	  TileMap* tm = dynamic_cast<TileMap*>(*i);
	  if (!tm) continue;
	  if (tm->get_name() != fade_tilemap) continue;
	  tm->fade(0.0, 1.0);
	}
      }

    }
  }
}

IMPLEMENT_FACTORY(SecretAreaTrigger, "secretarea");
