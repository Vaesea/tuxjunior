//  $Id: pushbutton.hpp 4603 2007-01-19 13:37:44Z anmaster $
//
//  SuperTux - PushButton running a script
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

#ifndef TUXJUNIOR_BUTTON_H
#define TUXJUNIOR_BUTTON_H

#include "moving_sprite.hpp"
#include "lisp/lisp.hpp"

/**
 * PushButton - jump on it to run a script
 */
class PushButton : public MovingSprite
{
public:
  PushButton(const lisp::Lisp& reader);

  HitResponse collision(GameObject& other, const CollisionHit& hit);
  void update(float elapsed_time);

private:
  enum PushButtonState {
    OFF,
    ON
  };

  std::string script;
  PushButtonState state;
};

#endif
