//  $Id: display_effect.hpp 4424 2006-10-28 00:45:41Z sommer $
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

#ifndef __OBJECT_DISPLAY_EFFECT_H__
#define __OBJECT_DISPLAY_EFFECT_H__

#include "scripting/display_effect.hpp"
#include "game_object.hpp"
#include "script_interface.hpp"

class DisplayEffect : public GameObject, public Scripting::DisplayEffect,
                      public ScriptInterface
{
public:
    DisplayEffect(std::string name = "");
    virtual ~DisplayEffect();

    void expose(HSQUIRRELVM vm, SQInteger table_idx);
    void unexpose(HSQUIRRELVM vm, SQInteger table_idx);

    void update(float elapsed_time);
    void draw(DrawingContext& context);


    /** 
     * @name Scriptable Methods
     * @{ 
     */

    void fade_out(float fadetime);
    void fade_in(float fadetime);
    void set_black(bool enabled);
    bool is_black();
    void sixteen_to_nine(float fadetime);
    void four_to_three(float fadetime);

    /** 
     * @} 
     */

private:
    enum FadeType {
        NO_FADE, FADE_IN, FADE_OUT
    };
    FadeType screen_fade;
    float screen_fadetime;
    float screen_fading;
    FadeType border_fade;
    float border_fadetime;
    float border_fading;
    float border_size;

    bool black;
    bool borders;
};

#endif
