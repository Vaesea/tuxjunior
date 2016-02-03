//  $Id: dart.hpp 4063 2006-07-21 21:05:23Z anmaster $
//
//  Dart - Your average poison dart
//  Copyright (C) 2006 Christoph Sommer <tuxjunior@2006.expires.deltadevelopment.de>
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

#ifndef __DART_H__
#define __DART_H__

#include "badguy.hpp"

/**
 * Badguy "Dart" - Your average poison dart
 */
class Dart : public BadGuy
{
public:
  Dart(const lisp::Lisp& reader);
  Dart(const Vector& pos, Direction d, const BadGuy* parent);
  Dart(const Dart& dart);
  ~Dart();

  void activate();
  void deactivate();
  void write(lisp::Writer& writer);

  void active_update(float elapsed_time);

  void collision_solid(const CollisionHit& hit);
  HitResponse collision_badguy(BadGuy& badguy, const CollisionHit& hit);
  HitResponse collision_player(Player& player, const CollisionHit& hit);

  virtual Dart* clone() const { return new Dart(*this); }

  virtual bool updatePointers(const GameObject* from_object, GameObject* to_object);

protected:
  const BadGuy* parent; /**< collisions with this BadGuy will be ignored */
  std::auto_ptr<SoundSource> sound_source; /**< SoundSource for ambient sound */
};

#endif
