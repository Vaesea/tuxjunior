//  $Id: block.hpp 4707 2007-01-28 16:32:42Z ravualhemio $
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

#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "moving_object.hpp"
#include "lisp/lisp.hpp"

class Sprite;
class Player;

class Block : public MovingObject
{
public:
  Block(Sprite* sprite = 0);
  ~Block();

  virtual HitResponse collision(GameObject& other, const CollisionHit& hit);
  virtual void update(float elapsed_time);
  virtual void draw(DrawingContext& context);

protected:
  friend class FlipLevelTransformer;

  virtual void hit(Player& player) = 0;
  void start_bounce();
  void start_break();
  void break_me();

  Sprite* sprite;
  bool bouncing;
  bool breaking;
  float bounce_dir;
  float bounce_offset;
  float original_y;

};

class BonusBlock : public Block
{
public:
  BonusBlock(const Vector& pos, int data);
  BonusBlock(const lisp::Lisp& lisp);
  virtual ~BonusBlock();
  HitResponse collision(GameObject& other, const CollisionHit& hit);

  void try_open();

  enum Contents {
    CONTENT_COIN,
    CONTENT_FIREGROW,
    CONTENT_ICEGROW,
    CONTENT_STAR,
    CONTENT_1UP,
    CONTENT_CUSTOM
  };

  Contents contents;
protected:
  virtual void hit(Player& player);

private:
  MovingObject* object;
};

class Brick : public Block
{
public:
  Brick(const Vector& pos, int data);

  void try_break(bool playerhit = false);
  HitResponse collision(GameObject& other, const CollisionHit& hit);

protected:
  virtual void hit(Player& player);

private:
  bool breakable;
  int coin_counter;
};

#endif
