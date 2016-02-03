//  $Id: timer.cpp 4059 2006-07-21 11:45:14Z matzebraun $
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
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
//  02111-1307, USA.
#include <config.h>

#include <math.h>
#include "timer.hpp"

float game_time = 0;
float real_time = 0;

Timer::Timer()
  : period(0), cycle_start(0), cyclic(false)
{
}

Timer::~Timer()
{
}

void
Timer::start(float period, bool cyclic)
{
  this->period = period;
  this->cyclic = cyclic;
  cycle_start = game_time;
}

bool
Timer::check()
{
  if(period == 0)
    return false;

  if(game_time - cycle_start >= period) {
    if(cyclic) {
      cycle_start = game_time - fmodf(game_time - cycle_start, period);
    } else {
      period = 0;
    }
    return true;
  }

  return false;
}
