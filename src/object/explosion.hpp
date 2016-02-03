//  $Id: explosion.hpp 5104 2007-06-13 19:43:08Z sommer $
//
//  SuperTux -- Explosion object
//  Copyright (C) 2007 Christoph Sommer <christoph.sommer@2007.expires.deltadevelopment.de>
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

#ifndef __EXPLOSION_H__
#define __EXPLOSION_H__

#include "moving_sprite.hpp"
#include "lisp/lisp.hpp"

/**
 * Just your average explosion - goes boom, hurts Tux
 */
class Explosion : public MovingSprite
{
public:
  /**
   * Create new Explosion centered(!) at @c pos
   */
  Explosion(const Vector& pos);
  Explosion(const lisp::Lisp& reader);

  void update(float elapsed_time);
  HitResponse collision(GameObject& other, const CollisionHit& hit);

protected:
  /**
   * plays sound, starts animation
   */
  void explode();

private:
  enum State {
    STATE_WAITING,
    STATE_EXPLODING
  };
  State state;

};

#endif

