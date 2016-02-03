//  $Id: igel.hpp 4435 2006-11-04 14:13:27Z sommer $
//
//  SuperTux - Badguy "Igel"
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

#ifndef __IGEL_H__
#define __IGEL_H__

#include "walking_badguy.hpp"
#include "moving_object.hpp"

/**
 * Badguy "Igel" - a hedgehog that can absorb bullets
 */
class Igel : public WalkingBadguy
{
public:
  Igel(const lisp::Lisp& reader);
  Igel(const Vector& pos, Direction d);

  void write(lisp::Writer& writer);
  HitResponse collision_bullet(Bullet& bullet, const CollisionHit& hit);

  void active_update(float elapsed_time);

  virtual Igel* clone() const { return new Igel(*this); }

protected:
  bool collision_squished(GameObject& object);
  void be_normal(); /**< switch to state STATE_NORMAL */
  void turn_around(); /**< reverse direction, assumes we are in STATE_NORMAL */
  bool can_see(const MovingObject& o); /**< check if we can see o */

private:
  Timer turn_recover_timer; /**< wait time until we will turn around again when shot at */

};

#endif
