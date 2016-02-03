//  $Id: root.hpp 5034 2007-05-26 17:42:23Z sommer $
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
#ifndef __ROOT_H__
#define __ROOT_H__

#include <memory>
#include "badguy.hpp"

class Timer;

class Root : public BadGuy
{
public:
  Root(const Vector& pos);
  ~Root();

  void activate();
  void deactivate();
  void active_update(float elapsed_time);
  virtual void draw(DrawingContext& context);
  virtual bool is_flammable() const { return false; }
  virtual bool is_freezable() const { return false; }
  virtual void kill_fall() { }

protected:
  enum MyState {
    STATE_APPEARING, STATE_HATCHING, STATE_GROWING, STATE_SHRINKING, STATE_VANISHING
  };
  MyState mystate;
  std::auto_ptr<Sprite> base_sprite;
  float offset_y;
  Timer hatch_timer;
};

#endif
