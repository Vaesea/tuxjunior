//  $Id: moving_sprite.hpp 4509 2006-12-28 16:00:43Z sommer $
//
//  SuperTux - MovingSprite Base Class
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

#ifndef __MOVING_SPRITE_H__
#define __MOVING_SPRITE_H__

#include <string>
#include "moving_object.hpp"
#include "sprite/sprite.hpp"
#include "video/drawing_context.hpp"
#include "object/anchor_point.hpp"

/**
 * Abstract base class for MovingObjects that are represented by a Sprite
 */
class MovingSprite : public MovingObject
{
public:
  MovingSprite(const Vector& pos, const std::string& sprite_name, int layer = LAYER_OBJECTS, CollisionGroup collision_group = COLGROUP_MOVING);
  MovingSprite(const lisp::Lisp& reader, const Vector& pos, int layer = LAYER_OBJECTS, CollisionGroup collision_group = COLGROUP_MOVING);
  MovingSprite(const lisp::Lisp& reader, const std::string& sprite_name, int layer = LAYER_OBJECTS, CollisionGroup collision_group = COLGROUP_MOVING);
  MovingSprite(const lisp::Lisp& reader, int layer = LAYER_OBJECTS, CollisionGroup collision_group = COLGROUP_MOVING);
  MovingSprite(const MovingSprite& moving_sprite);
  MovingSprite& operator=(const MovingSprite& moving_sprite);
  ~MovingSprite();

  virtual void draw(DrawingContext& context);
  virtual void update(float elapsed_time);

protected:
  std::string sprite_name;
  Sprite* sprite;
  int layer; /**< Sprite's z-position. Refer to video/drawing_context.hpp for sensible values. */

  /**
   * set new action for sprite and resize bounding box.
   * use with care as you can easily get stuck when resizing the bounding box.
   */
  void set_action(const std::string& action, int loops);

  /**
   * set new action for sprite and re-center bounding box.
   * use with care as you can easily get stuck when resizing the bounding box.
   */
  void set_action_centered(const std::string& action, int loops);

  /**
   * set new action for sprite and align bounding boxes at anchorPoint.
   * use with care as you can easily get stuck when resizing the bounding box.
   */
  void set_action(const std::string& action, int loops, AnchorPoint anchorPoint);
};

#endif
