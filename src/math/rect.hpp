//  $Id: rect.hpp 4059 2006-07-21 11:45:14Z matzebraun $
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

#ifndef __RECT_H__
#define __RECT_H__

#include <assert.h>
#include "vector.hpp"

/** This class represents a rectangle.
 * (Implementation Note) We're using upper left and lower right point instead of
 * upper left and width/height here, because that makes the collision dectection
 * a little bit efficienter.
 */
class Rect
{
public:
  Rect()
  { }

  Rect(const Vector& np1, const Vector& np2)
    : p1(np1), p2(np2)
  {
  }

  Rect(float x1, float y1, float x2, float y2)
    : p1(x1, y1), p2(x2, y2)
  {
    assert(p1.x <= p2.x && p1.y <= p2.y);
  }

  float get_left() const
  { return p1.x; }

  float get_right() const
  { return p2.x; }

  float get_top() const
  { return p1.y; }

  float get_bottom() const
  { return p2.y; }

  float get_width() const
  { return p2.x - p1.x; }

  float get_height() const
  { return p2.y - p1.y; }

  Vector get_middle() const
  { return Vector((p1.x+p2.x)/2, (p1.y+p2.y)/2); }

  void set_pos(const Vector& v)
  {
    move(v-p1);
  }

  void set_height(float height)
  {
    p2.y = p1.y + height;
  }
  void set_width(float width)
  {
    p2.x = p1.x + width;
  }
  void set_size(float width, float height)
  {
    set_width(width);
    set_height(height);
  }
  Vector get_size()
  {
    return Vector(get_width(), get_height());
  }

  void move(const Vector& v)
  {
    p1 += v;
    p2 += v;
  }

  bool contains(const Vector& v) const
  {
    return v.x >= p1.x && v.y >= p1.y && v.x < p2.x && v.y < p2.y;
  }
  bool contains(const Rect& other) const
  {
    if(p1.x >= other.p2.x || other.p1.x >= p2.x)
      return false;
    if(p1.y >= other.p2.y || other.p1.y >= p2.y)
      return false;

    return true;
  }

  // leave these 2 public to safe the headaches of set/get functions for such
  // simple things :)

  /// upper left edge
  Vector p1;
  /// lower right edge
  Vector p2;
};

#endif
