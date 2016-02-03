//  $Id: camera.hpp 5258 2008-01-06 02:52:24Z sommer $
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
#ifndef TUXJUNIOR_CAMERA_H
#define TUXJUNIOR_CAMERA_H

#include <vector>
#include <cassert>
#include <memory>

#include "math/vector.hpp"
#include "game_object.hpp"
#include "video/drawing_context.hpp"
#include "serializable.hpp"
#include "timer.hpp"
#include "script_interface.hpp"

namespace lisp {
class Lisp;
}

class Sector;
class Path;
class PathWalker;
class CameraConfig;

class Camera : public GameObject, public Serializable, public ScriptInterface
{
public:
  Camera(Sector* sector, std::string name = "");
  virtual ~Camera();

  /// parse camera mode from lisp file
  void parse(const lisp::Lisp& reader);
  /// write camera mode to a lisp file
  virtual void write(lisp::Writer& writer);

  /// reset camera postion
  void reset(const Vector& tuxpos);

  /** return camera position */
  const Vector& get_translation() const;

  virtual void update(float elapsed_time);

  virtual void draw(DrawingContext& );

  virtual void expose(HSQUIRRELVM vm, SQInteger table_idx);
  virtual void unexpose(HSQUIRRELVM vm, SQInteger table_idx);

  // shake camera in a direction 1 time
  void shake(float speed, float x, float y);

  void set_scrolling(int scroll_x, int scroll_y)
  {
    translation.x = scroll_x;
    translation.y = scroll_y;
  }

  /**
   * scroll the upper left edge of the camera in scrolltime seconds
   * to the position goal
   */
  void scroll_to(const Vector& goal, float scrolltime);

  void reload_config();

  enum CameraMode
  {
    NORMAL, AUTOSCROLL, SCROLLTO, MANUAL
  };
  CameraMode mode;

  /**
   * get the coordinates of the point directly in the center of this camera
   */
  Vector get_center() const;

private:
  void update_scroll_normal(float elapsed_time);
  void update_scroll_autoscroll(float elapsed_time);
  void update_scroll_to(float elapsed_time);
  void keep_in_bounds(Vector& vector);
  void shake();

  /**
   * The camera basically provides lookeahead on the left or right side
   * or is undecided.
   */
  enum LookaheadMode {
    LOOKAHEAD_NONE, LOOKAHEAD_LEFT, LOOKAHEAD_RIGHT
  };

  Vector translation;

  Sector* sector;

  // normal mode
  LookaheadMode lookahead_mode;
  float changetime;
  float lookahead_pos;

  // autoscroll mode
  std::auto_ptr<Path> autoscroll_path;
  std::auto_ptr<PathWalker> autoscroll_walker;

  // shaking
  Timer shaketimer;
  float shakespeed;
  float shakedepth_x;
  float shakedepth_y;

  // scrollto mode
  Vector scroll_from;
  Vector scroll_goal;
  float scroll_to_pos;
  float scrollspeed;

  CameraConfig *config;
};

#endif /*TUXJUNIOR_CAMERA_H*/
