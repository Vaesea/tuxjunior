//  $Id: functions.hpp 4759 2007-01-31 17:07:21Z ravualhemio $
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

#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#ifndef SCRIPTING_API
#define __suspend
#define __custom
#include <string>
#include "player_status.hpp"
#endif

namespace Scripting
{

/**
 * Display the value of the argument. This is usefull for inspecting tables.
 */
SQInteger display(HSQUIRRELVM vm) __custom;

/**
 * Displays contents of the current stack
 */
void print_stacktrace(HSQUIRRELVM vm);

/**
 * returns the currently running thread
 */
SQInteger get_current_thread(HSQUIRRELVM vm) __custom;

/**
 * Display a text file and scrolls it over the screen (on next screenswitch)
 */
void display_text_file(const std::string& filename);

/**
 * Load and display a worldmap (on next screenswitch)
 */
void load_worldmap(const std::string& filename);

/**
 * Load and display a level (on next screenswitch)
 */
void load_level(const std::string& filename);

/**
 * Suspend the script execution for the specified number of seconds
 */
void wait(HSQUIRRELVM vm, float seconds) __suspend;

/**
 * Suspend the script execution until the current screen has been changed
 */
void wait_for_screenswitch(HSQUIRRELVM vm) __suspend;

/**
 * Exits the currently running screen (force exit from worldmap or scrolling
 * text for example)
 */
void exit_screen();

/**
 * Does a fadeout for the specified number of seconds before next screenchange
 */
void fadeout_screen(float seconds);

/**
 * Does a shrinking fade towards the destposition for the specified number of
 * seconds before next screenchange
 */
void shrink_screen(float dest_x, float dest_y, float seconds);

/**
 * Aborts any kind of previous screen fade; the screenchange will happen
 * anyway.
 */
void abort_screenfade();

/**
 * Translate a text into the users language (by looking it up in the .po
 * files)
 */
std::string translate(const std::string& text);

/**
 * Load a script file and executes it. This is typically used to import
 * functions from external files.
 */
void import(HSQUIRRELVM v, const std::string& filename);

/**
 * Save world state to savegame
 */
void save_state();

/**
 * Update worldmap from worldmap state (state.world variable)
 */
void update_worldmap();

/**
 * enable/disable drawing of collision rectangles
 */
void debug_collrects(bool enable);

/**
 * enable/disable drawing of fps
 */
void debug_show_fps(bool enable);

/**
 * enable/disable drawing of non-solid layers
 */
void debug_draw_solids_only(bool enable);

/**
 * Changes music to musicfile
 */
void play_music(const std::string& musicfile);

/**
 * Plays a soundfile
 */
void play_sound(const std::string& soundfile);

/**
 * speeds Tux up
 */
void grease();

/**
 * makes Tux invincible for 10000 units of time
 */
void invincible();

/**
 * makes Tux a ghost, i.e. lets him float around and through solid objects
 */
void ghost();

/**
 * recall Tux's invincibility and ghost status
 */
void mortal();

/**
 * reinitialise and respawn Tux at the beginning of the current level
 */
void restart();

/**
 * print Tux's current coordinates in a level
 */
void whereami();

/**
 * move Tux near the end of the level
 */
void gotoend();

/**
 * show the camera's coordinates
 */
void camera();

/**
 * exit the game
 */
void quit();

/**
 * Returns a random integer
 */
int rand();

}

#endif
