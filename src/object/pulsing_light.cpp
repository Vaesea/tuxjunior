//  $Id: pulsing_light.cpp 4701 2007-01-28 13:23:57Z anmaster $
//
//  SuperTux - Pulsing Light
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

#include "pulsing_light.hpp"
#include "video/color.hpp"
#include <math.h>
#include "random_generator.hpp"

PulsingLight::PulsingLight(const Vector& center, float cycle_len, float min_alpha, float max_alpha, const Color& color)
	: Light(center, color), min_alpha(min_alpha), max_alpha(max_alpha), cycle_len(cycle_len), t(0)
{
  assert(cycle_len > 0);

  // start with random phase offset
  t = systemRandom.randf(0.0, cycle_len);
}

PulsingLight::~PulsingLight()
{
}

void
PulsingLight::update(float elapsed_time)
{
  Light::update(elapsed_time);

  t += elapsed_time;
  if (t > cycle_len) t -= cycle_len;
}

void
PulsingLight::draw(DrawingContext& context)
{
  Color old_color = color;

  color.alpha *= min_alpha + ((max_alpha - min_alpha) * cos(2 * M_PI * t / cycle_len));
  Light::draw(context);

  color = old_color;
}
