//  $Id: parser.hpp 4882 2007-02-28 18:16:37Z matzeb $
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

#ifndef __LISPPARSER_H__
#define __LISPPARSER_H__

#include <string>
#include "lexer.hpp"
#include "obstack/obstack.h"

namespace TinyGetText {
class Dictionary;
class DictionaryManager;
}

namespace lisp
{

class Lisp;
class LispFile;

class Parser
{
public:
  Parser(bool translate = true);
  ~Parser();

  /**
   * Parses a lispfile and returns the s-expression structure.
   * Note that all memory is held by the parser so don't destroy the parser
   * before you are finished with the lisp tree
   */
  const Lisp* parse(const std::string& filename);
  /**
   * Same as parse but reads from a generic std::istream. The sourcename is
   * used for errormessages to indicate the source of the data.
   */
  const Lisp* parse(std::istream& stream, const std::string& sourcename);

private:
  void parse_error(const char* msg) const;
  const Lisp* read();

  Lexer* lexer;
  std::string filename;
  TinyGetText::DictionaryManager* dictionary_manager;
  TinyGetText::Dictionary* dictionary;
  Lexer::TokenType token;

  struct obstack obst;
};

} // end of namespace lisp

#endif
