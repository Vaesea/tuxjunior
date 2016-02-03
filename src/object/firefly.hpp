//  $Id: firefly.hpp 4608 2007-01-20 00:48:21Z sommer $
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

#ifndef __FIREFLY_H__
#define __FIREFLY_H__

#include "lisp/lisp.hpp"
#include "object/moving_sprite.hpp"
#include "serializable.hpp"
#include "badguy/badguy.hpp"

/**
 * A Firefly: When tux touches it, it begins buzzing and you will respawn at this
 * position.
 */
class Firefly : public MovingSprite, public Serializable
{
public:
  Firefly(const lisp::Lisp& lisp);
  virtual Firefly* clone() const { return new Firefly(*this); }

  void write(lisp::Writer& writer);
  HitResponse collision(GameObject& other, const CollisionHit& hit);

private:
  bool activated;
  Vector initial_position; /**< position as in level file. This is where Tux will have to respawn, as the level is reset every time */
  void reactivate();
};

#endif
