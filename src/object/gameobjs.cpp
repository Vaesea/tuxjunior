//  $Id: gameobjs.cpp 4716 2007-01-28 19:45:34Z grumbel $
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

#include <algorithm>
#include <iostream>
#include <cmath>

#include "tile.hpp"
#include "tile_manager.hpp"
#include "game_session.hpp"
#include "gameobjs.hpp"
#include "sprite/sprite_manager.hpp"
#include "sprite/sprite.hpp"
#include "resources.hpp"
#include "sector.hpp"
#include "tilemap.hpp"
#include "video/drawing_context.hpp"
#include "camera.hpp"
#include "main.hpp"
#include "random_generator.hpp"

BouncyCoin::BouncyCoin(const Vector& pos)
  : position(pos)
{
  timer.start(.3f);
  sprite = sprite_manager->create("images/objects/coin/coin.sprite");
  sprite->set_action("still");
}

BouncyCoin::~BouncyCoin()
{
  delete sprite;
}

void
BouncyCoin::update(float elapsed_time)
{
  position.y += -200 * elapsed_time;

  if(timer.check())
    remove_me();
}

void
BouncyCoin::draw(DrawingContext& context)
{
  sprite->draw(context, position, LAYER_OBJECTS + 5);
}

//---------------------------------------------------------------------------

BrokenBrick::BrokenBrick(Sprite* nsprite,
    const Vector& pos, const Vector& nmovement)
  : sprite(new Sprite(*nsprite)), position(pos), movement(nmovement)
{
  timer.start(.2f);
}

BrokenBrick::~BrokenBrick()
{
  delete sprite;
}

void
BrokenBrick::update(float elapsed_time)
{
  position += movement * elapsed_time;

  if (timer.check())
    remove_me();
}

void
BrokenBrick::draw(DrawingContext& context)
{
  sprite->draw_part(context,
      Vector(systemRandom.rand(16), systemRandom.rand(16)), Vector(16, 16),
      position, LAYER_OBJECTS + 1);
}

//---------------------------------------------------------------------------

FloatingText::FloatingText(const Vector& pos, const std::string& text_)
  : position(pos), text(text_)
{
  timer.start(.1f);
  position.x -= text.size() * 8;
}

FloatingText::FloatingText(const Vector& pos, int score)
  : position(pos)
{
  timer.start(.1f);

  // turn int into a string
  char str[10];
  snprintf(str, 10, "%d", score);
  text = str;

  position.x -= text.size() * 8;
}

void
FloatingText::update(float elapsed_time)
{
  position.y -= 1.4 * elapsed_time;

  if(timer.check())
    remove_me();
}

#define FADING_TIME .350

void
FloatingText::draw(DrawingContext& context)
{
  // make an alpha animation when disapearing
  int alpha;
  if(timer.get_timeleft() < FADING_TIME)
    alpha = int(timer.get_timeleft() * 255 / FADING_TIME);
  else
    alpha = 255;

  context.push_transform();
  context.set_alpha(alpha);

  context.draw_text(gold_text, text, position, ALIGN_LEFT, LAYER_OBJECTS+1);

  context.pop_transform();
}

Sprite *img_smoke_cloud = 0;

SmokeCloud::SmokeCloud(const Vector& pos)
  : position(pos)
{
  timer.start(.3f);
  sprite = sprite_manager->create("images/objects/particles/stomp.sprite");
}

SmokeCloud::~SmokeCloud()
{
  delete sprite;
}

void
SmokeCloud::update(float elapsed_time)
{
  position.y -= 120 * elapsed_time;

  if(timer.check())
    remove_me();
}

void
SmokeCloud::draw(DrawingContext& context)
{
  sprite->draw(context, position, LAYER_OBJECTS+1);
}
