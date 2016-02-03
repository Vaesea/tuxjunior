//  $Id: ghosttree.hpp 5040 2007-05-26 20:37:50Z sommer $
//
//  SuperTux - Boss "GhostTree"
//  Copyright (C) 2007 Matthias Braun <matze@braunis.de>
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
#ifndef __GHOSTTREE_H__
#define __GHOSTTREE_H__
#include <config.h>
#include <algorithm>
#include <vector>
#include "badguy.hpp"

class TreeWillOWisp;
class Lantern;

class GhostTree : public BadGuy
{
public:
  GhostTree(const lisp::Lisp& lisp);
  ~GhostTree();

  virtual bool is_flammable() const { return false; }
  virtual bool is_freezable() const { return false; }
  virtual void kill_fall() { }

  void activate();
  void active_update(float elapsed_time);
  void willowisp_died(TreeWillOWisp* willowisp);
  virtual void draw(DrawingContext& context);

  virtual bool collides(GameObject& other, const CollisionHit& hit);
  virtual HitResponse collision(GameObject& other, const CollisionHit& hit);

  void die();

private:
  enum MyState {
    STATE_IDLE, STATE_SUCKING, STATE_SWALLOWING, STATE_DYING
  };
  MyState mystate;
  Timer willowisp_timer;
  float willo_spawn_y;
  float willo_radius;
  float willo_speed;
  int   willo_color;

  std::auto_ptr<Sprite> glow_sprite;
  Timer colorchange_timer;
  Timer suck_timer;
  Timer root_timer;
  int   treecolor;
  Color suck_lantern_color;

  Lantern* suck_lantern; /**< Lantern that is currently being sucked in */

  std::vector<TreeWillOWisp*> willowisps;

  bool is_color_deadly(Color color) const;
  void spawn_lantern();
};

#endif

