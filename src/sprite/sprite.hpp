//  $Id: sprite.hpp 4059 2006-07-21 11:45:14Z matzebraun $
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

#ifndef SUPERTUX_SPRITE_H
#define SUPERTUX_SPRITE_H

#include <string>
#include <assert.h>
#include <SDL.h>

#include "math/vector.hpp"
#include "math/rect.hpp"
#include "sprite_data.hpp"
#include "video/color.hpp"
#include "video/drawing_context.hpp"

class Surface;
class DrawingContext;
class Color;
class Blend;

class Sprite
{
public:
  Sprite(SpriteData& data);
  Sprite(const Sprite& other);
  ~Sprite();

  /** Draw sprite, automatically calculates next frame */
  void draw(DrawingContext& context, const Vector& pos, int layer);

  void draw_part(DrawingContext& context, const Vector& source,
      const Vector& size, const Vector& pos, int layer);

  /** Set action (or state) */
  void set_action(const std::string& act, int loops = -1);

  /** Set number of animation cycles until animation stops */
  void set_animation_loops(int loops = -1)
  { animation_loops = loops; }

  /** Set framerate */
  void set_fps(float new_fps);

  /* Stop animation */
  void stop_animation()
  { animation_loops = 0; }
  /** Check if animation is stopped or not */
  bool animation_done();

  float get_fps() const
  { return action->fps; }
  /** Get current action total frames */
  int get_frames() const
  { return action->surfaces.size(); }
  /** Get sprite's name */
  const std::string& get_name() const
  { return data.name; }
  /** Get current action name */
  const std::string& get_action() const
  { return action->name; }

  int get_width() const;
  int get_height() const;

  /** return x-offset of current action's hitbox, relative to start of image */
  float get_current_hitbox_x_offset() const;
  /** return y-offset of current action's hitbox, relative to start of image */
  float get_current_hitbox_y_offset() const;
  /** return width of current action's hitbox */
  float get_current_hitbox_width() const;
  /** return height of current action's hitbox */
  float get_current_hitbox_height() const;
  /** return current action's hitbox, relative to 0,0 */
  Rect get_current_hitbox() const;

  /** Set the angle of the sprite rotation in degree */
  void set_angle(float angle);

  /** Get the angle of the sprite rotation in degree */
  float get_angle() const;

  void set_color(const Color& color);

  Color get_color() const;

  void set_blend(const Blend& blend);

  Blend get_blend() const;

  /** Get current frame */
  int get_frame() const
  { return (int)frame; }
  /** Set current frame */
  void set_frame(int frame)
  {
    this->frame = (frame % get_frames());
  }
  Surface* get_frame(unsigned int frame)
  {
    assert(frame < action->surfaces.size());
    return action->surfaces[frame];
  }

private:
  void update();

  SpriteData& data;

  float frame;
  int   animation_loops;
  float last_ticks;
  float angle;
  Color color;
  Blend blend;

  SpriteData::Action* action;
};

#endif
