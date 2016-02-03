/* A Bison parser, made by GNU Bison 2.1.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     T_INT = 258,
     T_FLOAT = 259,
     T_STRING = 260,
     T_ID = 261,
     T_ATOMIC_TYPE = 262,
     T_NAMESPACEREF = 263,
     T_CLASS = 264,
     T_STRUCT = 265,
     T_STATIC = 266,
     T_SUSPEND = 267,
     T_CUSTOM = 268,
     T_CONST = 269,
     T_UNSIGNED = 270,
     T_SIGNED = 271,
     T_VOID = 272,
     T_BOOL = 273,
     T_CHAR = 274,
     T_SHORT = 275,
     T_LONG = 276,
     T_DOUBLE = 277,
     T_PUBLIC = 278,
     T_PROTECTED = 279,
     T_PRIVATE = 280,
     T_NAMESPACE = 281,
     T_DDCOL = 282
   };
#endif
/* Tokens.  */
#define T_INT 258
#define T_FLOAT 259
#define T_STRING 260
#define T_ID 261
#define T_ATOMIC_TYPE 262
#define T_NAMESPACEREF 263
#define T_CLASS 264
#define T_STRUCT 265
#define T_STATIC 266
#define T_SUSPEND 267
#define T_CUSTOM 268
#define T_CONST 269
#define T_UNSIGNED 270
#define T_SIGNED 271
#define T_VOID 272
#define T_BOOL 273
#define T_CHAR 274
#define T_SHORT 275
#define T_LONG 276
#define T_DOUBLE 277
#define T_PUBLIC 278
#define T_PROTECTED 279
#define T_PRIVATE 280
#define T_NAMESPACE 281
#define T_DDCOL 282




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)

typedef union YYSTYPE {
    char*       str;
    int         ival;
    float       fval;
    Class*      _class;
    Function*   function;
    Field*      field;
    Type*       type;
    AtomicType* atomic_type;
    Namespace*  _namespace;
} YYSTYPE;
/* Line 1447 of yacc.c.  */

# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif





