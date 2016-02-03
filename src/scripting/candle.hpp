//  $Id: candle.hpp 4063 2006-07-21 21:05:23Z anmaster $
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

#ifndef __SCRIPTING_CANDLE_H__
#define __SCRIPTING_CANDLE_H__

#ifndef SCRIPTING_API
class Candle;
typedef Candle _Candle;
#endif

namespace Scripting
{

class Candle
{
public:
#ifndef SCRIPTING_API
  Candle(_Candle* candle);
  ~Candle();
#endif

  bool get_burning(); /**< returns true if candle is lighted */
  void set_burning(bool burning); /**< true: light candle, false: extinguish candle */

#ifndef SCRIPTING_API
  _Candle* candle;
#endif
};

}

#endif
