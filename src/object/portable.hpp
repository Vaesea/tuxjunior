//  $Id: portable.hpp 4114 2006-08-02 22:23:22Z matzebraun $
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

#ifndef __PORTABLE_H__
#define __PORTABLE_H__

#include "moving_object.hpp"
#include "direction.hpp"
#include "refcounter.hpp"

/**
 * An object that inherits from this object is considered "portable" and can
 * be carried around by the player.
 * The object has to additionally set the PORTABLE flag (this allows to
 * make the object only temporarily portable by resetting the flag)
 */
class Portable
{
public:
  virtual ~Portable()
  { }

  /**
   * called each frame when the object has been grabbed.
   */
  virtual void grab(MovingObject& object, const Vector& pos, Direction dir) = 0;

  virtual void ungrab(MovingObject& , Direction )
  {}

  virtual bool is_portable() const
  {
    return true;
  }
};

#endif
