//  $Id: invisible_wall.hpp 4970 2007-04-09 00:00:06Z sommer $
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

#ifndef __INVISIBLE_WALL_H__
#define __INVISIBLE_WALL_H__

#include "object/moving_sprite.hpp"
#include "lisp/lisp.hpp"
#include "physic.hpp"
#include "timer.hpp"

class Player;

/** A tile that starts falling down if tux stands to long on it */
class InvisibleWall : public MovingSprite, private UsesPhysic
{
public:
  InvisibleWall(const lisp::Lisp& lisp);
  virtual InvisibleWall* clone() const { return new InvisibleWall(*this); }

  HitResponse collision(GameObject& other, const CollisionHit& hit);

private:
  float width, height;
};

#endif
