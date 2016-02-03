//  $Id: wind.hpp 4424 2006-10-28 00:45:41Z sommer $
//
//  SuperTux - Wind
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

#ifndef SUPERTUX_WIND_H
#define SUPERTUX_WIND_H

#include <set>
#include "moving_object.hpp"
#include "math/rect.hpp"
#include "sprite/sprite.hpp"
#include "script_interface.hpp"

class Player;

/**
 * Defines an area that will gently push Players in one direction
 */
class Wind : public MovingObject, public ScriptInterface
{
public:
  Wind(const lisp::Lisp& reader);

  void update(float elapsed_time);
  void draw(DrawingContext& context);
  HitResponse collision(GameObject& other, const CollisionHit& hit);

  /** 
   * @name Scriptable Methods
   * @{ 
   */

  /**
   * start blowing
   */
  void start();

  /**
   * stop blowing
   */
  void stop();

  /** 
   * @} 
   */

  virtual void expose(HSQUIRRELVM vm, SQInteger table_idx);
  virtual void unexpose(HSQUIRRELVM vm, SQInteger table_idx);

private:
  bool blowing; /**< true if wind is currently switched on */
  Vector speed;
  float acceleration;

  float elapsed_time; /**< stores last elapsed_time gotten at update() */
};

#endif
