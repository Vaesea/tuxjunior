//  $Id: spawn_point.cpp 4063 2006-07-21 21:05:23Z anmaster $
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

#include <config.h>

#include <stdexcept>
#include <iostream>
#include "spawn_point.hpp"
#include "lisp/lisp.hpp"
#include "lisp/list_iterator.hpp"
#include "log.hpp"

SpawnPoint::SpawnPoint()
{}

SpawnPoint::SpawnPoint(const SpawnPoint& other)
    : name(other.name), pos(other.pos)
{}

SpawnPoint::SpawnPoint(const lisp::Lisp* slisp)
{
    pos.x = -1;
    pos.y = -1;
    lisp::ListIterator iter(slisp);
    while(iter.next()) {
        const std::string& token = iter.item();
        if(token == "name") {
            iter.value()->get(name);
        } else if(token == "x") {
            iter.value()->get(pos.x);
        } else if(token == "y") {
            iter.value()->get(pos.y);
        } else {
            log_warning << "unknown token '" << token << "' in SpawnPoint" << std::endl;
        }
    }

    if(name == "")
        throw std::runtime_error("No name specified for spawnpoint");
    if(pos.x < 0 || pos.y < 0)
        throw std::runtime_error("Invalid coordinates for spawnpoint");
}
