//  $Id: pulsing_light.hpp 4603 2007-01-19 13:37:44Z anmaster $
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

#ifndef __PULSING_LIGHT_HPP__
#define __PULSING_LIGHT_HPP__

#include "light.hpp"
#include "game_object.hpp"
#include "lisp/lisp.hpp"
#include "math/vector.hpp"
#include "video/color.hpp"

class Sprite;

/**
 * Light source that changes alpha value to give the impression of a pulsating light
 */
class PulsingLight : public Light
{
public:
  PulsingLight(const Vector& center, float cycle_len = 5.0, float min_alpha = 0.0, float max_alpha = 1.0, const Color& color = Color(1.0, 1.0, 1.0, 1.0));
  virtual ~PulsingLight();

  void update(float elapsed_time);
  void draw(DrawingContext& context);

protected:
  float min_alpha; /**< minimum alpha */
  float max_alpha; /**< maximum alpha */
  float cycle_len; /**< length in seconds of one cycle */

  float t; /**< local time in seconds */
};

#endif
