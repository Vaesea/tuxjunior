//  $Id: level_transformer.hpp 4059 2006-07-21 11:45:14Z matzebraun $
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

#ifndef __LEVEL_TRANSFORMER_H__
#define __LEVEL_TRANSFORMER_H__

class Level;
class Sector;

/**
 * This class is an abstract interface for algorithms that transform levels in
 * some way before they are played.
 */
class LevelTransformer
{
public:
  virtual ~LevelTransformer();

  /** transform a complete Level, the standard implementation just calls
   * transformSector on each sector in the level.
   */
  virtual void transform(Level* level);

  virtual void transform_sector(Sector* sector) = 0;
};

#endif
