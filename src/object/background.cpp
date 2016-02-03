//  $Id: background.cpp 4059 2006-07-21 11:45:14Z matzebraun $
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

#include <stdexcept>
#include "background.hpp"
#include "camera.hpp"
#include "video/drawing_context.hpp"
#include "lisp/lisp.hpp"
#include "lisp/writer.hpp"
#include "object_factory.hpp"
#include "resources.hpp"
#include "main.hpp"
#include "log.hpp"

Background::Background()
  : layer(LAYER_BACKGROUND0)
{
}

Background::Background(const lisp::Lisp& reader)
  : layer(LAYER_BACKGROUND0)
{
  // read position, defaults to (0,0)
  float px = 0;
  float py = 0;
  reader.get("x", px);
  reader.get("y", py);
  this->pos = Vector(px,py);

  speed = 1.0;
  speed_y = 1.0;

  reader.get("layer", layer);
  if(!reader.get("image", imagefile) || !reader.get("speed", speed))
    throw std::runtime_error("Must specify image and speed for background");

  set_image(imagefile, speed);
  reader.get("speed-y", speed_y);
  if (reader.get("image-top", imagefile_top)) {
    image_top.reset(new Surface(imagefile_top));
  }
  if (reader.get("image-bottom", imagefile_bottom)) {
    image_bottom.reset(new Surface(imagefile_bottom));
  }
}

Background::~Background()
{
}

void
Background::write(lisp::Writer& writer)
{
  writer.start_list("background");

  if (image_top.get() != NULL)
    writer.write_string("image-top", imagefile_top);

  writer.write_string("image", imagefile);
  if (image_bottom.get() != NULL)
    writer.write_string("image-bottom", imagefile_bottom);

  writer.write_float("speed", speed);
  writer.write_float("speed-y", speed_y);
  writer.write_int("layer", layer);

  writer.end_list("background");
}

void
Background::update(float)
{
}

void
Background::set_image(const std::string& name, float speed)
{
  this->imagefile = name;
  this->speed = speed;

  image.reset(new Surface(name));
}

void
Background::draw(DrawingContext& context)
{
  if(image.get() == NULL)
    return;

  int w = (int) image->get_width();
  int h = (int) image->get_height();
  int sx = int(pos.x-context.get_translation().x * speed) % w - w;
  int sy = int(pos.y-context.get_translation().y * speed_y) % h - h;
  int center_image_py = int(pos.y-context.get_translation().y * speed_y);
  int bottom_image_py = int(pos.y-context.get_translation().y * speed_y) + h;
  context.push_transform();
  context.set_translation(Vector(0, 0));
  for(int x = sx; x < SCREEN_WIDTH; x += w) {
    for(int y = sy; y < SCREEN_HEIGHT; y += h) {
      if (image_top.get() != NULL && (y < center_image_py)) {
        context.draw_surface(image_top.get(), Vector(x, y), layer);
        continue;
      }
      if (image_bottom.get() != NULL && (y >= bottom_image_py)) {
        context.draw_surface(image_bottom.get(), Vector(x, y), layer);
        continue;
      }
      context.draw_surface(image.get(), Vector(x, y), layer);
    }
  }
  context.pop_transform();
}

IMPLEMENT_FACTORY(Background, "background");
