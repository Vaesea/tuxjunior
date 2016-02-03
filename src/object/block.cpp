//  $Id: block.cpp 5103 2007-06-13 18:27:37Z sommer $
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

#include "block.hpp"
#include "log.hpp"

#include <stdexcept>

#include "resources.hpp"
#include "player.hpp"
#include "sector.hpp"
#include "sprite/sprite.hpp"
#include "sprite/sprite_manager.hpp"
#include "video/drawing_context.hpp"
#include "lisp/lisp.hpp"
#include "gameobjs.hpp"
#include "portable.hpp"
#include "specialriser.hpp"
#include "growup.hpp"
#include "flower.hpp"
#include "oneup.hpp"
#include "star.hpp"
#include "player_status.hpp"
#include "badguy/badguy.hpp"
#include "coin.hpp"
#include "object_factory.hpp"
#include "lisp/list_iterator.hpp"
#include "object_factory.hpp"
#include "level.hpp"

static const float BOUNCY_BRICK_MAX_OFFSET = 8;
static const float BOUNCY_BRICK_SPEED = 90;
static const float EPSILON = .0001f;

Block::Block(Sprite* newsprite)
  : sprite(newsprite), bouncing(false), breaking(false), bounce_dir(0), bounce_offset(0)
{
  bbox.set_size(32, 32.1f);
  set_group(COLGROUP_STATIC);
  sound_manager->preload("sounds/upgrade.wav");
  sound_manager->preload("sounds/brick.wav");
}

Block::~Block()
{
  delete sprite;
}

HitResponse
Block::collision(GameObject& other, const CollisionHit& )
{
  Player* player = dynamic_cast<Player*> (&other);
  if(player) {
    if(player->get_bbox().get_top() > get_bbox().get_bottom() - 7.0) {
      hit(*player);
    }
  }

  // only interact with other objects if...
  //   1) we are bouncing
  // and
  //   2) the object is not portable (either never or not currently)
  Portable* portable = dynamic_cast<Portable*> (&other);
  if(bouncing && (portable == 0 || (!portable->is_portable()))) {

    // Badguys get killed
    BadGuy* badguy = dynamic_cast<BadGuy*> (&other);
    if(badguy) {
      badguy->kill_fall();
    }

    // Coins get collected
    Coin* coin = dynamic_cast<Coin*> (&other);
    if(coin) {
      coin->collect();
    }

  }

  return SOLID;
}

void
Block::update(float elapsed_time)
{
  if(!bouncing)
    return;

  float offset = original_y - get_pos().y;
  if(offset > BOUNCY_BRICK_MAX_OFFSET) {
    bounce_dir = BOUNCY_BRICK_SPEED;
    movement = Vector(0, bounce_dir * elapsed_time);
    if(breaking){
      break_me();
    }
  } else if(offset < BOUNCY_BRICK_SPEED * elapsed_time && bounce_dir > 0) {
    movement = Vector(0, offset);
    bounce_dir = 0;
    bouncing = false;
  } else {
    movement = Vector(0, bounce_dir * elapsed_time);
  }
}

void
Block::draw(DrawingContext& context)
{
  sprite->draw(context, get_pos(), LAYER_OBJECTS+1);
}

void
Block::start_bounce()
{
  original_y = bbox.p1.y;
  bouncing = true;
  bounce_dir = -BOUNCY_BRICK_SPEED;
  bounce_offset = 0;
}

void
Block::start_break()
{
  start_bounce();
  breaking = true;
}

//---------------------------------------------------------------------------

BonusBlock::BonusBlock(const Vector& pos, int data)
  : Block(sprite_manager->create("images/objects/bonus_block/bonusblock.sprite")), object(0)
{
  bbox.set_pos(pos);
  sprite->set_action("normal");
  switch(data) {
    case 1: contents = CONTENT_COIN; break;
    case 2: contents = CONTENT_FIREGROW; break;
    case 3: contents = CONTENT_STAR; break;
    case 4: contents = CONTENT_1UP; break;
    case 5: contents = CONTENT_ICEGROW; break;
    default:
      log_warning << "Invalid box contents" << std::endl;
      contents = CONTENT_COIN;
      break;
  }
}

BonusBlock::BonusBlock(const lisp::Lisp& lisp)
  : Block(sprite_manager->create("images/objects/bonus_block/bonusblock.sprite"))
{
  Vector pos;

  contents = CONTENT_COIN;
  lisp::ListIterator iter(&lisp);
  while(iter.next()) {
    const std::string& token = iter.item();
    if(token == "x") {
      iter.value()->get(pos.x);
    } else if(token == "y") {
      iter.value()->get(pos.y);
    } else if(token == "contents") {
      std::string contentstring;
      iter.value()->get(contentstring);
      if(contentstring == "coin") {
        contents = CONTENT_COIN;
      } else if(contentstring == "firegrow") {
        contents = CONTENT_FIREGROW;
      } else if(contentstring == "icegrow") {
        contents = CONTENT_ICEGROW;
      } else if(contentstring == "star") {
        contents = CONTENT_STAR;
      } else if(contentstring == "1up") {
        contents = CONTENT_1UP;
      } else if(contentstring == "custom") {
        contents = CONTENT_CUSTOM;
      } else {
        log_warning << "Invalid box contents '" << contentstring << "'" << std::endl;
      }
    } else {
      if(contents == CONTENT_CUSTOM) {
        GameObject* game_object = create_object(token, *(iter.lisp()));
        object = dynamic_cast<MovingObject*> (game_object);
        if(object == 0)
          throw std::runtime_error(
            "Only MovingObjects are allowed inside BonusBlocks");
      } else {
        log_warning << "Invalid element '" << token << "' in bonusblock" << std::endl;
      }
    }
  }

  if(contents == CONTENT_CUSTOM && object == 0)
    throw std::runtime_error("Need to specify content object for custom block");

  bbox.set_pos(pos);
}

BonusBlock::~BonusBlock()
{
  delete object;
}

void
BonusBlock::hit(Player& )
{
  try_open();
}

HitResponse
BonusBlock::collision(GameObject& other, const CollisionHit& hit){
    BadGuy* badguy = dynamic_cast<BadGuy*> (&other);
    if(badguy) {
      // hit contains no information for collisions with blocks.
      // Badguy's bottom has to be below the top of the bonusblock
      // +7 is required to slide over one tile gaps.
      if( badguy->can_break() && ( badguy->get_bbox().get_bottom() > get_bbox().get_top() + 7.0) ){
        try_open();
      }
    }
    Portable* portable = dynamic_cast<Portable*> (&other);
    if(portable) {
      MovingObject* moving = dynamic_cast<MovingObject*> (&other);
      if(moving->get_bbox().get_top() > get_bbox().get_bottom() - 7.0) {
        try_open();
      }
    }
    return Block::collision(other, hit);
}

void
BonusBlock::try_open()
{
  if(sprite->get_action() == "empty") {
    sound_manager->play("sounds/brick.wav");
    return;
  }

  Sector* sector = Sector::current();
  assert(sector);
  assert(sector->player);
  Player& player = *(sector->player);
  Direction direction = (player.get_bbox().get_middle().x > get_bbox().get_middle().x) ? LEFT : RIGHT;

  switch(contents) {
    case CONTENT_COIN:
      Sector::current()->add_object(new BouncyCoin(get_pos()));
      player.get_status()->add_coins(1);
      Sector::current()->get_level()->stats.coins++;
      break;

    case CONTENT_FIREGROW:
      if(player.get_status()->bonus == NO_BONUS) {
        SpecialRiser* riser = new SpecialRiser(get_pos(), new GrowUp(direction));
        sector->add_object(riser);
      } else {
        SpecialRiser* riser = new SpecialRiser(
            get_pos(), new Flower(FIRE_BONUS));
        sector->add_object(riser);
      }
      sound_manager->play("sounds/upgrade.wav");
      break;

    case CONTENT_ICEGROW:
      if(player.get_status()->bonus == NO_BONUS) {
        SpecialRiser* riser = new SpecialRiser(get_pos(), new GrowUp(direction));
        sector->add_object(riser);
      } else {
        SpecialRiser* riser = new SpecialRiser(
            get_pos(), new Flower(ICE_BONUS));
        sector->add_object(riser);
      }
      sound_manager->play("sounds/upgrade.wav");
      break;

    case CONTENT_STAR:
      sector->add_object(new Star(get_pos() + Vector(0, -32), direction));
      break;

    case CONTENT_1UP:
      sector->add_object(new OneUp(get_pos(), direction));
      break;

    case CONTENT_CUSTOM:
      SpecialRiser* riser = new SpecialRiser(get_pos(), object);
      object = 0;
      sector->add_object(riser);
      sound_manager->play("sounds/upgrade.wav");
      break;
  }

  start_bounce();
  sprite->set_action("empty");
}

void
Block::break_me()
{
  Sector* sector = Sector::current();
  sector->add_object(
      new BrokenBrick(new Sprite(*sprite), get_pos(), Vector(-100, -400)));
  sector->add_object(
      new BrokenBrick(new Sprite(*sprite), get_pos() + Vector(0, 16),
        Vector(-150, -300)));
  sector->add_object(
      new BrokenBrick(new Sprite(*sprite), get_pos() + Vector(16, 0),
        Vector(100, -400)));
  sector->add_object(
      new BrokenBrick(new Sprite(*sprite), get_pos() + Vector(16, 16),
        Vector(150, -300)));
  remove_me();
}

IMPLEMENT_FACTORY(BonusBlock, "bonusblock");

//---------------------------------------------------------------------------

Brick::Brick(const Vector& pos, int data)
  : Block(sprite_manager->create("images/objects/bonus_block/brick.sprite")), breakable(false),
    coin_counter(0)
{
  bbox.set_pos(pos);
  if(data == 1)
    coin_counter = 5;
  else
    breakable = true;
}

void
Brick::hit(Player& )
{
  if(sprite->get_action() == "empty")
    return;

  try_break(true);
}

HitResponse
Brick::collision(GameObject& other, const CollisionHit& hit){
    BadGuy* badguy = dynamic_cast<BadGuy*> (&other);
    if(badguy) {
      // hit contains no information for collisions with blocks.
      // Badguy's bottom has to be below the top of the brick
      // +7 is required to slide over one tile gaps.
      if( badguy->can_break() && ( badguy->get_bbox().get_bottom() > get_bbox().get_top() + 7.0 ) ){
        try_break(false);
      }
    }
    Portable* portable = dynamic_cast<Portable*> (&other);
    if(portable) {
      MovingObject* moving = dynamic_cast<MovingObject*> (&other);
      if(moving->get_bbox().get_top() > get_bbox().get_bottom() - 7.0) {
        try_break();
      }
    }
   return Block::collision(other, hit);
}

void
Brick::try_break(bool playerhit)
{
  if(sprite->get_action() == "empty")
    return;

  sound_manager->play("sounds/brick.wav");
  Sector* sector = Sector::current();
  Player& player = *(sector->player);
  if(coin_counter > 0) {
    sector->add_object(new BouncyCoin(get_pos()));
    coin_counter--;
    player.get_status()->add_coins(1);
    if(coin_counter == 0)
      sprite->set_action("empty");
    start_bounce();
  } else if(breakable) {
    if(playerhit){
      if(player.is_big()){
        start_break();
        return;
      } else {
        start_bounce();
        return;
      }
    }
   break_me();
  }
}

//IMPLEMENT_FACTORY(Brick, "brick");
