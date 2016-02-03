//  $Id: mole_rock.hpp 4603 2007-01-19 13:37:44Z anmaster $
//
//  MoleRock - Rock thrown by "Mole" Badguy
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
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
//  02111-1307, USA.

#ifndef __MOLE_ROCK_H__
#define __MOLE_ROCK_H__

#include "badguy.hpp"

/**
 * Badguy "MoleRock" - Rock thrown by "Mole" Badguy
 */
class MoleRock : public BadGuy
{
public:
  MoleRock(const lisp::Lisp& reader);
  MoleRock(const Vector& pos, const Vector& velocity, const BadGuy* parent);
  MoleRock(const MoleRock& mole_rock);
  ~MoleRock();

  void activate();
  void deactivate();
  void write(lisp::Writer& writer);

  void active_update(float elapsed_time);

  void collision_solid(const CollisionHit& hit);
  HitResponse collision_badguy(BadGuy& badguy, const CollisionHit& hit);
  HitResponse collision_player(Player& player, const CollisionHit& hit);

  virtual MoleRock* clone() const { return new MoleRock(*this); }

  virtual bool updatePointers(const GameObject* from_object, GameObject* to_object);

protected:
  const BadGuy* parent; /**< collisions with this BadGuy will be ignored */
  const Vector initial_velocity; /**< velocity at time of creation */
};

#endif
