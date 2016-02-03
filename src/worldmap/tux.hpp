//  $Id: tux.hpp 4961 2007-04-03 21:12:55Z sommer $
//
//  SuperTux -  A Jump'n Run
//  Copyright (C) 2004 Ingo Ruhnke <grumbel@gmx.de>
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
#ifndef __WORLDMAP_TUX_HPP__
#define __WORLDMAP_TUX_HPP__

#include <memory>
#include "game_object.hpp"
#include "worldmap.hpp"

class Sprite;

namespace WorldMapNS
{

class WorldMap;

class Tux : public GameObject
{
public:
  Direction back_direction;
private:
  WorldMap* worldmap;
  std::auto_ptr<Sprite> sprite;
  Controller* controller;

  Direction input_direction;
  Direction direction;
  Vector tile_pos;
  /** Length by which tux is away from its current tile, length is in
      input_direction direction */
  float offset;
  bool  moving;

  void stop();

  bool canWalk(int tile_data, Direction dir); /**< check if we can leave a tile (with given "tile_data") in direction "dir" */
  void updateInputDirection(); /**< if controller was pressed, update input_direction */
  void tryStartWalking(); /**< try starting to walk in input_direction */
  void tryContinueWalking(float elapsed_time); /**< try to continue walking in current direction */

public:
  Tux(WorldMap* worldmap_);
  ~Tux();

  void setup(); /**< called prior to first update */
  void draw(DrawingContext& context);
  void update(float elapsed_time);

  void set_direction(Direction dir);

  bool is_moving() const { return moving; }
  Vector get_pos();
  Vector get_tile_pos() const { return tile_pos; }
  void  set_tile_pos(Vector p) { tile_pos = p; }
};

}

#endif
