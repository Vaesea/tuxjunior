//  $Id: light.hpp 3327 2006-04-13 15:02:40Z ravu_al_hemio $
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

#ifndef __SPOTLIGHT_HPP__
#define __SPOTLIGHT_HPP__

#include "game_object.hpp"
#include "math/vector.hpp"
#include "lisp/lisp.hpp"
#include "video/color.hpp"

class Sprite;

class Spotlight : public GameObject
{
public:
  Spotlight(const lisp::Lisp& reader);
  virtual ~Spotlight();

  void update(float elapsed_time);
  void draw(DrawingContext& context);

private:
  Vector  position;
  float   angle;
  Sprite* center;
  Sprite* base;
  Sprite* lights;
  Sprite* light;
  Sprite* lightcone;

  Color   color;
};

#endif
