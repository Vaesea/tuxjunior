//  $Id: level_time.hpp 4063 2006-07-21 21:05:23Z anmaster $
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

#ifndef __SCRIPTING_LEVELTIME_H__
#define __SCRIPTING_LEVELTIME_H__

#ifndef SCRIPTING_API
class LevelTime;
typedef LevelTime _LevelTime;
#endif

namespace Scripting
{

class LevelTime
{
public:
#ifndef SCRIPTING_API
  LevelTime(_LevelTime* level_time);
  ~LevelTime();
#endif

  /**
   * Resumes the countdown
   */
  void start();
    
  /**
   * Pauses the countdown
   */
  void stop();

  /**
   * Returns the number of seconds left on the clock
   */
  float get_time();

  /**
   * Changes the number of seconds left on the clock
   */
  void set_time(float time_left);

#ifndef SCRIPTING_API
  _LevelTime* level_time;
#endif
};

}

#endif
