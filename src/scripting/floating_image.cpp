//  $Id: floating_image.cpp 4463 2006-12-16 14:47:31Z sommer $
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

#include <assert.h>
#include <stdexcept>
#include "floating_image.hpp"
#include "sector.hpp"
#include "object/floating_image.hpp"
#include "worldmap/worldmap.hpp"

namespace Scripting
{

FloatingImage::FloatingImage(const std::string& spritefile)
{
  using namespace WorldMapNS;

  floating_image = new _FloatingImage(spritefile);
  if(Sector::current() != NULL) {
    Sector::current()->add_object(floating_image.get());
  } else if(WorldMap::current() != NULL) {
    WorldMap::current()->add_object(floating_image.get());
  } else {
    throw new std::runtime_error("Neither sector nor worldmap active");
  }
}

FloatingImage::~FloatingImage()
{
  floating_image->remove_me();
}

void
FloatingImage::set_layer(int layer)
{
  floating_image->set_layer(layer);
}

int
FloatingImage::get_layer()
{
  return floating_image->get_layer();
}

void
FloatingImage::set_pos(float x, float y)
{
  floating_image->set_pos(Vector(x, y));
}

float
FloatingImage::get_pos_x()
{
  return floating_image->get_pos().x;
}

float
FloatingImage::get_pos_y()
{
  return floating_image->get_pos().y;
}

void
FloatingImage::set_anchor_point(int anchor)
{
  floating_image->set_anchor_point((AnchorPoint) anchor);
}

int
FloatingImage::get_anchor_point()
{
  return (int) floating_image->get_anchor_point();
}

bool
FloatingImage::get_visible()
{
  return floating_image->get_visible();
}

void
FloatingImage::set_visible(bool visible)
{
  floating_image->set_visible(visible);
}

void
FloatingImage::set_action(const std::string& action)
{
  floating_image->set_action(action);
}

std::string
FloatingImage::get_action()
{
  return floating_image->get_action();
}

void
FloatingImage::fade_in(float fadetime)
{
  floating_image->fade_in(fadetime);
}

void
FloatingImage::fade_out(float fadetime)
{
  floating_image->fade_out(fadetime);
}


}
