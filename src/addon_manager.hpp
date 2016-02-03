//  $Id: addon_manager.hpp 4958 2007-04-01 22:39:30Z sommer $
//
//  SuperTux - Add-on Manager
//  Copyright (C) 2007 Christoph Sommer <christoph.sommer@2007.expires.deltadevelopment.de>
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
//
#ifndef ADDON_MANAGER_H
#define ADDON_MANAGER_H

#include <string>
#include <vector>
#include "addon.hpp"

/**
 * Checks for, installs and removes Add-ons
 */
class AddonManager
{
public:
  /**
   * returns a list of installed Add-ons
   */
  std::vector<Addon> get_installed_addons() const;
  
  /**
   * returns a list of available Add-ons
   */
  std::vector<Addon> get_available_addons() const;

  /**
   * Download and install Add-on
   */
  void install(const Addon& addon);

  /**
   * Physically delete Add-on
   */
  void remove(const Addon& addon);

  static AddonManager& get_instance();

protected:
  AddonManager();
  ~AddonManager();
};

#endif
