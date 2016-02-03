//  $Id: spiky.hpp 4188 2006-08-16 01:08:19Z sommer $
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

#ifndef __SPIKY_H__
#define __SPIKY_H__

#include "walking_badguy.hpp"

class Spiky : public WalkingBadguy
{
public:
  Spiky(const lisp::Lisp& reader);

  void write(lisp::Writer& writer);
  virtual Spiky* clone() const { return new Spiky(*this); }

  void freeze();
  bool is_freezable() const;

private:
};

#endif
