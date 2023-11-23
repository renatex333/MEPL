/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_ELEGANT_PARSER_TAB_H_INCLUDED
# define YY_YY_ELEGANT_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    T_GREETINGS = 258,             /* T_GREETINGS  */
    T_INTRODUCE = 259,             /* T_INTRODUCE  */
    T_AS = 260,                    /* T_AS  */
    T_INTEGER_TYPE = 261,          /* T_INTEGER_TYPE  */
    T_STRING_TYPE = 262,           /* T_STRING_TYPE  */
    T_DECLARE_VALUE = 263,         /* T_DECLARE_VALUE  */
    T_ASSIGN = 264,                /* T_ASSIGN  */
    T_ASSIGN_VALUE = 265,          /* T_ASSIGN_VALUE  */
    T_CONDITIONAL = 266,           /* T_CONDITIONAL  */
    T_HOLDS_TRUE = 267,            /* T_HOLDS_TRUE  */
    T_OTHERWISE = 268,             /* T_OTHERWISE  */
    T_WHILST = 269,                /* T_WHILST  */
    T_INQUIRE = 270,               /* T_INQUIRE  */
    T_DISPLAY = 271,               /* T_DISPLAY  */
    T_FIRSTLY = 272,               /* T_FIRSTLY  */
    T_CONCLUSION = 273,            /* T_CONCLUSION  */
    T_OR = 274,                    /* T_OR  */
    T_AND = 275,                   /* T_AND  */
    T_EQUIVALENCE = 276,           /* T_EQUIVALENCE  */
    T_GREATER = 277,               /* T_GREATER  */
    T_LESSER = 278,                /* T_LESSER  */
    T_ADDITION = 279,              /* T_ADDITION  */
    T_SUBTRACTION = 280,           /* T_SUBTRACTION  */
    T_CONCATENATION = 281,         /* T_CONCATENATION  */
    T_MULTIPLICATION = 282,        /* T_MULTIPLICATION  */
    T_DIVISON = 283,               /* T_DIVISON  */
    T_POSITIVELY = 284,            /* T_POSITIVELY  */
    T_NEGATIVELY = 285,            /* T_NEGATIVELY  */
    T_NOT = 286,                   /* T_NOT  */
    T_IDENTIFIER = 287,            /* T_IDENTIFIER  */
    T_STRING = 288,                /* T_STRING  */
    T_NUMBER = 289,                /* T_NUMBER  */
    T_NEW_SENTENCE = 290           /* T_NEW_SENTENCE  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_ELEGANT_PARSER_TAB_H_INCLUDED  */
