//  $Id: mriceblock.hpp 5254 2008-01-06 02:40:59Z sommer $
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

#ifndef __MRICEBLOCK_H__
#define __MRICEBLOCK_H__

#include "walking_badguy.hpp"
#include "object/portable.hpp"

class MrIceBlock : public WalkingBadguy, public Portable
{
public:
  MrIceBlock(const lisp::Lisp& reader);
  MrIceBlock(const Vector& pos, Direction d);

  void activate();
  void write(lisp::Writer& writer);
  HitResponse collision(GameObject& object, const CollisionHit& hit);
  void collision_solid(const CollisionHit& hit);
  HitResponse collision_badguy(BadGuy& badguy, const CollisionHit& hit);
  HitResponse collision_player(Player& player, const CollisionHit& hit);

  void active_update(float elapsed_time);

  void grab(MovingObject& object, const Vector& pos, Direction dir);
  void ungrab(MovingObject& object, Direction dir);
  bool is_portable() const;

  bool can_break();

  virtual MrIceBlock* clone() const { return new MrIceBlock(*this); }

protected:
  bool collision_squished(GameObject& object);

private:
  enum IceState {
    ICESTATE_NORMAL,
    ICESTATE_FLAT,
    ICESTATE_GRABBED,
    ICESTATE_KICKED
  };

  void set_state(IceState state);

  IceState ice_state;
  Timer nokick_timer;
  Timer flat_timer;
  int squishcount;
};

#endif
