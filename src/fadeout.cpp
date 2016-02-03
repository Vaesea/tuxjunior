//  $Id: fadeout.cpp 4063 2006-07-21 21:05:23Z anmaster $
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
#include <config.h>

#include "fadeout.hpp"
#include "main.hpp"
#include "video/drawing_context.hpp"

FadeOut::FadeOut(float fade_time, Color color)
    : color(color), fade_time(fade_time), accum_time(0)
{
}

FadeOut::~FadeOut()
{
}

void
FadeOut::update(float elapsed_time)
{
  accum_time += elapsed_time;
  if(accum_time > fade_time)
    accum_time = fade_time;
}

void
FadeOut::draw(DrawingContext& context)
{
  Color col = color;
  col.alpha = accum_time / fade_time;
  context.draw_filled_rect(Vector(0, 0),
                           Vector(SCREEN_WIDTH, SCREEN_HEIGHT),
                           col, LAYER_GUI+1);
}

bool
FadeOut::done()
{
  return accum_time >= fade_time;
}
