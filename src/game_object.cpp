//  $Id: game_object.cpp 4814 2007-02-05 20:41:23Z sommer $
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
#include "log.hpp"
#include "game_object.hpp"
#include "object_remove_listener.hpp"

GameObject::GameObject()
  : wants_to_die(false), remove_listeners(NULL)
{
}

GameObject::~GameObject()
{
  // call remove listeners (and remove them from the list)
  RemoveListenerListEntry* entry = remove_listeners;
  while(entry != NULL) {
    RemoveListenerListEntry* next = entry->next;
    entry->listener->object_removed(this);
    delete entry;
    entry = next;
  }
}

 
void 
GameObject::add_remove_listener(ObjectRemoveListener* listener)
{
  RemoveListenerListEntry* entry = new RemoveListenerListEntry();
  entry->next = remove_listeners;
  entry->listener = listener;
  remove_listeners = entry;
}

void
GameObject::del_remove_listener(ObjectRemoveListener* listener)
{
  RemoveListenerListEntry* entry = remove_listeners;
  if (entry->listener == listener) {
    remove_listeners = entry->next;
    delete entry;
    return;
  }
  RemoveListenerListEntry* next = entry->next;
  while(next != NULL) {
    if (next->listener == listener) {
      entry->next = next->next;
      delete next;
      break;
    }
    entry = next;
    next = next->next;
  }
}

