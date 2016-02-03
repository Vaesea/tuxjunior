//  $Id: endsequence.hpp 4719 2007-01-28 20:35:11Z sommer $
//
//  SuperTux - End Sequence
//  Copyright (C) 2007 Christoph Sommer <christoph.sommer@2006.expires.deltadevelopment.de>
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

#ifndef __ENDSEQUENCE_H__
#define __ENDSEQUENCE_H__

#include <memory>
#include "game_object.hpp"
#include "timer.hpp"
#include "lisp/lisp.hpp"
#include "control/codecontroller.hpp"

class EndSequence : public GameObject
{
public:
    EndSequence();
    virtual ~EndSequence();

    virtual void update(float elapsed_time);
    virtual void draw(DrawingContext& context);

    void start(); /**< play EndSequence */
    void stop_tux(); /**< called when Tux has reached his final position */
    void stop(); /**< stop playing EndSequence, mark it as done playing */
    bool is_tux_stopped(); /**< returns true if Tux has reached his final position */
    bool is_done(); /**< returns true if EndSequence has finished playing */

protected:
    virtual void starting(); /**< called when EndSequence starts */
    virtual void running(float elapsed_time); /**< called while the EndSequence is running */
    virtual void stopping(); /**< called when EndSequence stops */

    bool isrunning; /**< true while EndSequence plays */
    bool isdone; /**< true if EndSequence has finished playing */
    bool tux_may_walk; /**< true while tux is allowed to walk */
    CodeController* end_sequence_controller;

};

#endif
