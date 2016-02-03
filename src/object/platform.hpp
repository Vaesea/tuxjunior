//  $Id: platform.hpp 5064 2007-05-27 21:51:46Z sommer $
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

#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include <memory>
#include <string>
#include "object/moving_sprite.hpp"
#include "object/path.hpp"
#include "object/path_walker.hpp"
#include "script_interface.hpp"

/**
 * This class is the base class for platforms that tux can stand on
 */
class Platform : public MovingSprite, public ScriptInterface
{
public:
  Platform(const lisp::Lisp& reader);
  Platform(const Platform& platform);
  virtual Platform* clone() const { return new Platform(*this); }

  virtual HitResponse collision(GameObject& other, const CollisionHit& hit);
  virtual void update(float elapsed_time);

  const Vector& get_speed() const
  {
    return speed;
  }

  /**
   * @name Scriptable Methods
   * @{
   */

  /** Move platform until at given node, then stop */
  void goto_node(int node_no);

  /** Start moving platform */
  void start_moving();

  /** Stop platform at next node */
  void stop_moving();

  /**
   * @}
   */

  virtual void expose(HSQUIRRELVM vm, SQInteger table_idx);
  virtual void unexpose(HSQUIRRELVM vm, SQInteger table_idx);

  Path& get_path() {
    return *path.get();
  }

private:
  std::auto_ptr<Path> path;
  std::auto_ptr<PathWalker> walker;

  Vector speed;

  bool automatic; /**< true if Platform will automatically pick a destination based on collisions and current Player position */
  bool player_contact; /**< true if a Player touched the Platform during the last round of collision detections */
  bool last_player_contact; /**< true if a Player touched the Platform during the round before the last round of collision detections */

};

#endif
