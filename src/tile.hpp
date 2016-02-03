//  $Id: tile.hpp 5265 2008-01-08 00:10:32Z matzeb $
//
//  SuperTux
//  Copyright (C) 2004 Tobias Glaesser <tobi.web@gmx.de>
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
#ifndef TILE_H
#define TILE_H

#include <vector>
#include <SDL.h>
#include <stdint.h>
#include "video/surface.hpp"
#include "math/rect.hpp"
#include <memory>
#include <algorithm>
#include <sstream>
#include <stdexcept>
#include <list>
#include <physfs.h>
#include <sys/stat.h>
#include <stdio.h>
#include "addon_manager.hpp"
#include "config.h"
#include "log.hpp"
#include "lisp/parser.hpp"
#include "lisp/lisp.hpp"
#include "lisp/list_iterator.hpp"
#include <stdlib.h>
#include <string.h>

namespace lisp { class Lisp; }

class TileSet;
class DrawingContext;

/**
Tile Class
*/
class Tile
{
public:
  /// bitset for tile attributes
  enum {
    /** solid tile that is indestructable by Tux */
    SOLID     = 0x0001,
    /** uni-directional solid tile */
    UNISOLID  = 0x0002,
    /** a brick that can be destroyed by jumping under it */
    BRICK     = 0x0004,
    /** the level should be finished when touching a goaltile.
     * if data is 0 then the endsequence should be triggered, if data is 1
     * then we can finish the level instantly.
     */
    GOAL      = 0x0008,
    /** slope tile */
    SLOPE     = 0x0010,
    /** Bonusbox, content is stored in \a data */
    FULLBOX   = 0x0020,
    /** Tile is a coin */
    COIN      = 0x0040,

    /* interesting flags (the following are passed to gameobjects) */
    FIRST_INTERESTING_FLAG = 0x0100,

    /** an ice brick that makes tux sliding more than usual */
    ICE       = 0x0100,
    /** a water tile in which tux starts to swim */
    WATER     = 0x0200,
    /** a tile that hurts the player if he touches it */
    HURTS     = 0x0400,
    /** for lava: WATER, HURTS, FIRE */
    FIRE      = 0x0800
  };

  /// worldmap flags
  enum {
    WORLDMAP_NORTH = 0x0001,
    WORLDMAP_SOUTH = 0x0002,
    WORLDMAP_EAST  = 0x0004,
    WORLDMAP_WEST  = 0x0008,
	WORLDMAP_DIR_MASK = 0x000f,

    WORLDMAP_STOP  = 0x0010,

    // convenience values ("C" stands for crossroads)
    WORLDMAP_CNSE  = WORLDMAP_NORTH | WORLDMAP_SOUTH | WORLDMAP_EAST,
    WORLDMAP_CNSW  = WORLDMAP_NORTH | WORLDMAP_SOUTH | WORLDMAP_WEST,
    WORLDMAP_CNEW  = WORLDMAP_NORTH | WORLDMAP_EAST  | WORLDMAP_WEST,
    WORLDMAP_CSEW  = WORLDMAP_SOUTH | WORLDMAP_EAST  | WORLDMAP_WEST,
    WORLDMAP_CNSEW = WORLDMAP_NORTH | WORLDMAP_SOUTH | WORLDMAP_EAST | WORLDMAP_WEST
  };

  struct ImageSpec {
    ImageSpec(const std::string& newfile, const Rect& newrect)
      : file(newfile), rect(newrect)
    { }

    std::string file;
    Rect rect;
  };

private:
  const TileSet         *tileset;
  std::vector<ImageSpec> imagespecs;
  std::vector<Surface*>  images;

  /// tile attributes
  uint32_t attributes;

  /** General purpose data attached to a tile (content of a box, type of coin)*/
  int data;

  float anim_fps;

public:
  ~Tile();

  /** Draw a tile on the screen */
  void draw(DrawingContext& context, const Vector& pos, int z_pos) const;

  uint32_t getAttributes() const
  { return attributes; }

  int getData() const
  { return data; }

  /// returns the width of the tile in pixels
  int getWidth() const
  {
    if(!images.size())
      return 0;
    return (int) images[0]->get_width();
  }

  /// returns the height of the tiles in pixels
  int getHeight() const
  {
    if(!images.size())
      return 0;
    return (int) images[0]->get_height();
  }

protected:
  friend class TileSet;
  Tile(const TileSet *tileset);
  Tile(const TileSet *tileset, Uint32 attributes, const ImageSpec& imagespec);

  void load_images();

  /// parses the tile and returns it's id number
  uint32_t parse(const lisp::Lisp& reader);
  void parse_images(const lisp::Lisp& cur);
};

#endif
