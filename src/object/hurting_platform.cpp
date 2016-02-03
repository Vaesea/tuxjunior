//  $Id: hurting_platform.cpp 4063 2006-07-21 21:05:23Z anmaster $
//
//  SuperTux - Hurting Platform
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

#include <config.h>
#include <stdexcept>

#include "hurting_platform.hpp"

#include "log.hpp"
#include "player.hpp"
#include "badguy/badguy.hpp"
#include "object_factory.hpp"

HurtingPlatform::HurtingPlatform(const lisp::Lisp& reader)
	: Platform(reader)
{
  set_group(COLGROUP_TOUCHABLE);
}

HitResponse
HurtingPlatform::collision(GameObject& other, const CollisionHit& )
{
  Player* player = dynamic_cast<Player*>(&other);
  if (player) {
    player->kill(false);
  }
  BadGuy* badguy = dynamic_cast<BadGuy*>(&other);
  if (badguy) {
    badguy->kill_fall();
  }

  return FORCE_MOVE;
}

IMPLEMENT_FACTORY(HurtingPlatform, "hurting_platform");
