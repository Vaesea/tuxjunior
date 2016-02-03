//  $Id: obstackpp.hpp 4882 2007-02-28 18:16:37Z matzeb $
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
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
//  02111-1307, USA.
#ifndef OBSTACKPP_H_
#define OBSTACKPP_H_

#include "obstack.h"

inline void*
operator new (size_t bytes, struct obstack& obst)
{
  return obstack_alloc(&obst, bytes);
}

inline void*
operator new[] (size_t bytes, struct obstack& obst)
{
  return obstack_alloc(&obst, bytes);
}

static inline void* obstack_chunk_alloc(size_t size)
{
  return new char[size];
}

static inline void obstack_chunk_free(void* data)
{
  char* ptr = static_cast<char*> (data);
  delete[] ptr;
}

#endif

