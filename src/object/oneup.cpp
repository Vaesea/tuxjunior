//  $Id: oneup.cpp 4707 2007-01-28 16:32:42Z ravualhemio $
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

#include <config.h>

#include "oneup.hpp"
#include "resources.hpp"
#include "player.hpp"
#include "player_status.hpp"
#include "sector.hpp"
#include "level.hpp"
#include "statistics.hpp"
#include "video/drawing_context.hpp"

OneUp::OneUp(const Vector& pos, Direction direction)
	: MovingSprite(pos, "images/powerups/1up/1up.sprite", LAYER_FLOATINGOBJECTS, COLGROUP_TOUCHABLE)
{
  physic.set_velocity((direction == LEFT)?-100:100, -400);
}

void
OneUp::update(float elapsed_time)
{
  if(!Sector::current()->inside(bbox))
    remove_me();

  movement = physic.get_movement(elapsed_time);
}

HitResponse
OneUp::collision(GameObject& other, const CollisionHit& )
{
  Player* player = dynamic_cast<Player*> (&other);
  if(player) {
    player->get_status()->add_coins(100);
#if 0
    // FIXME: do we want this? q.v. src/level.cpp
    Sector::current()->get_level()->stats.coins += 100;
#endif
    remove_me();
    return ABORT_MOVE;
  }
  return FORCE_MOVE;
}
