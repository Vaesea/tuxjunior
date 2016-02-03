//  $Id: willowisp.hpp 5060 2007-05-27 10:46:08Z matzeb $
//
//  SuperTux
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

#ifndef __SCRIPTING_WILLOWISP_H__
#define __SCRIPTING_WILLOWISP_H__

namespace Scripting
{

class WillOWisp
{
public:
#ifndef SCRIPTING_API
  virtual ~WillOWisp()
  {}
#endif

  /** Move willowisp to given node */
  virtual void goto_node(int node_no) = 0;

  /** set willowisp state can be:
   * -stopped          willowisp doesn't move
   * -move_path        willowisp moves along the path (call goto_node)
   * -move_path_track  willowisp moves along path but catchs tux when he is near
   * -normal           "normal" mode starts tracking tux when he is near enough
   * -vanish           vanish
   */
  virtual void set_state(const std::string& state) = 0;

  virtual void start_moving() = 0;
  virtual void stop_moving() = 0;
};

}

#endif
