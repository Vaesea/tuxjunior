//  $Id: climbable.hpp 4762 2007-01-31 20:19:42Z sommer $
//
//  SuperTux - Climbable area
//  Copyright (C) 2007 Christoph Sommer <christoph.sommer@2007.expires.deltadevelopment.de>
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

#ifndef __CLIMBABLE_H__
#define __CLIMBABLE_H__

#include "trigger_base.hpp"
#include "serializable.hpp"
#include "resources.hpp"
#include "video/drawing_context.hpp"
#include "timer.hpp"
#include "object/player.hpp"

class Climbable : public TriggerBase, public Serializable
{
public:
  Climbable(const lisp::Lisp& reader);
  Climbable(const Rect& area);
  ~Climbable();

  void write(lisp::Writer& writer);
  void event(Player& player, EventType type);
  void update(float elapsed_time);
  void draw(DrawingContext& context);

  /**
   * returns true if the player is within bounds of the Climbable
   */
  bool may_climb(Player& player);

protected:
  Player* climbed_by; /**< set to player who's currently climbing us, null if nobody is */
  Timer activate_try_timer; /**< try to correct mis-alignment while this timer runs */
};

#endif
