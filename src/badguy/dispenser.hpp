//  $Id: dispenser.hpp 4435 2006-11-04 14:13:27Z sommer $
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

#ifndef __DISPENSER_H__
#define __DISPENSER_H__

#include "badguy.hpp"
#include "timer.hpp"

class Dispenser : public BadGuy
{
public:
  Dispenser(const lisp::Lisp& reader);

  void activate();
  void deactivate();
  void write(lisp::Writer& writer);
  void active_update(float elapsed_time);

  void freeze();
  void unfreeze();
  bool is_freezable() const;

  virtual Dispenser* clone() const { return new Dispenser(*this); }

protected:
  bool collision_squished(GameObject& object);
  void launch_badguy();
  float cycle;
  std::string badguy;
  Timer dispense_timer;
};

#endif
