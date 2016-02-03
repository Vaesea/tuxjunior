//  $Id: drawing_context.hpp 4986 2007-04-16 17:48:28Z matzeb $
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
#ifndef TUXJUNIOR_RENDERER_H
#define TUXJUNIOR_RENDERER_H

#include <vector>
#include <string>
#include <memory>

#include <stdint.h>

#include <SDL_video.h>

#include "glutil.hpp"
#include "obstack/obstack.h"
#include "math/vector.hpp"
#include "math/rect.hpp"
#include "surface.hpp"
#include "font.hpp"
#include "color.hpp"

class Surface;
class Texture;
struct DrawingRequest;

class Renderer
{
public:
  virtual ~Renderer() {}

  virtual void draw_surface(const DrawingRequest& request) = 0;
  virtual void draw_surface_part(const DrawingRequest& request) = 0;
  virtual void draw_gradient(const DrawingRequest& request) = 0;
  virtual void draw_filled_rect(const DrawingRequest& request)= 0;
  virtual void do_take_screenshot() = 0;
  virtual void flip() = 0;
};

#endif

