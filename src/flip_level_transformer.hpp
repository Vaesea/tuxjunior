//  $Id: flip_level_transformer.hpp 4903 2007-03-02 14:13:41Z tuxdev $
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
#ifndef __FLIP_LEVEL_TRANSFORMER_H__
#define __FLIP_LEVEL_TRANSFORMER_H__

#include "level_transformer.hpp"

class TileMap;
class BadGuy;
class SpawnPoint;
class MovingObject;
class Platform;
class Block;

/** Vertically or horizontally flip a level */
class FlipLevelTransformer : public LevelTransformer
{
public:
  virtual void transform_sector(Sector* sector);

private:
  void transform_tilemap(TileMap* tilemap);
  void transform_moving_object(float height, MovingObject* object);
  void transform_badguy(float height, BadGuy* badguy);
  void transform_spawnpoint(float height, SpawnPoint* spawnpoint);
  void transform_platform(float height, Platform& platform);
  void transform_block(float height, Block& block);
};

#endif
