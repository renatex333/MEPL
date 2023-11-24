/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "/home/renatex/Desktop/MEPL/compiler/src/parser/elegant_parser.y"

#define YYSTYPE PyObject *

#include <stdio.h>
#include <stdlib.h>
#include <Python.h>

void yyerror(const char *s);
extern int yylex(void);
extern char *yytext;
extern FILE *yyin;

PyObject *pRootNode = NULL;

PyObject *create_ast_node(const char *node_type, PyObject *args) {
    static PyObject *pModule = NULL;
    PyObject *pName = PyUnicode_FromString("compiler.src.semantic.AbstractSyntaxTreeNodes");
    if (!pModule) {
        pModule = PyImport_Import(pName);
        if (!pModule) {
            PyErr_Print();
            fprintf(stderr, "Failed to load 'AbstractSyntaxTreeNodes' module\n");
            return NULL;
        }
    }

    PyObject *pClass = PyObject_GetAttrString(pModule, node_type);
    if (!pClass || !PyCallable_Check(pClass)) {
        if (PyErr_Occurred())
            PyErr_Print();
        fprintf(stderr, "Failed to find class '%s'\n", node_type);
        Py_XDECREF(pClass);
        return NULL;
    }

    PyObject *pInstance = PyObject_CallObject(pClass, args);
    Py_DECREF(pClass);
    if (!pInstance) {
        PyErr_Print();
        fprintf(stderr, "Failed to create instance of '%s'\n", node_type);
        return NULL;
    }

    return pInstance;
}


#line 119 "elegant_parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "elegant_parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_T_GREETINGS = 3,                /* T_GREETINGS  */
  YYSYMBOL_T_INTRODUCE = 4,                /* T_INTRODUCE  */
  YYSYMBOL_T_AS = 5,                       /* T_AS  */
  YYSYMBOL_T_INTEGER_TYPE = 6,             /* T_INTEGER_TYPE  */
  YYSYMBOL_T_STRING_TYPE = 7,              /* T_STRING_TYPE  */
  YYSYMBOL_T_DECLARE_VALUE = 8,            /* T_DECLARE_VALUE  */
  YYSYMBOL_T_ASSIGN = 9,                   /* T_ASSIGN  */
  YYSYMBOL_T_ASSIGN_VALUE = 10,            /* T_ASSIGN_VALUE  */
  YYSYMBOL_T_CONDITIONAL = 11,             /* T_CONDITIONAL  */
  YYSYMBOL_T_HOLDS_TRUE = 12,              /* T_HOLDS_TRUE  */
  YYSYMBOL_T_OTHERWISE = 13,               /* T_OTHERWISE  */
  YYSYMBOL_T_WHILST = 14,                  /* T_WHILST  */
  YYSYMBOL_T_SOLICITATION = 15,            /* T_SOLICITATION  */
  YYSYMBOL_T_DISPLAY = 16,                 /* T_DISPLAY  */
  YYSYMBOL_T_FIRSTLY = 17,                 /* T_FIRSTLY  */
  YYSYMBOL_T_CONCLUSION = 18,              /* T_CONCLUSION  */
  YYSYMBOL_T_OR = 19,                      /* T_OR  */
  YYSYMBOL_T_AND = 20,                     /* T_AND  */
  YYSYMBOL_T_EQUIVALENCE = 21,             /* T_EQUIVALENCE  */
  YYSYMBOL_T_DIFFERENCE = 22,              /* T_DIFFERENCE  */
  YYSYMBOL_T_GREATER = 23,                 /* T_GREATER  */
  YYSYMBOL_T_LESSER = 24,                  /* T_LESSER  */
  YYSYMBOL_T_ADDITION = 25,                /* T_ADDITION  */
  YYSYMBOL_T_SUBTRACTION = 26,             /* T_SUBTRACTION  */
  YYSYMBOL_T_CONCATENATION = 27,           /* T_CONCATENATION  */
  YYSYMBOL_T_MULTIPLICATION = 28,          /* T_MULTIPLICATION  */
  YYSYMBOL_T_DIVISON = 29,                 /* T_DIVISON  */
  YYSYMBOL_T_POSITIVELY = 30,              /* T_POSITIVELY  */
  YYSYMBOL_T_NEGATIVELY = 31,              /* T_NEGATIVELY  */
  YYSYMBOL_T_NOT = 32,                     /* T_NOT  */
  YYSYMBOL_T_IDENTIFIER = 33,              /* T_IDENTIFIER  */
  YYSYMBOL_T_STRING = 34,                  /* T_STRING  */
  YYSYMBOL_T_NUMBER = 35,                  /* T_NUMBER  */
  YYSYMBOL_T_NEW_SENTENCE = 36,            /* T_NEW_SENTENCE  */
  YYSYMBOL_YYACCEPT = 37,                  /* $accept  */
  YYSYMBOL_ElegantConversation = 38,       /* ElegantConversation  */
  YYSYMBOL_Greeting = 39,                  /* Greeting  */
  YYSYMBOL_SentenceList = 40,              /* SentenceList  */
  YYSYMBOL_Sentence = 41,                  /* Sentence  */
  YYSYMBOL_Declare = 42,                   /* Declare  */
  YYSYMBOL_Identifier = 43,                /* Identifier  */
  YYSYMBOL_Type = 44,                      /* Type  */
  YYSYMBOL_OptionalValue = 45,             /* OptionalValue  */
  YYSYMBOL_Assign = 46,                    /* Assign  */
  YYSYMBOL_Conditional = 47,               /* Conditional  */
  YYSYMBOL_OptionalElse = 48,              /* OptionalElse  */
  YYSYMBOL_Loop = 49,                      /* Loop  */
  YYSYMBOL_Solicit = 50,                   /* Solicit  */
  YYSYMBOL_Display = 51,                   /* Display  */
  YYSYMBOL_Block = 52,                     /* Block  */
  YYSYMBOL_BlockSentenceList = 53,         /* BlockSentenceList  */
  YYSYMBOL_BooleanExpression = 54,         /* BooleanExpression  */
  YYSYMBOL_BooleanClause = 55,             /* BooleanClause  */
  YYSYMBOL_RelationalExpression = 56,      /* RelationalExpression  */
  YYSYMBOL_RelationalOp = 57,              /* RelationalOp  */
  YYSYMBOL_Expression = 58,                /* Expression  */
  YYSYMBOL_ArithmeticAddSubConcatOp = 59,  /* ArithmeticAddSubConcatOp  */
  YYSYMBOL_Term = 60,                      /* Term  */
  YYSYMBOL_ArithmeticMultDivOp = 61,       /* ArithmeticMultDivOp  */
  YYSYMBOL_Factor = 62,                    /* Factor  */
  YYSYMBOL_UnaryOp = 63                    /* UnaryOp  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  5
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   76

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  37
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  54
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  86

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   291


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    58,    58,    73,    75,    83,    88,    92,    93,    94,
      95,    96,    97,    99,   121,   138,   141,   145,   148,   152,
     172,   195,   198,   202,   222,   241,   260,   275,   278,   288,
     291,   311,   314,   334,   337,   357,   360,   363,   366,   370,
     373,   393,   396,   399,   403,   406,   426,   429,   433,   449,
     465,   483,   485,   488,   491
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "T_GREETINGS",
  "T_INTRODUCE", "T_AS", "T_INTEGER_TYPE", "T_STRING_TYPE",
  "T_DECLARE_VALUE", "T_ASSIGN", "T_ASSIGN_VALUE", "T_CONDITIONAL",
  "T_HOLDS_TRUE", "T_OTHERWISE", "T_WHILST", "T_SOLICITATION", "T_DISPLAY",
  "T_FIRSTLY", "T_CONCLUSION", "T_OR", "T_AND", "T_EQUIVALENCE",
  "T_DIFFERENCE", "T_GREATER", "T_LESSER", "T_ADDITION", "T_SUBTRACTION",
  "T_CONCATENATION", "T_MULTIPLICATION", "T_DIVISON", "T_POSITIVELY",
  "T_NEGATIVELY", "T_NOT", "T_IDENTIFIER", "T_STRING", "T_NUMBER",
  "T_NEW_SENTENCE", "$accept", "ElegantConversation", "Greeting",
  "SentenceList", "Sentence", "Declare", "Identifier", "Type",
  "OptionalValue", "Assign", "Conditional", "OptionalElse", "Loop",
  "Solicit", "Display", "Block", "BlockSentenceList", "BooleanExpression",
  "BooleanClause", "RelationalExpression", "RelationalOp", "Expression",
  "ArithmeticAddSubConcatOp", "Term", "ArithmeticMultDivOp", "Factor",
  "UnaryOp", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-56)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      12,   -15,    29,    26,   -56,   -56,   -56,     3,     3,    21,
      21,     3,    21,    34,   -56,   -56,   -56,   -56,   -56,   -56,
     -56,   -56,    39,    37,   -56,   -56,   -56,   -56,   -56,   -56,
      -5,    19,    36,    41,   -19,   -56,    21,     0,    10,   -14,
     -56,    27,    21,    44,    21,    21,   -56,   -56,   -56,   -56,
      21,   -56,   -56,   -56,    21,   -56,   -56,    21,   -56,    44,
     -56,   -56,   -56,   -56,    54,   -11,   -56,    50,    19,    36,
      41,   -19,   -56,   -56,    21,    33,   -56,     2,    44,   -56,
      51,   -56,    35,   -56,   -56,   -56
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     3,     1,     6,     0,     0,     0,
       0,     0,     0,     2,     5,     7,     8,     9,    10,    11,
      12,    14,     0,     0,    52,    53,    54,    49,    48,    51,
       0,    29,    31,    33,    39,    44,     0,     0,     0,     0,
       4,     0,     0,     0,     0,     0,    35,    36,    37,    38,
       0,    41,    42,    43,     0,    46,    47,     0,    50,     0,
      24,    25,    15,    16,    17,     0,    27,    21,    30,    32,
      34,    40,    45,    23,     0,     0,    19,     0,     0,    20,
      18,    13,     0,    28,    22,    26
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -56,   -56,   -56,   -56,   -12,   -56,    20,   -56,   -56,   -56,
     -56,   -56,   -56,   -56,   -56,   -55,   -56,   -10,    28,    30,
     -56,    23,   -56,    22,   -56,   -33,   -56
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     3,    13,    14,    15,    29,    64,    75,    16,
      17,    79,    18,    19,    20,    67,    77,    30,    31,    32,
      50,    33,    54,    34,    57,    35,    36
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      37,    40,    39,    58,    73,    44,     7,    43,    44,    55,
      56,     8,    59,     9,    44,     1,    10,    11,    12,    44,
      82,     4,    61,    84,    72,    76,     6,    22,    23,     5,
       7,    38,    65,    62,    63,     8,    21,     9,     7,    45,
      10,    11,    12,     8,    41,     9,    60,    42,    10,    11,
      12,    24,    25,    26,    21,    27,    28,    46,    47,    48,
      49,    66,    74,    78,    80,    83,    51,    52,    53,    81,
      44,    85,    68,    70,     0,    69,    71
};

static const yytype_int8 yycheck[] =
{
      10,    13,    12,    36,    59,    19,     4,    12,    19,    28,
      29,     9,    12,    11,    19,     3,    14,    15,    16,    19,
      18,    36,    36,    78,    57,    36,     0,     7,     8,     0,
       4,    11,    42,     6,     7,     9,    33,    11,     4,    20,
      14,    15,    16,     9,     5,    11,    36,    10,    14,    15,
      16,    30,    31,    32,    33,    34,    35,    21,    22,    23,
      24,    17,     8,    13,    74,    77,    25,    26,    27,    36,
      19,    36,    44,    50,    -1,    45,    54
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    38,    39,    36,     0,     0,     4,     9,    11,
      14,    15,    16,    40,    41,    42,    46,    47,    49,    50,
      51,    33,    43,    43,    30,    31,    32,    34,    35,    43,
      54,    55,    56,    58,    60,    62,    63,    54,    43,    54,
      41,     5,    10,    12,    19,    20,    21,    22,    23,    24,
      57,    25,    26,    27,    59,    28,    29,    61,    62,    12,
      36,    36,     6,     7,    44,    54,    17,    52,    55,    56,
      58,    60,    62,    52,     8,    45,    36,    53,    13,    48,
      54,    36,    18,    41,    52,    36
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    37,    38,    39,    40,    40,    40,    41,    41,    41,
      41,    41,    41,    42,    43,    44,    44,    45,    45,    46,
      47,    48,    48,    49,    50,    51,    52,    53,    53,    54,
      54,    55,    55,    56,    56,    57,    57,    57,    57,    58,
      58,    59,    59,    59,    60,    60,    61,    61,    62,    62,
      62,    62,    63,    63,    63
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     6,     1,     1,     1,     0,     2,     5,
       5,     0,     2,     4,     3,     3,     4,     0,     2,     1,
       3,     1,     3,     1,     3,     1,     1,     1,     1,     1,
       3,     1,     1,     1,     1,     3,     1,     1,     1,     1,
       2,     1,     1,     1,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* ElegantConversation: Greeting SentenceList  */
#line 58 "/home/renatex/Desktop/MEPL/compiler/src/parser/elegant_parser.y"
                                           {
    PyObject *pArgsList = PyList_New(0);
    PyObject *pValue = PyUnicode_FromString("ElegantConversation");

    PyList_Append(pArgsList, pValue);
    PyList_Append(pArgsList, yyvsp[0]);

    PyObject *pArgsTuple = PyList_AsTuple(pArgsList);
    pRootNode = create_ast_node("ElegantConversation", pArgsTuple);
    
    Py_DECREF(pArgsList);
    Py_DECREF(pValue);
    Py_DECREF(pArgsTuple);
}
#line 1242 "elegant_parser.tab.c"
    break;

  case 4: /* SentenceList: SentenceList Sentence  */
#line 75 "/home/renatex/Desktop/MEPL/compiler/src/parser/elegant_parser.y"
                                    {
    if (!PyList_Check(yyvsp[-1])) {
        yyerror("Expected a list as the first argument");
        yyval = NULL;
    } else {
        PyList_Append(yyvsp[-1], yyvsp[0]);
    }
}
#line 1255 "elegant_parser.tab.c"
    break;

  case 5: /* SentenceList: Sentence  */
#line 83 "/home/renatex/Desktop/MEPL/compiler/src/parser/elegant_parser.y"
                        {
    PyObject *singleSentenceList = PyList_New(1);
    PyList_SetItem(singleSentenceList, 0, yyvsp[0]); // $1 refers to the single Sentence node
    yyval = singleSentenceList;
}
#line 1265 "elegant_parser.tab.c"
    break;

  case 6: /* SentenceList: $end  */
#line 88 "/home/renatex/Desktop/MEPL/compiler/src/parser/elegant_parser.y"
                    {
    yyval = PyList_New(0); // Base case: an empty list
}
#line 1273 "elegant_parser.tab.c"
    break;

  case 13: /* Declare: T_INTRODUCE Identifier T_AS Type OptionalValue T_NEW_SENTENCE  */
#line 99 "/home/renatex/Desktop/MEPL/compiler/src/parser/elegant_parser.y"
                                                                        {
    PyObject *pArgsList = PyList_New(0);
    PyObject *pValue = yyvsp[-2];
    PyObject *pChildren = PyList_New(0);

    PyList_Append(pChildren, yyvsp[-4]);
    if (yyvsp[-1] != 0) {
        PyList_Append(pChildren, yyvsp[-1]);
    }

    PyList_Append(pArgsList, pValue);
    PyList_Append(pArgsList, pChildren);

    PyObject *pArgsTuple = PyList_AsTuple(pArgsList);
    yyval = create_ast_node("ElegantVariableDeclaration", pArgsTuple);
    
    Py_DECREF(pArgsList);
    Py_DECREF(pValue);
    Py_DECREF(pChildren);
    Py_DECREF(pArgsTuple);
}
#line 1299 "elegant_parser.tab.c"
    break;

  case 14: /* Identifier: T_IDENTIFIER  */
#line 121 "/home/renatex/Desktop/MEPL/compiler/src/parser/elegant_parser.y"
                            {
    PyObject *pArgsList = PyList_New(0);
    PyObject *pValue = PyUnicode_FromString(yytext);
    PyObject *pChildren = PyList_New(0);

    PyList_Append(pArgsList, pValue);
    PyList_Append(pArgsList, pChildren);

    PyObject *pArgsTuple = PyList_AsTuple(pArgsList);
    yyval = create_ast_node("ElegantIdentifier", pArgsTuple);
    
    Py_DECREF(pArgsList);
    Py_DECREF(pValue);
    Py_DECREF(pChildren);
    Py_DECREF(pArgsTuple);
}
#line 1320 "elegant_parser.tab.c"
    break;

  case 15: /* Type: T_INTEGER_TYPE  */
#line 138 "/home/renatex/Desktop/MEPL/compiler/src/parser/elegant_parser.y"
                        {
    yyval = PyUnicode_FromString("INT");
}
#line 1328 "elegant_parser.tab.c"
    break;

  case 16: /* Type: T_STRING_TYPE  */
#line 141 "/home/renatex/Desktop/MEPL/compiler/src/parser/elegant_parser.y"
                    {
    yyval = PyUnicode_FromString("STRING");
}
#line 1336 "elegant_parser.tab.c"
    break;

  case 17: /* OptionalValue: %empty  */
#line 145 "/home/renatex/Desktop/MEPL/compiler/src/parser/elegant_parser.y"
                            {
    yyval = 0;
}
#line 1344 "elegant_parser.tab.c"
    break;

  case 18: /* OptionalValue: T_DECLARE_VALUE BooleanExpression  */
#line 148 "/home/renatex/Desktop/MEPL/compiler/src/parser/elegant_parser.y"
                                                {
    yyval = yyvsp[0];
}
#line 1352 "elegant_parser.tab.c"
    break;

  case 19: /* Assign: T_ASSIGN Identifier T_ASSIGN_VALUE BooleanExpression T_NEW_SENTENCE  */
#line 152 "/home/renatex/Desktop/MEPL/compiler/src/parser/elegant_parser.y"
                                                                            {
    PyObject *pArgsList = PyList_New(0);
    PyObject *pValue = PyUnicode_FromString("ElegantAssignment");
    PyObject *pChildren = PyList_New(0);

    PyList_Append(pChildren, yyvsp[-3]);
    PyList_Append(pChildren, yyvsp[-1]);

    PyList_Append(pArgsList, pValue);
    PyList_Append(pArgsList, pChildren);

    PyObject *pArgsTuple = PyList_AsTuple(pArgsList);
    yyval = create_ast_node("ElegantAssignment", pArgsTuple);
    
    Py_DECREF(pArgsList);
    Py_DECREF(pValue);
    Py_DECREF(pChildren);
    Py_DECREF(pArgsTuple);
}
#line 1376 "elegant_parser.tab.c"
    break;

  case 20: /* Conditional: T_CONDITIONAL BooleanExpression T_HOLDS_TRUE Block OptionalElse  */
#line 172 "/home/renatex/Desktop/MEPL/compiler/src/parser/elegant_parser.y"
                                                                                {
    PyObject *pArgsList = PyList_New(0);
    PyObject *pValue = PyUnicode_FromString("ElegantConditional");
    PyObject *pChildren = PyList_New(0);

    PyList_Append(pChildren, yyvsp[-3]);
    PyList_Append(pChildren, yyvsp[-1]);
    if (yyvsp[0] != 0) {
        PyList_Append(pChildren, yyvsp[0]);
    }

    PyList_Append(pArgsList, pValue);
    PyList_Append(pArgsList, pChildren);

    PyObject *pArgsTuple = PyList_AsTuple(pArgsList);
    yyval = create_ast_node("ElegantConditional", pArgsTuple);
    
    Py_DECREF(pArgsList);
    Py_DECREF(pValue);
    Py_DECREF(pChildren);
    Py_DECREF(pArgsTuple);
}
#line 1403 "elegant_parser.tab.c"
    break;

  case 21: /* OptionalElse: %empty  */
#line 195 "/home/renatex/Desktop/MEPL/compiler/src/parser/elegant_parser.y"
                            {
    yyval = 0;
}
#line 1411 "elegant_parser.tab.c"
    break;

  case 22: /* OptionalElse: T_OTHERWISE Block  */
#line 198 "/home/renatex/Desktop/MEPL/compiler/src/parser/elegant_parser.y"
                                {
    yyval = yyvsp[0];
}
#line 1419 "elegant_parser.tab.c"
    break;

  case 23: /* Loop: T_WHILST BooleanExpression T_HOLDS_TRUE Block  */
#line 202 "/home/renatex/Desktop/MEPL/compiler/src/parser/elegant_parser.y"
                                                    {
    PyObject *pArgsList = PyList_New(0);
    PyObject *pValue = PyUnicode_FromString("ElegantLoop");
    PyObject *pChildren = PyList_New(0);

    PyList_Append(pChildren, yyvsp[-2]);
    PyList_Append(pChildren, yyvsp[0]);

    PyList_Append(pArgsList, pValue);
    PyList_Append(pArgsList, pChildren);

    PyObject *pArgsTuple = PyList_AsTuple(pArgsList);
    yyval = create_ast_node("ElegantLoop", pArgsTuple);
    
    Py_DECREF(pArgsList);
    Py_DECREF(pValue);
    Py_DECREF(pChildren);
    Py_DECREF(pArgsTuple);
}
#line 1443 "elegant_parser.tab.c"
    break;

  case 24: /* Solicit: T_SOLICITATION Identifier T_NEW_SENTENCE  */
#line 222 "/home/renatex/Desktop/MEPL/compiler/src/parser/elegant_parser.y"
                                                    {
    PyObject *pArgsList = PyList_New(0);
    PyObject *pValue = PyUnicode_FromString("ElegantSolicitation");
    PyObject *pChildren = PyList_New(0);

    PyList_Append(pChildren, yyvsp[-1]);

    PyList_Append(pArgsList, pValue);
    PyList_Append(pArgsList, pChildren);

    PyObject *pArgsTuple = PyList_AsTuple(pArgsList);
    yyval = create_ast_node("ElegantSolicitation", pArgsTuple);
    
    Py_DECREF(pArgsList);
    Py_DECREF(pValue);
    Py_DECREF(pChildren);
    Py_DECREF(pArgsTuple);
}
#line 1466 "elegant_parser.tab.c"
    break;

  case 25: /* Display: T_DISPLAY BooleanExpression T_NEW_SENTENCE  */
#line 241 "/home/renatex/Desktop/MEPL/compiler/src/parser/elegant_parser.y"
                                                    {
    PyObject *pArgsList = PyList_New(0);
    PyObject *pValue = PyUnicode_FromString("ElegantDisplay");
    PyObject *pChildren = PyList_New(0);

    PyList_Append(pChildren, yyvsp[-1]);

    PyList_Append(pArgsList, pValue);
    PyList_Append(pArgsList, pChildren);

    PyObject *pArgsTuple = PyList_AsTuple(pArgsList);
    yyval = create_ast_node("ElegantDisplay", pArgsTuple);
    
    Py_DECREF(pArgsList);
    Py_DECREF(pValue);
    Py_DECREF(pChildren);
    Py_DECREF(pArgsTuple);
}
#line 1489 "elegant_parser.tab.c"
    break;

  case 26: /* Block: T_FIRSTLY BlockSentenceList T_CONCLUSION T_NEW_SENTENCE  */
#line 260 "/home/renatex/Desktop/MEPL/compiler/src/parser/elegant_parser.y"
                                                                 {
    PyObject *pArgsList = PyList_New(0);
    PyObject *pValue = PyUnicode_FromString("ElegantBlock");

    PyList_Append(pArgsList, pValue);
    PyList_Append(pArgsList, yyvsp[-2]);

    PyObject *pArgsTuple = PyList_AsTuple(pArgsList);
    yyval = create_ast_node("ElegantBlock", pArgsTuple);
    
    Py_DECREF(pArgsList);
    Py_DECREF(pValue);
    Py_DECREF(pArgsTuple);
}
#line 1508 "elegant_parser.tab.c"
    break;

  case 27: /* BlockSentenceList: %empty  */
#line 275 "/home/renatex/Desktop/MEPL/compiler/src/parser/elegant_parser.y"
                                {
    yyval = PyList_New(0); // Base case: an empty list
}
#line 1516 "elegant_parser.tab.c"
    break;

  case 28: /* BlockSentenceList: BlockSentenceList Sentence  */
#line 278 "/home/renatex/Desktop/MEPL/compiler/src/parser/elegant_parser.y"
                                         {
    if (!PyList_Check(yyvsp[-1])) {
        yyerror("Expected a list as the first argument");
        yyval = NULL;
    } else {
        PyList_Append(yyvsp[-1], yyvsp[0]);
        yyval = yyvsp[-1];    // Assign the modified list back to $$
    }
}
#line 1530 "elegant_parser.tab.c"
    break;

  case 29: /* BooleanExpression: BooleanClause  */
#line 288 "/home/renatex/Desktop/MEPL/compiler/src/parser/elegant_parser.y"
                                    {
    yyval = yyvsp[0];
}
#line 1538 "elegant_parser.tab.c"
    break;

  case 30: /* BooleanExpression: BooleanExpression T_OR BooleanClause  */
#line 291 "/home/renatex/Desktop/MEPL/compiler/src/parser/elegant_parser.y"
                                                        {
    PyObject *pArgsList = PyList_New(0);
    PyObject *pValue = PyUnicode_FromString("or");
    PyObject *pChildren = PyList_New(0);

    PyList_Append(pChildren, yyvsp[-2]);
    PyList_Append(pChildren, yyvsp[0]);

    PyList_Append(pArgsList, pValue);
    PyList_Append(pArgsList, pChildren);

    PyObject *pArgsTuple = PyList_AsTuple(pArgsList);
    yyval = create_ast_node("ElegantBinaryOperation", pArgsTuple);
    
    Py_DECREF(pArgsList);
    Py_DECREF(pValue);
    Py_DECREF(pChildren);
    Py_DECREF(pArgsTuple);
}
#line 1562 "elegant_parser.tab.c"
    break;

  case 31: /* BooleanClause: RelationalExpression  */
#line 311 "/home/renatex/Desktop/MEPL/compiler/src/parser/elegant_parser.y"
                                    {
    yyval = yyvsp[0];
}
#line 1570 "elegant_parser.tab.c"
    break;

  case 32: /* BooleanClause: BooleanClause T_AND RelationalExpression  */
#line 314 "/home/renatex/Desktop/MEPL/compiler/src/parser/elegant_parser.y"
                                                        {
    PyObject *pArgsList = PyList_New(0);
    PyObject *pValue = PyUnicode_FromString("and");
    PyObject *pChildren = PyList_New(0);

    PyList_Append(pChildren, yyvsp[-2]);
    PyList_Append(pChildren, yyvsp[0]);

    PyList_Append(pArgsList, pValue);
    PyList_Append(pArgsList, pChildren);

    PyObject *pArgsTuple = PyList_AsTuple(pArgsList);
    yyval = create_ast_node("ElegantBinaryOperation", pArgsTuple);
    
    Py_DECREF(pArgsList);
    Py_DECREF(pValue);
    Py_DECREF(pChildren);
    Py_DECREF(pArgsTuple);
}
#line 1594 "elegant_parser.tab.c"
    break;

  case 33: /* RelationalExpression: Expression  */
#line 334 "/home/renatex/Desktop/MEPL/compiler/src/parser/elegant_parser.y"
                                    {
    yyval = yyvsp[0];
}
#line 1602 "elegant_parser.tab.c"
    break;

  case 34: /* RelationalExpression: RelationalExpression RelationalOp Expression  */
#line 337 "/home/renatex/Desktop/MEPL/compiler/src/parser/elegant_parser.y"
                                                                    {
    PyObject *pArgsList = PyList_New(0);
    PyObject *pValue = yyvsp[-1];
    PyObject *pChildren = PyList_New(0);

    PyList_Append(pChildren, yyvsp[-2]);
    PyList_Append(pChildren, yyvsp[0]);

    PyList_Append(pArgsList, pValue);
    PyList_Append(pArgsList, pChildren);

    PyObject *pArgsTuple = PyList_AsTuple(pArgsList);
    yyval = create_ast_node("ElegantBinaryOperation", pArgsTuple);
    
    Py_DECREF(pArgsList);
    Py_DECREF(pValue);
    Py_DECREF(pChildren);
    Py_DECREF(pArgsTuple);
}
#line 1626 "elegant_parser.tab.c"
    break;

  case 35: /* RelationalOp: T_EQUIVALENCE  */
#line 357 "/home/renatex/Desktop/MEPL/compiler/src/parser/elegant_parser.y"
                            {
    yyval = PyUnicode_FromString(yytext); 
}
#line 1634 "elegant_parser.tab.c"
    break;

  case 36: /* RelationalOp: T_DIFFERENCE  */
#line 360 "/home/renatex/Desktop/MEPL/compiler/src/parser/elegant_parser.y"
                            {
    yyval = PyUnicode_FromString(yytext); 
}
#line 1642 "elegant_parser.tab.c"
    break;

  case 37: /* RelationalOp: T_GREATER  */
#line 363 "/home/renatex/Desktop/MEPL/compiler/src/parser/elegant_parser.y"
                            {
    yyval = PyUnicode_FromString(yytext); 
}
#line 1650 "elegant_parser.tab.c"
    break;

  case 38: /* RelationalOp: T_LESSER  */
#line 366 "/home/renatex/Desktop/MEPL/compiler/src/parser/elegant_parser.y"
                            {
    yyval = PyUnicode_FromString(yytext); 
}
#line 1658 "elegant_parser.tab.c"
    break;

  case 39: /* Expression: Term  */
#line 370 "/home/renatex/Desktop/MEPL/compiler/src/parser/elegant_parser.y"
                    {
    yyval = yyvsp[0];
}
#line 1666 "elegant_parser.tab.c"
    break;

  case 40: /* Expression: Expression ArithmeticAddSubConcatOp Term  */
#line 373 "/home/renatex/Desktop/MEPL/compiler/src/parser/elegant_parser.y"
                                                        {
    PyObject *pArgsList = PyList_New(0);
    PyObject *pValue = yyvsp[-1];
    PyObject *pChildren = PyList_New(0);

    PyList_Append(pChildren, yyvsp[-2]);
    PyList_Append(pChildren, yyvsp[0]);

    PyList_Append(pArgsList, pValue);
    PyList_Append(pArgsList, pChildren);

    PyObject *pArgsTuple = PyList_AsTuple(pArgsList);
    yyval = create_ast_node("ElegantBinaryOperation", pArgsTuple);
    
    Py_DECREF(pArgsList);
    Py_DECREF(pValue);
    Py_DECREF(pChildren);
    Py_DECREF(pArgsTuple);
}
#line 1690 "elegant_parser.tab.c"
    break;

  case 41: /* ArithmeticAddSubConcatOp: T_ADDITION  */
#line 393 "/home/renatex/Desktop/MEPL/compiler/src/parser/elegant_parser.y"
                                        {
    yyval = PyUnicode_FromString(yytext); 
}
#line 1698 "elegant_parser.tab.c"
    break;

  case 42: /* ArithmeticAddSubConcatOp: T_SUBTRACTION  */
#line 396 "/home/renatex/Desktop/MEPL/compiler/src/parser/elegant_parser.y"
                                        {
    yyval = PyUnicode_FromString(yytext); 
}
#line 1706 "elegant_parser.tab.c"
    break;

  case 43: /* ArithmeticAddSubConcatOp: T_CONCATENATION  */
#line 399 "/home/renatex/Desktop/MEPL/compiler/src/parser/elegant_parser.y"
                                            {
    yyval = PyUnicode_FromString(yytext); 
}
#line 1714 "elegant_parser.tab.c"
    break;

  case 44: /* Term: Factor  */
#line 403 "/home/renatex/Desktop/MEPL/compiler/src/parser/elegant_parser.y"
                {
    yyval = yyvsp[0];
}
#line 1722 "elegant_parser.tab.c"
    break;

  case 45: /* Term: Term ArithmeticMultDivOp Factor  */
#line 406 "/home/renatex/Desktop/MEPL/compiler/src/parser/elegant_parser.y"
                                        {
    PyObject *pArgsList = PyList_New(0);
    PyObject *pValue = yyvsp[-1];
    PyObject *pChildren = PyList_New(0);

    PyList_Append(pChildren, yyvsp[-2]);
    PyList_Append(pChildren, yyvsp[0]);

    PyList_Append(pArgsList, pValue);
    PyList_Append(pArgsList, pChildren);

    PyObject *pArgsTuple = PyList_AsTuple(pArgsList);
    yyval = create_ast_node("ElegantBinaryOperation", pArgsTuple);
    
    Py_DECREF(pArgsList);
    Py_DECREF(pValue);
    Py_DECREF(pChildren);
    Py_DECREF(pArgsTuple);
}
#line 1746 "elegant_parser.tab.c"
    break;

  case 46: /* ArithmeticMultDivOp: T_MULTIPLICATION  */
#line 426 "/home/renatex/Desktop/MEPL/compiler/src/parser/elegant_parser.y"
                                        {
    yyval = PyUnicode_FromString(yytext); 
}
#line 1754 "elegant_parser.tab.c"
    break;

  case 47: /* ArithmeticMultDivOp: T_DIVISON  */
#line 429 "/home/renatex/Desktop/MEPL/compiler/src/parser/elegant_parser.y"
                                {
    yyval = PyUnicode_FromString(yytext); 
}
#line 1762 "elegant_parser.tab.c"
    break;

  case 48: /* Factor: T_NUMBER  */
#line 433 "/home/renatex/Desktop/MEPL/compiler/src/parser/elegant_parser.y"
                    {
    PyObject *pArgsList = PyList_New(0);
    PyObject *pValue = PyUnicode_FromString(yytext);
    PyObject *pChildren = PyList_New(0);

    PyList_Append(pArgsList, pValue);
    PyList_Append(pArgsList, pChildren);

    PyObject *pArgsTuple = PyList_AsTuple(pArgsList);
    yyval = create_ast_node("ElegantIntegerValue", pArgsTuple);
    
    Py_DECREF(pArgsList);
    Py_DECREF(pValue);
    Py_DECREF(pChildren);
    Py_DECREF(pArgsTuple);
}
#line 1783 "elegant_parser.tab.c"
    break;

  case 49: /* Factor: T_STRING  */
#line 449 "/home/renatex/Desktop/MEPL/compiler/src/parser/elegant_parser.y"
                    {
    PyObject *pArgsList = PyList_New(0);
    PyObject *pValue = PyUnicode_FromString(yytext);
    PyObject *pChildren = PyList_New(0);

    PyList_Append(pArgsList, pValue);
    PyList_Append(pArgsList, pChildren);

    PyObject *pArgsTuple = PyList_AsTuple(pArgsList);
    yyval = create_ast_node("ElegantStringValue", pArgsTuple);
    
    Py_DECREF(pArgsList);
    Py_DECREF(pValue);
    Py_DECREF(pChildren);
    Py_DECREF(pArgsTuple);
}
#line 1804 "elegant_parser.tab.c"
    break;

  case 50: /* Factor: UnaryOp Factor  */
#line 465 "/home/renatex/Desktop/MEPL/compiler/src/parser/elegant_parser.y"
                        {
    PyObject *pArgsList = PyList_New(0);
    PyObject *pValue = yyvsp[-1];
    PyObject *pChildren = PyList_New(0);

    PyList_Append(pChildren, yyvsp[0]);

    PyList_Append(pArgsList, pValue);
    PyList_Append(pArgsList, pChildren);

    PyObject *pArgsTuple = PyList_AsTuple(pArgsList);
    yyval = create_ast_node("ElegantUnaryOperation", pArgsTuple);
    
    Py_DECREF(pArgsList);
    Py_DECREF(pValue);
    Py_DECREF(pChildren);
    Py_DECREF(pArgsTuple);
}
#line 1827 "elegant_parser.tab.c"
    break;

  case 52: /* UnaryOp: T_POSITIVELY  */
#line 485 "/home/renatex/Desktop/MEPL/compiler/src/parser/elegant_parser.y"
                        {
    yyval = PyUnicode_FromString(yytext); 
}
#line 1835 "elegant_parser.tab.c"
    break;

  case 53: /* UnaryOp: T_NEGATIVELY  */
#line 488 "/home/renatex/Desktop/MEPL/compiler/src/parser/elegant_parser.y"
                        {
    yyval = PyUnicode_FromString(yytext); 
}
#line 1843 "elegant_parser.tab.c"
    break;

  case 54: /* UnaryOp: T_NOT  */
#line 491 "/home/renatex/Desktop/MEPL/compiler/src/parser/elegant_parser.y"
                {
    yyval = PyUnicode_FromString(yytext); 
}
#line 1851 "elegant_parser.tab.c"
    break;


#line 1855 "elegant_parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 495 "/home/renatex/Desktop/MEPL/compiler/src/parser/elegant_parser.y"


void yyerror(const char *s) {
    fprintf(stderr, "Error near token '%s': %s\n", yytext, s);
}

PyObject *create_instance(const char* module_name, const char* class_name, PyObject *args) {
    PyObject *pName = PyUnicode_FromString(module_name);
    PyObject *pModule = PyImport_Import(pName);
    Py_DECREF(pName);
    if (pModule == NULL) return NULL;

    PyObject *pClass = PyObject_GetAttrString(pModule, class_name);
    Py_DECREF(pModule);
    if (pClass == NULL) return NULL;

    PyObject *pInstance;
    if (args != NULL) {
        pInstance = PyObject_CallObject(pClass, args);
    } else {
        pInstance = PyObject_CallObject(pClass, NULL);
    }
    Py_DECREF(pClass);
    if (pInstance == NULL) {
        PyErr_Print();
        fprintf(stderr, "Failed to create instance of '%s'\n", class_name);
        return NULL;
    }

    return pInstance;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror(argv[1]);
        return 1;
    }

    yyin = file;

    Py_Initialize();

    PyObject *pSymbolTable = create_instance("compiler.src.semantic.SymbolTable", "SymbolTable", NULL);

    PyObject *pFilename = PyUnicode_FromString(argv[1]);
    PyObject *pArgs = PyTuple_New(1);
    PyTuple_SetItem(pArgs, 0, pFilename);
    PyObject *pCodeGenerator = create_instance("compiler.src.codegen.CodeGenerator", "CodeGen", pArgs);
    Py_DECREF(pArgs);

    PyObject_CallMethod(pCodeGenerator, "start", NULL);
    
    if (yyparse() == 0 && pRootNode != NULL) {
        PyObject_CallMethod(pRootNode, "evaluate", "OO", pSymbolTable, pCodeGenerator);
    } else {
        printf("Error in parsing!\n");
    }

    PyObject_CallMethod(pCodeGenerator, "finish", NULL);

    Py_XDECREF(pRootNode);
    Py_XDECREF(pSymbolTable);
    Py_XDECREF(pCodeGenerator);
    Py_Finalize();
    fclose(file);
    return 0;
}

