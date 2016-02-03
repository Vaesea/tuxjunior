//  $Id: flyingsnowball.hpp 4435 2006-11-04 14:13:27Z sommer $
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

#ifndef __FLYINGSNOWBALL_H__
#define __FLYINGSNOWBALL_H__

#include "badguy.hpp"

class FlyingSnowBall : public BadGuy
{
public:
  FlyingSnowBall(const lisp::Lisp& reader);
  FlyingSnowBall(const Vector& pos);

  void activate();
  void write(lisp::Writer& writer);
  void active_update(float elapsed_time);
  void collision_solid(const CollisionHit& hit);

  virtual FlyingSnowBall* clone() const { return new FlyingSnowBall(*this); }

protected:
  enum FlyingSnowballMode {
    FLY_UP,
    FLY_DOWN
  };
  FlyingSnowballMode mode;
  bool collision_squished(GameObject& object);
private:
  Timer timer;
  Timer puff_timer; /**< time until the next smoke puff is spawned */
};

#endif
