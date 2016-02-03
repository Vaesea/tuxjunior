//  $Id: level_time.hpp 4701 2007-01-28 13:23:57Z anmaster $
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

#ifndef __LEVELTIME_H__
#define __LEVELTIME_H__

#include <memory>
#include "game_object.hpp"
#include "timer.hpp"
#include "lisp/lisp.hpp"
#include "video/surface.hpp"
#include "script_interface.hpp"

class LevelTime : public GameObject, public ScriptInterface
{
public:
    LevelTime(const lisp::Lisp& reader);

    virtual void expose(HSQUIRRELVM vm, SQInteger table_idx);
    virtual void unexpose(HSQUIRRELVM vm, SQInteger table_idx);

    void update(float elapsed_time);
    void draw(DrawingContext& context);

    /**
     * @name Scriptable Methods
     * @{
     */

    /**
     * Resumes the countdown
     */
    void start();

    /**
     * Pauses the countdown
     */
    void stop();

    /**
     * Returns the number of seconds left on the clock
     */
    float get_time();

    /**
     * Changes the number of seconds left on the clock
     */
    void set_time(float time_left);

    /**
     * @}
     */

private:
    std::auto_ptr<Surface> time_surface;
    bool running;
    float time_left;
};

#endif
