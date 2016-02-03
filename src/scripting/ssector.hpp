//  $Id: ssector.hpp 4174 2006-08-13 00:19:06Z wolfgangb $
//
//  SuperTux - Sector Scripting
//  Copyright (C) 2006 Wolfgang Becker <uafr@gmx.de>
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

#ifndef __SECTOR_H__
#define __SECTOR_H__

namespace Scripting
{

class SSector
{
public:
#ifndef SCRIPTING_API
    virtual ~SSector()
    {}
#endif
  virtual void set_ambient_light(float red, float green, float blue) = 0;
  virtual float get_ambient_red() = 0;
  virtual float get_ambient_green() = 0;
  virtual float get_ambient_blue() = 0;
};

}

#endif
