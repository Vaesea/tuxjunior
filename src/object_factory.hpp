//  $Id: object_factory.hpp 5163 2007-10-07 19:25:34Z tuxdev $
//
//  SuperTux
//  Copyright (C) 2004 Ricardo Cruz <rick2@aeiou.pt>
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
#ifndef OBJECT_FACTORY_H
#define OBJECT_FACTORY_H

#include <string>
#include <map>

namespace lisp { class Lisp; }
class Vector;
class GameObject;

class Factory
{
public:
  virtual ~Factory()
  { }

  /** Creates a new gameobject from a lisp node.
   * Remember to delete the objects later
   */
  virtual GameObject* create_object(const lisp::Lisp& reader) = 0;

  typedef std::map<std::string, Factory*> Factories;
  static Factories &get_factories()
  {
    static Factories object_factories;
    return object_factories;
  }
};

GameObject* create_object(const std::string& name, const lisp::Lisp& reader);
GameObject* create_object(const std::string& name, const Vector& pos);

/** comment from Matze:
 * Yes I know macros are evil, but in this specific case they save
 * A LOT of typing and evil code duplication.
 * I'll happily accept alternatives if someone can present me one that does
 * not involve typing 4 or more lines for each object class
 */
#define IMPLEMENT_FACTORY(CLASS, NAME)                            \
class INTERN_##CLASS##Factory : public Factory                    \
{                                                                 \
public:                                                           \
  INTERN_##CLASS##Factory()                                       \
  {                                                               \
    get_factories()[NAME] = this;                                \
  }                                                               \
                                                                  \
  ~INTERN_##CLASS##Factory()                                      \
  {                                                               \
    get_factories().erase(NAME);                                 \
  }                                                               \
                                                                  \
  virtual GameObject* create_object(const lisp::Lisp& reader)     \
  {                                                               \
    return new CLASS(reader);                                     \
  }                                                               \
};                                                                \
static INTERN_##CLASS##Factory factory_##CLASS;

#endif
