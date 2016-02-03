//  $Id: file_system.cpp 4063 2006-07-21 21:05:23Z anmaster $
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

#include <config.h>

#include "log.hpp"
#include "file_system.hpp"

#include <string>
#include <vector>
#include <sstream>

namespace FileSystem
{

std::string dirname(const std::string& filename)
{
  std::string::size_type p = filename.find_last_of('/');
  if(p == std::string::npos)
    return "";

  return filename.substr(0, p+1);
}

std::string basename(const std::string& filename)
{
  std::string::size_type p = filename.find_last_of('/');
  if(p == std::string::npos)
    return filename;

  return filename.substr(p+1, filename.size()-p-1);
}

std::string strip_extension(const std::string& filename)
{
  std::string::size_type p = filename.find_last_of('.');
  if(p == std::string::npos)
    return filename;

  return filename.substr(0, p);
}

std::string normalize(const std::string& filename)
{
  std::vector<std::string> path_stack;

  const char* p = filename.c_str();

  while(true) {
    while(*p == '/') {
      p++;
      continue;
    }

    const char* pstart = p;
    while(*p != '/' && *p != 0) {
      ++p;
    }

    size_t len = p - pstart;
    if(len == 0)
      break;

    std::string pathelem(pstart, p-pstart);
    if(pathelem == ".")
      continue;

    if(pathelem == "..") {
      if(path_stack.empty()) {

        log_warning << "Invalid '..' in path '" << filename << "'" << std::endl;
        // push it into the result path so that the users sees his error...
        path_stack.push_back(pathelem);
      } else {
        path_stack.pop_back();
      }
    } else {
      path_stack.push_back(pathelem);
    }
  }

  // construct path
  std::ostringstream result;
  for(std::vector<std::string>::iterator i = path_stack.begin();
      i != path_stack.end(); ++i) {
    result << '/' << *i;
  }
  if(path_stack.empty())
    result << '/';

  return result.str();
}

}
