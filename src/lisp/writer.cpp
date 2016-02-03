//  $Id: writer.cpp 4982 2007-04-15 21:35:52Z wolfgangb $
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

#include <iostream>

#include "writer.hpp"
#include "physfs/physfs_stream.hpp"
#include "log.hpp"

namespace lisp
{

Writer::Writer(const std::string& filename)
{
  out = new OFileStream(filename);
  out_owned = true;
  indent_depth = 0;
  out->precision(10);
}

Writer::Writer(std::ostream* newout)
{
  out = newout;
  out_owned = false;
  indent_depth = 0;
  out->precision(10);
}

Writer::~Writer()
{
  if(lists.size() > 0) {
    log_warning << "Not all sections closed in lispwriter" << std::endl;
  }
  if(out_owned)
    delete out;
}

void
Writer::write_comment(const std::string& comment)
{
  *out << "; " << comment << "\n";
}

void
Writer::start_list(const std::string& listname, bool string)
{
  indent();
  *out << '(';
  if(string)
    write_escaped_string(listname);
  else
    *out << listname;
  *out << '\n';
  indent_depth += 2;

  lists.push_back(listname);
}

void
Writer::end_list(const std::string& listname)
{
  if(lists.size() == 0) {
    log_warning << "Trying to close list '" << listname << "', which is not open" << std::endl;
    return;
  }
  if(lists.back() != listname) {
    log_warning << "trying to close list '" << listname << "' while list '" << lists.back() << "' is open" << std::endl;
    return;
  }
  lists.pop_back();

  indent_depth -= 2;
  indent();
  *out << ")\n";
}

void
Writer::write_int(const std::string& name, int value)
{
  indent();
  *out << '(' << name << ' ' << value << ")\n";
}

void
Writer::write_float(const std::string& name, float value)
{
  indent();
  *out << '(' << name << ' ' << value << ")\n";
}

void
Writer::write_string(const std::string& name, const std::string& value,
    bool translatable)
{
  indent();
  *out << '(' << name;
  if(translatable) {
    *out << " (_ ";
    write_escaped_string(value);
    *out << "))\n";
  } else {
    *out << " ";
    write_escaped_string(value);
    *out << ")\n";
  }
}

void
Writer::write_bool(const std::string& name, bool value)
{
  indent();
  *out << '(' << name << ' ' << (value ? "#t" : "#f") << ")\n";
}

void
Writer::write_int_vector(const std::string& name,
    const std::vector<int>& value)
{
  indent();
  *out << '(' << name;
  for(std::vector<int>::const_iterator i = value.begin(); i != value.end(); ++i)
    *out << " " << *i;
  *out << ")\n";
}

void
Writer::write_int_vector(const std::string& name,
    const std::vector<unsigned int>& value)
{
  indent();
  *out << '(' << name;
  for(std::vector<unsigned int>::const_iterator i = value.begin(); i != value.end(); ++i)
    *out << " " << *i;
  *out << ")\n";
}

void
Writer::write_float_vector(const std::string& name,
                           const std::vector<float>& value)
{
  indent();
  *out << '(' << name;
  for(std::vector<float>::const_iterator i = value.begin(); i != value.end(); ++i)
    *out << " " << *i;
  *out << ")\n";
}

void
Writer::write_escaped_string(const std::string& str)
{
  *out << '"';
  for(const char* c = str.c_str(); *c != 0; ++c) {
    if(*c == '\"')
      *out << "\\\"";
    else if(*c == '\\')
      *out << "\\\\";
    else
      *out << *c;
  }
  *out << '"';
}

void
Writer::indent()
{
  for(int i = 0; i<indent_depth; ++i)
    *out << ' ';
}

} // end of namespace lisp
