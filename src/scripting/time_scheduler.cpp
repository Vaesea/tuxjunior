//  $Id: time_scheduler.cpp 4063 2006-07-21 21:05:23Z anmaster $
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
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
//  02111-1307, USA.
#include <config.h>

#include <algorithm>

#include "time_scheduler.hpp"
#include "squirrel_util.hpp"
#include "squirrel_error.hpp"
#include "log.hpp"

namespace Scripting
{

TimeScheduler* TimeScheduler::instance = NULL;

TimeScheduler::TimeScheduler()
{
}

TimeScheduler::~TimeScheduler()
{
}

void
TimeScheduler::update(float time)
{
  while(!schedule.empty() && schedule.front().wakeup_time < time) {
    HSQOBJECT thread_ref = schedule.front().thread_ref;

    sq_pushobject(global_vm, thread_ref);
    sq_getweakrefval(global_vm, -1);

    HSQUIRRELVM scheduled_vm;
    if(sq_gettype(global_vm, -1) == OT_THREAD &&
        SQ_SUCCEEDED(sq_getthread(global_vm, -1, &scheduled_vm))) {
      if(SQ_FAILED(sq_wakeupvm(scheduled_vm, SQFalse, SQFalse, SQTrue))) {
        std::ostringstream msg;
        msg << "Couldn't wakeup scheduled squirrel VM: ";
        sq_getlasterror(scheduled_vm);
        if(sq_gettype(scheduled_vm, -1) != OT_STRING) {
            msg << "(no info)";
        } else {
            const char* lasterr;
            sq_getstring(scheduled_vm, -1, &lasterr);
            msg << lasterr;
        }
        log_warning << msg.str() << std::endl;
        sq_pop(scheduled_vm, 1);
      }
    }

    sq_release(global_vm, &thread_ref);
    sq_pop(global_vm, 2);

    std::pop_heap(schedule.begin(), schedule.end());
    schedule.pop_back();
  }
}

void
TimeScheduler::schedule_thread(HSQUIRRELVM scheduled_vm, float time)
{
  // create a weakref to the VM
  SQObject vm_obj = vm_to_object(scheduled_vm);
  sq_pushobject(global_vm, vm_obj);
  sq_weakref(global_vm, -1);

  ScheduleEntry entry;
  if(SQ_FAILED(sq_getstackobj(global_vm, -1, & entry.thread_ref))) {
    sq_pop(global_vm, 2);
    throw SquirrelError(global_vm, "Couldn't get thread weakref from vm");
  }
  entry.wakeup_time = time;

  sq_addref(global_vm, & entry.thread_ref);
  sq_pop(global_vm, 2);

  schedule.push_back(entry);
  std::push_heap(schedule.begin(), schedule.end());
}

}
