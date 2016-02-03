//  $Id: mrbomb.hpp 4435 2006-11-04 14:13:27Z sommer $
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

#ifndef __MRBOMB_H__
#define __MRBOMB_H__

#include "walking_badguy.hpp"
#include "object/portable.hpp"

class MrBomb : public WalkingBadguy, public Portable
{
public:
  MrBomb(const lisp::Lisp& reader);
  MrBomb(const Vector& pos, Direction d);

  void write(lisp::Writer& writer);
  void kill_fall();
  HitResponse collision(GameObject& object, const CollisionHit& hit);
  HitResponse collision_player(Player& player, const CollisionHit& hit);

  void active_update(float elapsed_time);

  void grab(MovingObject& object, const Vector& pos, Direction dir);
  void ungrab(MovingObject& object, Direction dir);
  bool is_portable() const;

  void freeze();
  bool is_freezable() const;

  virtual MrBomb* clone() const { return new MrBomb(*this); }

protected:
  bool collision_squished(GameObject& object);

private:
  bool grabbed;
};

#endif
