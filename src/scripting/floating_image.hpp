//  $Id: floating_image.hpp 4463 2006-12-16 14:47:31Z sommer $
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

#ifndef __FLOATING_IMAGE_HPP__
#define __FLOATING_IMAGE_HPP__

#ifndef SCRIPTING_API
#define __suspend
#include <string>
#include "ref.hpp"

class FloatingImage;
typedef FloatingImage _FloatingImage;
#endif

namespace Scripting
{

class FloatingImage
{
public:
  FloatingImage(const std::string& spritefile);
  ~FloatingImage();

  void set_layer(int layer);
  int get_layer();
  void set_pos(float x, float y);
  float get_pos_x();
  float get_pos_y();
  void set_anchor_point(int anchor);
  int get_anchor_point();
  void set_visible(bool visible);
  bool get_visible();
  void set_action(const std::string& action);
  std::string get_action();
  void fade_in(float fadetime);
  void fade_out(float fadetime);

#ifndef SCRIPTING_API
private:
  Ref<_FloatingImage> floating_image;
#endif
};

}

#endif
