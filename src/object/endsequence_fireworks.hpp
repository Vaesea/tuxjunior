//  $Id: endsequence_fireworks.hpp 4729 2007-01-29 14:07:11Z anmaster $
//
//  SuperTux - End Sequence: Tux walks right
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

#ifndef __ENDSEQUENCE_FIREWORKS_H__
#define __ENDSEQUENCE_FIREWORKS_H__

#include <memory>
#include "object/endsequence.hpp"
#include "timer.hpp"

class EndSequenceFireworks : public EndSequence
{
public:
    EndSequenceFireworks();
    virtual ~EndSequenceFireworks();
    virtual void draw(DrawingContext& context);

protected:
    virtual void starting(); /**< called when EndSequence starts */
    virtual void running(float elapsed_time); /**< called while the EndSequence is running */
    virtual void stopping(); /**< called when EndSequence stops */

    Timer endsequence_timer;
};

#endif
