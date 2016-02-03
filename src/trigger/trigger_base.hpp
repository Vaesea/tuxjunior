//  $Id: trigger_base.hpp 4814 2007-02-05 20:41:23Z sommer $
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

#ifndef TUXJUNIOR_TRIGGER_BASE_H
#define TUXJUNIOR_TRIGGER_BASE_H

#include <list>
#include "moving_object.hpp"
#include "math/rect.hpp"
#include "sprite/sprite.hpp"
#include "object_remove_listener.hpp"

class Player;

/** This class is the base class for all objects you can interact with in some
 * way. There are several interaction types defined like touch and activate
 */
class TriggerBase : public MovingObject, public ObjectRemoveListener
{
public:
  enum EventType {
    EVENT_TOUCH,     /**< Object came into contact */
    EVENT_LOSETOUCH, /**< Lost contact with object */
    EVENT_ACTIVATE   /**< Action button pressed    */
  };

  TriggerBase();
  ~TriggerBase();

  void update(float elapsed_time);
  void draw(DrawingContext& context);
  HitResponse collision(GameObject& other, const CollisionHit& hit);

  /**
   * Receive trigger events
   */
  virtual void event(Player& player, EventType type) = 0;
  
  /**
   * Called by GameObject destructor of an object in losetouch_listeners
   */
  virtual void object_removed(GameObject* object);

private:
  Sprite* sprite;
  bool lasthit;
  bool hit;

  std::list<Player*> losetouch_listeners; /**< Players that will be informed when we lose touch with them */
};

#endif /*TUXJUNIOR_INTERACTIVE_OBJECT_H*/
