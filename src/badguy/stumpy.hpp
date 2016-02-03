//  $Id: stumpy.hpp 3980 2006-07-10 19:55:56Z sommer $
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

#ifndef __STUMPY_H__
#define __STUMPY_H__

#include "walking_badguy.hpp"

class Stumpy : public WalkingBadguy
{
public:
  Stumpy(const lisp::Lisp& reader);
  Stumpy(const Vector& pos, Direction d);

  void activate();
  void active_update(float elapsed_time);
  void write(lisp::Writer& writer);
  void collision_solid(const CollisionHit& hit);
  HitResponse collision_badguy(BadGuy& badguy, const CollisionHit& hit);

  virtual Stumpy* clone() const { return new Stumpy(*this); }

protected:
  enum MyState {
    STATE_INVINCIBLE, STATE_NORMAL
  };
  MyState mystate;

  Timer invincible_timer;

  bool collision_squished(GameObject& object);
};

#endif
