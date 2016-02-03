//  $Id: tile_set.hpp 5266 2008-01-08 00:28:50Z matzeb $
//
//  SuperTux
//  Copyright (C) 2008 Matthias Braun <matze@braunis.de>
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
#ifndef HEADER_TILE_SET_HPP
#define HEADER_TILE_SET_HPP

#include <vector>
#include <string>
#include <assert.h>
#include "log.hpp"
#include "tile.hpp"

class TileSet
{
private:
  typedef std::vector<Tile*> Tiles;
  Tiles tiles;

  std::string tiles_path;
  bool        tiles_loaded;

  friend class TileManager;
  friend class Tile;
  TileSet(const std::string& filename);

public:
  TileSet();
  ~TileSet();

  void merge(const TileSet *tileset, uint32_t start, uint32_t end,
             uint32_t offset);

  const Tile* get(uint32_t id) const
  {
    assert(id < tiles.size());
    Tile* tile = tiles[id];
    if(!tile) {
      log_warning << "Invalid tile: " << id << std::endl;
      return tiles[0];
    }

    if(tile->images.size() == 0 && tile->imagespecs.size() != 0)
      tile->load_images();

    return tile;
  }

  uint32_t get_max_tileid() const
  {
    return tiles.size();
  }
};

#endif
