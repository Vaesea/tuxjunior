//  $Id: weak_block.hpp 4063 2006-07-21 21:05:23Z anmaster $
//
//  SuperTux - Weak Block
//  Copyright (C) 2006 Matthias Braun <matze@braunis.de>
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

#ifndef __WEAK_BLOCK_H__
#define __WEAK_BLOCK_H__

#include "object/moving_sprite.hpp"
#include "lisp/lisp.hpp"
#include "physic.hpp"
#include "timer.hpp"

/**
 * A block that can be destroyed by Bullet hits
 */
class WeakBlock : public MovingSprite
{
public:
  WeakBlock(const lisp::Lisp& lisp);

  HitResponse collision(GameObject& other, const CollisionHit& hit);
  void update(float elapsed_time);

protected:
  /**
   * called by self when hit by a bullet
   */
  void startBurning();

  /**
   * pass hit to nearby WeakBlock objects
   */
  void spreadHit();

private:
  enum State {
    STATE_NORMAL, /**< default state */
    STATE_BURNING, /**< on fire, still solid */
    STATE_DISINTEGRATING /**< crumbling to dust, no longer solid */
  };
  State state;

  Physic physic;
};

#endif
