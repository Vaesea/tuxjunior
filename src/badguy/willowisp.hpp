//  $Id: willowisp.hpp 5060 2007-05-27 10:46:08Z matzeb $
//
//  SuperTux - "Will-O-Wisp" Badguy
//  Copyright (C) 2006 Christoph Sommer <christoph.sommer@2006.expires.deltadevelopment.de>
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

#ifndef __WILLOWISP_H__
#define __WILLOWISP_H__

#include "badguy.hpp"
#include "object/path.hpp"
#include "object/path_walker.hpp"
#include "script_interface.hpp"
#include "scripting/willowisp.hpp"

class WillOWisp : public BadGuy, public Scripting::WillOWisp,
                  public ScriptInterface
{
public:
  WillOWisp(const lisp::Lisp& reader);

  void activate();
  void deactivate();

  void active_update(float elapsed_time);
  virtual bool is_flammable() const { return false; }
  virtual bool is_freezable() const { return false; }
  virtual void kill_fall() { vanish(); }

  /**
   * make WillOWisp vanish
   */
  void vanish();

  virtual void draw(DrawingContext& context);

  virtual void goto_node(int node_no);
  virtual void set_state(const std::string& state);
  virtual void start_moving();
  virtual void stop_moving();

  virtual void expose(HSQUIRRELVM vm, SQInteger table_idx);
  virtual void unexpose(HSQUIRRELVM vm, SQInteger table_idx);

protected:
  virtual bool collides(GameObject& other, const CollisionHit& hit);
  HitResponse collision_player(Player& player, const CollisionHit& hit);

private:
  enum MyState {
    STATE_STOPPED, STATE_IDLE, STATE_TRACKING, STATE_VANISHING, STATE_WARPING,
    STATE_PATHMOVING, STATE_PATHMOVING_TRACK
  };
  MyState mystate;

  std::string target_sector;
  std::string target_spawnpoint;
  std::string hit_script;

  std::auto_ptr<SoundSource> sound_source;

  std::auto_ptr<Path>        path;
  std::auto_ptr<PathWalker>  walker;

  float flyspeed;
  float track_range;
  float vanish_range;
};

#endif
