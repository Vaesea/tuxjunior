//  $Id: switch.hpp 4063 2006-07-21 21:05:23Z anmaster $
//
//  SuperTux - Switch Trigger
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
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#ifndef TUXJUNIOR_SWITCH_H
#define TUXJUNIOR_SWITCH_H

#include <string>

#include "trigger_base.hpp"
#include "serializable.hpp"
#include "lisp/lisp.hpp"
#include "lisp/writer.hpp"
#include "video/drawing_context.hpp"
#include "sprite/sprite.hpp"

class Switch : public TriggerBase, public Serializable
{
public:
  Switch(const lisp::Lisp& reader);
  virtual ~Switch();

  virtual void write(lisp::Writer& writer);

  virtual void update(float elapsed_time);
  virtual void draw(DrawingContext& context);
  virtual void event(Player& player, EventType type);

private:
  enum SwitchState {
    OFF,
    TURN_ON,
    ON,
    TURN_OFF
  };

  std::string sprite_name;
  Sprite* sprite;
  std::string script;

  SwitchState state;

};

#endif
