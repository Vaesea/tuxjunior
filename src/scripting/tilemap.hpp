//  $Id: tilemap.hpp 4956 2007-04-01 15:10:23Z sommer $
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

#ifndef __SCRIPTING_TILEMAP_H__
#define __SCRIPTING_TILEMAP_H__

#ifndef SCRIPTING_API
class TileMap;
typedef TileMap _TileMap;
#endif

namespace Scripting
{

class TileMap
{
public:
#ifndef SCRIPTING_API
  TileMap(_TileMap* tilemap);
  ~TileMap();
#endif

  /** Move tilemap until at given node, then stop */
  void goto_node(int node_no);

  /** Start moving tilemap */
  void start_moving();

  /** Stop tilemap at next node */
  void stop_moving();

  /**
   * Start fading the tilemap to opacity given by @c alpha.
   * Destination opacity will be reached after @c seconds seconds. Also influences solidity.
   */
  void fade(float alpha, float seconds);

  /**
   * Instantly switch tilemap's opacity to @c alpha. Also influences solidity.
   */
  void set_alpha(float alpha);

  /**
   * Return tilemap's opacity. Note that while the tilemap is fading in or out, this will return the current alpha value, not the target alpha.
   */
  float get_alpha();

#ifndef SCRIPTING_API
  _TileMap* tilemap;
#endif
};

}

#endif
