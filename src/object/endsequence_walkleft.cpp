//  $Id: endsequence_walkleft.cpp 5161 2007-10-07 09:08:29Z ravualhemio $
//
//  SuperTux - End Sequence: Tux walks right
//  Copyright (C) 2007 Christoph Sommer <christoph.sommer@2006.expires.deltadevelopment.de>
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
#include "endsequence_walkleft.hpp"
#include "sector.hpp"
#include "mainloop.hpp"
#include "object/player.hpp"

EndSequenceWalkLeft::EndSequenceWalkLeft()
: EndSequence()
{
}

EndSequenceWalkLeft::~EndSequenceWalkLeft()
{
}

void
EndSequenceWalkLeft::draw(DrawingContext& /*context*/)
{
}

void
EndSequenceWalkLeft::starting()
{
  EndSequence::starting();
  last_x_pos = -1;
  endsequence_timer.start(7.3f * main_loop->get_speed());
}

void
EndSequenceWalkLeft::running(float elapsed_time)
{
  EndSequence::running(elapsed_time);
  Player& tux = *Sector::current()->player;

  if (tux_may_walk) {
    end_sequence_controller->press(Controller::LEFT);
    if (int(last_x_pos) == int(tux.get_pos().x)) {
      end_sequence_controller->press(Controller::JUMP);
    }
  }

  last_x_pos = tux.get_pos().x;

  if (endsequence_timer.check()) isdone = true;
}

void
EndSequenceWalkLeft::stopping()
{
  EndSequence::stopping();
}
