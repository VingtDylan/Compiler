/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 3 "./syntax.y" /* yacc.c:339  */

  #include <stdio.h>
  #include <stdlib.h>
  #include "grammertree.h"
  #include "semantic.h"
  #include "semanticTraverse.h"
  #include "lex.yy.c"
  int yyerror(const char *s);
  int yylex();
  extern void yyrestart(FILE*);
  extern int yyparse(); 
  extern FILE *yyin;
  extern int yylineno;
  bool error_exist=false;
  TreeNode* Root=NULL;

#line 83 "./syntax.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "syntax.tab.h".  */
#ifndef YY_YY_SYNTAX_TAB_H_INCLUDED
# define YY_YY_SYNTAX_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ID = 258,
    INT = 259,
    FLOAT = 260,
    SEMI = 261,
    COMMA = 262,
    ASSIGNOP = 263,
    RELOP = 264,
    PLUS = 265,
    MINUS = 266,
    STAR = 267,
    DIV = 268,
    AND = 269,
    OR = 270,
    DOT = 271,
    NOT = 272,
    TYPE = 273,
    STRUCT = 274,
    LP = 275,
    RP = 276,
    LB = 277,
    RB = 278,
    LC = 279,
    RC = 280,
    IF = 281,
    ELSE = 282,
    WHILE = 283,
    RETURN = 284,
    LOWER_THAN_ELSE = 285
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 24 "./syntax.y" /* yacc.c:355  */

  int ivalue;
  float fvalue;
  //double dvalue;
  //char *string;
  struct Node* treenode; 

#line 162 "./syntax.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_SYNTAX_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 193 "./syntax.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  13
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   309

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  31
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  69
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  130

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   285

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
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
      25,    26,    27,    28,    29,    30
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    69,    69,    76,    81,    84,    91,    97,   103,   110,
     113,   117,   127,   131,   137,   145,   152,   156,   159,   167,
     171,   178,   181,   188,   194,   197,   203,   209,   213,   214,
     219,   227,   230,   235,   238,   243,   247,   253,   261,   271,
     276,   288,   293,   296,   303,   306,   310,   318,   322,   332,
     338,   344,   350,   356,   362,   368,   374,   380,   386,   391,
     396,   403,   409,   416,   421,   427,   431,   435,   441,   447
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "ID", "INT", "FLOAT", "SEMI", "COMMA",
  "ASSIGNOP", "RELOP", "PLUS", "MINUS", "STAR", "DIV", "AND", "OR", "DOT",
  "NOT", "TYPE", "STRUCT", "LP", "RP", "LB", "RB", "LC", "RC", "IF",
  "ELSE", "WHILE", "RETURN", "LOWER_THAN_ELSE", "$accept", "Program",
  "ExtDefList", "ExtDef", "ExtDecList", "Specifier", "StructSpecifier",
  "OptTag", "Tag", "VarDec", "FunDec", "VarList", "ParamDec", "CompSt",
  "StmtList", "Stmt", "DefList", "Def", "DecList", "Dec", "Exp", "Args", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285
};
# endif

#define YYPACT_NINF -61

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-61)))

#define YYTABLE_NINF -43

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     122,     5,   -61,    14,    47,   -61,   122,    12,   -61,   -61,
      25,    44,   -61,   -61,   -61,    68,    54,   -61,    87,     2,
      -5,    21,   -61,    24,   -61,    95,   142,   -61,    33,   -61,
      97,    95,    84,    62,    57,   -61,    95,    89,   107,   -61,
     -61,   103,   105,    35,   101,   -61,    61,   118,   127,   -61,
     -61,   -61,   -61,   113,   -61,    53,   -61,   -61,   -61,   131,
     -61,   -61,   133,   133,   133,   143,   144,   133,   -61,   117,
     101,   146,   133,   -61,    95,   -61,   128,   287,    -8,   208,
     133,   133,   161,   -61,   -61,   -61,   133,   133,   133,   133,
     133,   133,   133,   133,   162,    96,   253,   -61,   -61,   177,
     126,   -61,   223,   238,   -61,   253,   282,   287,   287,    -8,
      -8,   275,   267,   -61,   155,   192,   133,   -61,    91,   101,
     -61,   -61,   -61,   139,   152,   -61,   101,   101,   -61,   -61
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    12,    17,     0,     2,     0,     0,    13,     9,
      18,     0,    15,     1,     3,     0,    19,     6,     0,    10,
       0,     0,    24,     0,     5,     0,     0,     8,     0,     7,
       0,     0,     0,     0,     0,    23,     0,     0,    26,    19,
      11,     0,     0,     0,    33,    44,    47,     0,    45,    14,
      41,    28,    29,    27,    22,     0,    21,    20,    31,    65,
      66,    67,     0,     0,     0,     0,     0,     0,    35,     0,
      33,     0,     0,    43,     0,    25,     0,    58,    59,     0,
       0,     0,     0,    30,    32,    34,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    48,    46,    61,    69,
       0,    57,     0,     0,    36,    49,    52,    53,    54,    55,
      56,    50,    51,    64,     0,     0,     0,    60,     0,     0,
      63,    62,    68,     0,    37,    40,     0,     0,    39,    38
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -61,   -61,   174,   -61,   156,     0,   -61,   -61,   -61,   -26,
     -61,   140,   -61,   176,   112,   -42,    42,   -61,   120,   -61,
     -60,    81
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     4,     5,     6,    18,    31,     8,    11,    12,    19,
      20,    37,    38,    68,    69,    70,    32,    33,    47,    48,
      71,   100
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
       7,    27,    77,    78,    79,    46,     7,    82,    94,    25,
      53,     9,    96,    15,    95,    16,    99,    10,    17,    28,
     102,   103,    30,    36,    26,    34,   105,   106,   107,   108,
     109,   110,   111,   112,    43,   115,   -42,   -42,   -42,     2,
       3,    45,     2,     3,   -42,    35,   -42,    13,    46,   -16,
     -42,     2,     3,   -42,    34,    36,    99,   -42,   -42,   -42,
      58,   -42,   -42,    30,    51,   -42,   -42,   -42,    21,    72,
      44,     2,     3,   -42,    23,    50,   124,   125,    52,   -42,
       2,     3,   -42,    26,   128,   129,   -42,   -42,   -42,    22,
     -42,   -42,   123,    24,    59,    60,    61,   114,    39,    59,
      60,    61,    62,    45,    59,    60,    61,    62,    63,    49,
      54,    64,    62,    63,    55,    28,    64,    65,    63,    66,
      67,    64,    -4,     1,    73,    28,    56,    65,    57,    66,
      67,    59,    60,    61,    74,    26,    59,    60,    61,    62,
       2,     3,    83,    41,    62,    63,    42,   117,    64,    98,
      63,    76,    85,    64,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    80,    81,   113,   126,   104,    95,    86,
      87,    88,    89,    90,    91,    92,    93,    94,   120,   127,
      14,    40,    84,    95,   116,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    97,    75,    29,   122,     0,    95,
      86,    87,    88,    89,    90,    91,    92,    93,    94,     0,
       0,     0,     0,     0,    95,   121,    86,    87,    88,    89,
      90,    91,    92,    93,    94,     0,     0,     0,     0,   101,
      95,    86,    87,    88,    89,    90,    91,    92,    93,    94,
       0,     0,     0,     0,   118,    95,    86,    87,    88,    89,
      90,    91,    92,    93,    94,     0,     0,     0,     0,   119,
      95,    86,    87,    88,    89,    90,    91,    92,    93,    94,
       0,     0,     0,     0,     0,    95,    87,    88,    89,    90,
      91,    92,     0,    94,    87,    88,    89,    90,    91,    95,
       0,    94,    88,    89,    90,    91,     0,    95,    94,    90,
      91,     0,     0,    94,    95,     0,     0,     0,     0,    95
};

static const yytype_int8 yycheck[] =
{
       0,     6,    62,    63,    64,    31,     6,    67,    16,     7,
      36,     6,    72,     1,    22,     3,    76,     3,     6,    24,
      80,    81,     1,    23,    22,     1,    86,    87,    88,    89,
      90,    91,    92,    93,     1,    95,     3,     4,     5,    18,
      19,     6,    18,    19,    11,    21,    25,     0,    74,    24,
      17,    18,    19,    20,     1,    55,   116,    24,    25,    26,
      25,    28,    29,     1,     7,     3,     4,     5,    24,     8,
      28,    18,    19,    11,    20,    33,   118,   119,    21,    17,
      18,    19,    20,    22,   126,   127,    24,    25,    26,    21,
      28,    29,     1,     6,     3,     4,     5,     1,     3,     3,
       4,     5,    11,     6,     3,     4,     5,    11,    17,    25,
      21,    20,    11,    17,     7,    24,    20,    26,    17,    28,
      29,    20,     0,     1,     6,    24,    23,    26,    23,    28,
      29,     3,     4,     5,     7,    22,     3,     4,     5,    11,
      18,    19,    25,     1,    11,    17,     4,    21,    20,    21,
      17,    20,     6,    20,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    20,    20,     3,    27,     6,    22,     8,
       9,    10,    11,    12,    13,    14,    15,    16,    23,    27,
       6,    25,    70,    22,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    74,    55,    20,   116,    -1,    22,
       8,     9,    10,    11,    12,    13,    14,    15,    16,    -1,
      -1,    -1,    -1,    -1,    22,    23,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    -1,    -1,    -1,    -1,    21,
      22,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      -1,    -1,    -1,    -1,    21,    22,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    -1,    -1,    -1,    -1,    21,
      22,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      -1,    -1,    -1,    -1,    -1,    22,     9,    10,    11,    12,
      13,    14,    -1,    16,     9,    10,    11,    12,    13,    22,
      -1,    16,    10,    11,    12,    13,    -1,    22,    16,    12,
      13,    -1,    -1,    16,    22,    -1,    -1,    -1,    -1,    22
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     1,    18,    19,    32,    33,    34,    36,    37,     6,
       3,    38,    39,     0,    33,     1,     3,     6,    35,    40,
      41,    24,    21,    20,     6,     7,    22,     6,    24,    44,
       1,    36,    47,    48,     1,    21,    36,    42,    43,     3,
      35,     1,     4,     1,    47,     6,    40,    49,    50,    25,
      47,     7,    21,    40,    21,     7,    23,    23,    25,     3,
       4,     5,    11,    17,    20,    26,    28,    29,    44,    45,
      46,    51,     8,     6,     7,    42,    20,    51,    51,    51,
      20,    20,    51,    25,    45,     6,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    22,    51,    49,    21,    51,
      52,    21,    51,    51,     6,    51,    51,    51,    51,    51,
      51,    51,    51,     3,     1,    51,     7,    21,    21,    21,
      23,    23,    52,     1,    46,    46,    27,    27,    46,    46
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    31,    32,    33,    33,    34,    34,    34,    34,    34,
      35,    35,    36,    36,    37,    37,    38,    38,    39,    40,
      40,    40,    41,    41,    41,    42,    42,    43,    43,    43,
      44,    44,    45,    45,    46,    46,    46,    46,    46,    46,
      46,    47,    47,    48,    48,    49,    49,    50,    50,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    51,    51,
      51,    51,    51,    51,    51,    51,    51,    51,    52,    52
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     3,     2,     3,     3,     2,
       1,     3,     1,     1,     5,     2,     1,     0,     1,     1,
       4,     4,     4,     3,     2,     3,     1,     2,     2,     2,
       4,     3,     2,     0,     2,     1,     3,     5,     7,     7,
       5,     2,     0,     3,     2,     1,     3,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       4,     3,     4,     4,     3,     1,     1,     1,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;
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
| yyreduce -- Do a reduction.  |
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

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 69 "./syntax.y" /* yacc.c:1646  */
    { 
               (yyval.treenode) = createNode("Program"," ",Node_Program,d_gray); 
               addChild((yyval.treenode),(yyvsp[0].treenode),1);  
               Root=(yyval.treenode); 
             }
#line 1486 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 76 "./syntax.y" /* yacc.c:1646  */
    { 
               (yyval.treenode) = createNode("ExtDefList"," ",Node_Program,d_gray); 
               addChild((yyval.treenode),(yyvsp[-1].treenode),1); 
               addChild((yyval.treenode),(yyvsp[0].treenode),2); 
             }
#line 1496 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 81 "./syntax.y" /* yacc.c:1646  */
    { (yyval.treenode) = NULL ;/*NULL*/}
#line 1502 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 84 "./syntax.y" /* yacc.c:1646  */
    { 
               (yyval.treenode) = createNode("ExtDef"," ",Node_Program,d_gray); 
               addChild((yyval.treenode),(yyvsp[-2].treenode),1); 
               addChild((yyval.treenode),(yyvsp[-1].treenode),2); 
               addChild((yyval.treenode),(yyvsp[0].treenode),3); 
             }
#line 1513 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 91 "./syntax.y" /* yacc.c:1646  */
    { 
               (yyval.treenode) = createNode("ExtDef"," ",Node_Program,d_gray); 
               addChild((yyval.treenode),(yyvsp[-1].treenode),1); 
               addChild((yyval.treenode),(yyvsp[0].treenode),2); 
             }
#line 1523 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 97 "./syntax.y" /* yacc.c:1646  */
    { 
               (yyval.treenode) = createNode("ExtDef"," ",Node_Program,d_gray); 
               addChild((yyval.treenode),(yyvsp[-2].treenode),1); 
               addChild((yyval.treenode),(yyvsp[-1].treenode),2); 
               addChild((yyval.treenode),(yyvsp[0].treenode),3); 
             }
#line 1534 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 103 "./syntax.y" /* yacc.c:1646  */
    {
               (yyval.treenode) = createNode("ExtDef"," ",Node_Program,d_gray);
               addChild((yyval.treenode),(yyvsp[-2].treenode),1);
               addChild((yyval.treenode),(yyvsp[-1].treenode),2);
               addChild((yyval.treenode),(yyvsp[0].treenode),3);
             }
#line 1545 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 110 "./syntax.y" /* yacc.c:1646  */
    { error_exist = true;/*yyerrok;*/ }
#line 1551 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 113 "./syntax.y" /* yacc.c:1646  */
    { 
               (yyval.treenode) = createNode("ExtDecList"," ",Node_Program,d_gray); 
               addChild((yyval.treenode),(yyvsp[0].treenode),1); 
             }
#line 1560 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 117 "./syntax.y" /* yacc.c:1646  */
    { 
               (yyval.treenode) = createNode("ExtDecList"," ",Node_Program,d_gray); 
               addChild((yyval.treenode),(yyvsp[-2].treenode),1); 
               addChild((yyval.treenode),(yyvsp[-1].treenode),2); 
               addChild((yyval.treenode),(yyvsp[0].treenode),3); 
             }
#line 1571 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 127 "./syntax.y" /* yacc.c:1646  */
    { 
               (yyval.treenode) = createNode("Specifier"," ",Node_Program,d_gray); 
               addChild((yyval.treenode),(yyvsp[0].treenode),1); 
             }
#line 1580 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 131 "./syntax.y" /* yacc.c:1646  */
    { 
               (yyval.treenode) = createNode("StructSpecifier"," ",Node_Program,d_gray);
               addChild((yyval.treenode),(yyvsp[0].treenode),1);
             }
#line 1589 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 137 "./syntax.y" /* yacc.c:1646  */
    { 
                   (yyval.treenode) = createNode("StructSpecifier"," ",Node_Program,d_gray); 
                   addChild((yyval.treenode),(yyvsp[-4].treenode),1);
                   addChild((yyval.treenode),(yyvsp[-3].treenode),2); 
                   addChild((yyval.treenode),(yyvsp[-2].treenode),3); 
                   addChild((yyval.treenode),(yyvsp[-1].treenode),4); 
                   addChild((yyval.treenode),(yyvsp[0].treenode),5); 
                 }
#line 1602 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 145 "./syntax.y" /* yacc.c:1646  */
    { 
               (yyval.treenode) = createNode("StructSpecifier"," ",Node_Program,d_gray);
               addChild((yyval.treenode),(yyvsp[-1].treenode),1); 
               addChild((yyval.treenode),(yyvsp[0].treenode),2); 
             }
#line 1612 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 152 "./syntax.y" /* yacc.c:1646  */
    { 
               (yyval.treenode) = createNode("OptTag"," ",Node_Program,d_gray); 
               addChild((yyval.treenode),(yyvsp[0].treenode),1); 
             }
#line 1621 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 156 "./syntax.y" /* yacc.c:1646  */
    { (yyval.treenode) = NULL; /*NULL*/}
#line 1627 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 159 "./syntax.y" /* yacc.c:1646  */
    { 
               (yyval.treenode) = createNode("Tag"," ",Node_Program,d_gray); 
               addChild((yyval.treenode),(yyvsp[0].treenode),1); 
             }
#line 1636 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 167 "./syntax.y" /* yacc.c:1646  */
    { 
               (yyval.treenode) = createNode("VarDec"," ",Node_Program,d_gray); 
               addChild((yyval.treenode),(yyvsp[0].treenode),1); 
             }
#line 1645 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 171 "./syntax.y" /* yacc.c:1646  */
    { 
               (yyval.treenode) = createNode("VarDec"," ",Node_Program,d_gray); 
               addChild((yyval.treenode),(yyvsp[-3].treenode),1); 
               addChild((yyval.treenode),(yyvsp[-2].treenode),2); 
               addChild((yyval.treenode),(yyvsp[-1].treenode),3); 
               addChild((yyval.treenode),(yyvsp[0].treenode),4); 
             }
#line 1657 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 178 "./syntax.y" /* yacc.c:1646  */
    { error_exist = true; /*yyerrok;*/ }
#line 1663 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 181 "./syntax.y" /* yacc.c:1646  */
    { 
               (yyval.treenode) = createNode("FunDec"," ",Node_Program,d_gray); 
               addChild((yyval.treenode),(yyvsp[-3].treenode),1); 
               addChild((yyval.treenode),(yyvsp[-2].treenode),2); 
               addChild((yyval.treenode),(yyvsp[-1].treenode),3); 
               addChild((yyval.treenode),(yyvsp[0].treenode),4); 
             }
#line 1675 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 188 "./syntax.y" /* yacc.c:1646  */
    { 
               (yyval.treenode) = createNode("FunDec"," ",Node_Program,d_gray); 
               addChild((yyval.treenode),(yyvsp[-2].treenode),1); 
               addChild((yyval.treenode),(yyvsp[-1].treenode),2); 
               addChild((yyval.treenode),(yyvsp[0].treenode),3); 
             }
#line 1686 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 194 "./syntax.y" /* yacc.c:1646  */
    { error_exist = true; /*yyerrok;*/ }
#line 1692 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 197 "./syntax.y" /* yacc.c:1646  */
    { 
               (yyval.treenode) = createNode("VarList"," ",Node_Program,d_gray);
               addChild((yyval.treenode),(yyvsp[-2].treenode),1); 
               addChild((yyval.treenode),(yyvsp[-1].treenode),2); 
               addChild((yyval.treenode),(yyvsp[0].treenode),3); 
             }
#line 1703 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 203 "./syntax.y" /* yacc.c:1646  */
    { 
               (yyval.treenode) = createNode("VarList"," ",Node_Program,d_gray); 
               addChild((yyval.treenode),(yyvsp[0].treenode),1);
             }
#line 1712 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 209 "./syntax.y" /* yacc.c:1646  */
    { 
               (yyval.treenode) = createNode("ParamDec"," ",Node_Program,d_gray);
               addChild((yyval.treenode),(yyvsp[-1].treenode),1);
               addChild((yyval.treenode),(yyvsp[0].treenode),2); }
#line 1721 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 213 "./syntax.y" /* yacc.c:1646  */
    { error_exist = true;/*yyerrok;*/ }
#line 1727 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 214 "./syntax.y" /* yacc.c:1646  */
    { /*yyerrok;*/ }
#line 1733 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 219 "./syntax.y" /* yacc.c:1646  */
    { 
             (yyval.treenode) = createNode("CompSt"," ",Node_Program,d_gray); 
             addChild((yyval.treenode),(yyvsp[-3].treenode),1); 
             addChild((yyval.treenode),(yyvsp[-2].treenode),2);
             addChild((yyval.treenode),(yyvsp[-1].treenode),3); 
             addChild((yyval.treenode),(yyvsp[0].treenode),4); 
             }
#line 1745 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 227 "./syntax.y" /* yacc.c:1646  */
    { error_exist = true; }
#line 1751 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 230 "./syntax.y" /* yacc.c:1646  */
    { 
               (yyval.treenode) = createNode("StmtList"," ",Node_Program,d_gray); 
               addChild((yyval.treenode),(yyvsp[-1].treenode),1); 
               addChild((yyval.treenode),(yyvsp[0].treenode),2); 
             }
#line 1761 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 235 "./syntax.y" /* yacc.c:1646  */
    { (yyval.treenode) = NULL; /*NULL*/}
#line 1767 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 238 "./syntax.y" /* yacc.c:1646  */
    { 
               (yyval.treenode) = createNode("Stmt"," ",Node_Program,d_gray); 
               addChild((yyval.treenode),(yyvsp[-1].treenode),1); 
               addChild((yyval.treenode),(yyvsp[0].treenode),2); 
             }
#line 1777 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 243 "./syntax.y" /* yacc.c:1646  */
    { 
               (yyval.treenode) = createNode("Stmt"," ",Node_Program,d_gray); 
               addChild((yyval.treenode),(yyvsp[0].treenode),1); 
             }
#line 1786 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 247 "./syntax.y" /* yacc.c:1646  */
    { 
               (yyval.treenode) = createNode("Stmt"," ",Node_Program,d_gray); 
               addChild((yyval.treenode),(yyvsp[-2].treenode),1); 
               addChild((yyval.treenode),(yyvsp[-1].treenode),2); 
               addChild((yyval.treenode),(yyvsp[0].treenode),3); 
             }
#line 1797 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 253 "./syntax.y" /* yacc.c:1646  */
    { 
               (yyval.treenode) = createNode("Stmt"," ",Node_Program,d_gray); 
               addChild((yyval.treenode),(yyvsp[-4].treenode),1); 
               addChild((yyval.treenode),(yyvsp[-3].treenode),2); 
               addChild((yyval.treenode),(yyvsp[-2].treenode),3); 
               addChild((yyval.treenode),(yyvsp[-1].treenode),4);
               addChild((yyval.treenode),(yyvsp[0].treenode),5); 
             }
#line 1810 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 261 "./syntax.y" /* yacc.c:1646  */
    { 
               (yyval.treenode) = createNode("Stmt"," ",Node_Program,d_gray); 
               addChild((yyval.treenode),(yyvsp[-6].treenode),1); 
               addChild((yyval.treenode),(yyvsp[-5].treenode),2); 
               addChild((yyval.treenode),(yyvsp[-4].treenode),3); 
               addChild((yyval.treenode),(yyvsp[-3].treenode),4);
               addChild((yyval.treenode),(yyvsp[-2].treenode),5); 
               addChild((yyval.treenode),(yyvsp[-1].treenode),6);
               addChild((yyval.treenode),(yyvsp[0].treenode),7); 
             }
#line 1825 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 271 "./syntax.y" /* yacc.c:1646  */
    { 
               PrintError("Missing \";\" ?\n");  
               error_exist = true;
               /*yyerrok;*/ 
             }
#line 1835 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 276 "./syntax.y" /* yacc.c:1646  */
    { 
               (yyval.treenode) = createNode("Stmt"," ",Node_Program,d_gray);
               addChild((yyval.treenode),(yyvsp[-4].treenode),1); 
               addChild((yyval.treenode),(yyvsp[-3].treenode),2); 
               addChild((yyval.treenode),(yyvsp[-2].treenode),3); 
               addChild((yyval.treenode),(yyvsp[-1].treenode),4);
               addChild((yyval.treenode),(yyvsp[0].treenode),5);
             }
#line 1848 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 288 "./syntax.y" /* yacc.c:1646  */
    { 
               (yyval.treenode) = createNode("DefList"," ",Node_Program,d_gray); 
               addChild((yyval.treenode),(yyvsp[-1].treenode),1); 
               addChild((yyval.treenode),(yyvsp[0].treenode),2); 
             }
#line 1858 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 293 "./syntax.y" /* yacc.c:1646  */
    { (yyval.treenode) = NULL; /*NULL*/}
#line 1864 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 296 "./syntax.y" /* yacc.c:1646  */
    { 
               (yyval.treenode) = createNode("Def"," ",Node_Program,d_gray); 
               addChild((yyval.treenode),(yyvsp[-2].treenode),1); 
               addChild((yyval.treenode),(yyvsp[-1].treenode),2); 
               addChild((yyval.treenode),(yyvsp[0].treenode),3); 
             }
#line 1875 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 303 "./syntax.y" /* yacc.c:1646  */
    {}
#line 1881 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 306 "./syntax.y" /* yacc.c:1646  */
    { 
               (yyval.treenode) = createNode("DecList"," ",Node_Program,d_gray); 
               addChild((yyval.treenode),(yyvsp[0].treenode),1); 
             }
#line 1890 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 310 "./syntax.y" /* yacc.c:1646  */
    { 
               (yyval.treenode) = createNode("DecList"," ",Node_Program,d_gray);
               addChild((yyval.treenode),(yyvsp[-2].treenode),1);
               addChild((yyval.treenode),(yyvsp[-1].treenode),2);
               addChild((yyval.treenode),(yyvsp[0].treenode),3); 
             }
#line 1901 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 318 "./syntax.y" /* yacc.c:1646  */
    { 
               (yyval.treenode) = createNode("Dec"," ",Node_Program,d_gray); 
               addChild((yyval.treenode),(yyvsp[0].treenode),1); 
             }
#line 1910 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 322 "./syntax.y" /* yacc.c:1646  */
    { 
               (yyval.treenode) = createNode("Dec"," ",Node_Program,d_gray); 
               addChild((yyval.treenode),(yyvsp[-2].treenode),1); 
               addChild((yyval.treenode),(yyvsp[-1].treenode),2);
               addChild((yyval.treenode),(yyvsp[0].treenode),3); 
             }
#line 1921 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 332 "./syntax.y" /* yacc.c:1646  */
    { 
              (yyval.treenode) = createNode("Exp"," ",Node_Program,d_gray); 
              addChild((yyval.treenode),(yyvsp[-2].treenode),1);
              addChild((yyval.treenode),(yyvsp[-1].treenode),2);
              addChild((yyval.treenode),(yyvsp[0].treenode),3); 
            }
#line 1932 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 338 "./syntax.y" /* yacc.c:1646  */
    { 
              (yyval.treenode) = createNode("Exp"," ",Node_Program,d_gray);
              addChild((yyval.treenode),(yyvsp[-2].treenode),1);
              addChild((yyval.treenode),(yyvsp[-1].treenode),2);
              addChild((yyval.treenode),(yyvsp[0].treenode),3);
            }
#line 1943 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 344 "./syntax.y" /* yacc.c:1646  */
    { 
              (yyval.treenode) = createNode("Exp"," ",Node_Program,d_gray); 
              addChild((yyval.treenode),(yyvsp[-2].treenode),1); 
              addChild((yyval.treenode),(yyvsp[-1].treenode),2);
              addChild((yyval.treenode),(yyvsp[0].treenode),3); 
            }
#line 1954 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 350 "./syntax.y" /* yacc.c:1646  */
    { 
              (yyval.treenode) = createNode("Exp"," ",Node_Program,d_gray);
              addChild((yyval.treenode),(yyvsp[-2].treenode),1); 
              addChild((yyval.treenode),(yyvsp[-1].treenode),2); 
              addChild((yyval.treenode),(yyvsp[0].treenode),3); 
            }
#line 1965 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 356 "./syntax.y" /* yacc.c:1646  */
    { 
              (yyval.treenode) = createNode("Exp"," ",Node_Program,d_gray);
              addChild((yyval.treenode),(yyvsp[-2].treenode),1); 
              addChild((yyval.treenode),(yyvsp[-1].treenode),2);
              addChild((yyval.treenode),(yyvsp[0].treenode),3); 
            }
#line 1976 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 362 "./syntax.y" /* yacc.c:1646  */
    { 
              (yyval.treenode) = createNode("Exp"," ",Node_Program,d_gray); 
              addChild((yyval.treenode),(yyvsp[-2].treenode),1); 
              addChild((yyval.treenode),(yyvsp[-1].treenode),2); 
              addChild((yyval.treenode),(yyvsp[0].treenode),3); 
            }
#line 1987 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 368 "./syntax.y" /* yacc.c:1646  */
    { 
              (yyval.treenode) = createNode("Exp"," ",Node_Program,d_gray); 
              addChild((yyval.treenode),(yyvsp[-2].treenode),1); 
              addChild((yyval.treenode),(yyvsp[-1].treenode),2);
              addChild((yyval.treenode),(yyvsp[0].treenode),3);
            }
#line 1998 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 374 "./syntax.y" /* yacc.c:1646  */
    { 
              (yyval.treenode) = createNode("Expf"," ",Node_Program,d_gray); 
              addChild((yyval.treenode),(yyvsp[-2].treenode),1); 
              addChild((yyval.treenode),(yyvsp[-1].treenode),2); 
              addChild((yyval.treenode),(yyvsp[0].treenode),3); 
            }
#line 2009 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 380 "./syntax.y" /* yacc.c:1646  */
    { 
              (yyval.treenode) = createNode("Exp"," ",Node_Program,d_gray); 
              addChild((yyval.treenode),(yyvsp[-2].treenode),1);
              addChild((yyval.treenode),(yyvsp[-1].treenode),2);
              addChild((yyval.treenode),(yyvsp[0].treenode),3); 
            }
#line 2020 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 386 "./syntax.y" /* yacc.c:1646  */
    { 
              (yyval.treenode) = createNode("Exp"," ",Node_Program,d_gray); 
              addChild((yyval.treenode),(yyvsp[-1].treenode),1);
              addChild((yyval.treenode),(yyvsp[0].treenode),2); 
            }
#line 2030 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 391 "./syntax.y" /* yacc.c:1646  */
    {
              (yyval.treenode) = createNode("Exp"," ",Node_Program,d_gray);
              addChild((yyval.treenode),(yyvsp[-1].treenode),1);
              addChild((yyval.treenode),(yyvsp[0].treenode),2);
            }
#line 2040 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 396 "./syntax.y" /* yacc.c:1646  */
    { 
              (yyval.treenode) = createNode("Exp"," ",Node_Program,d_gray); 
              addChild((yyval.treenode),(yyvsp[-3].treenode),1);
              addChild((yyval.treenode),(yyvsp[-2].treenode),2); 
              addChild((yyval.treenode),(yyvsp[-1].treenode),3);
              addChild((yyval.treenode),(yyvsp[0].treenode),4); 
            }
#line 2052 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 403 "./syntax.y" /* yacc.c:1646  */
    { 
              (yyval.treenode) = createNode("Exp"," ",Node_Program,d_gray);
              addChild((yyval.treenode),(yyvsp[-2].treenode),1);
              addChild((yyval.treenode),(yyvsp[-1].treenode),2);
              addChild((yyval.treenode),(yyvsp[0].treenode),3); 
            }
#line 2063 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 409 "./syntax.y" /* yacc.c:1646  */
    { 
              (yyval.treenode) = createNode("Exp"," ",Node_Program,d_gray); 
              addChild((yyval.treenode),(yyvsp[-3].treenode),1); 
              addChild((yyval.treenode),(yyvsp[-2].treenode),2);
              addChild((yyval.treenode),(yyvsp[-1].treenode),3); 
              addChild((yyval.treenode),(yyvsp[0].treenode),4);
            }
#line 2075 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 416 "./syntax.y" /* yacc.c:1646  */
    { 
              PrintError("Missing \"]\" ?\n");
              error_exist = true;
              /*yyerrok;*/ 
            }
#line 2085 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 421 "./syntax.y" /* yacc.c:1646  */
    { 
              (yyval.treenode) = createNode("Exp"," ",Node_Program,d_gray); 
              addChild((yyval.treenode),(yyvsp[-2].treenode),1); 
              addChild((yyval.treenode),(yyvsp[-1].treenode),2); 
              addChild((yyval.treenode),(yyvsp[0].treenode),3); 
            }
#line 2096 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 427 "./syntax.y" /* yacc.c:1646  */
    { 
              (yyval.treenode) = createNode("Exp"," ",Node_Program,d_gray);
              addChild((yyval.treenode),(yyvsp[0].treenode),1); 
            }
#line 2105 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 431 "./syntax.y" /* yacc.c:1646  */
    { 
              (yyval.treenode) = createNode("Exp"," ",Node_Program,d_gray); 
              addChild((yyval.treenode),(yyvsp[0].treenode),1); 
            }
#line 2114 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 435 "./syntax.y" /* yacc.c:1646  */
    { 
              (yyval.treenode) = createNode("Exp"," ",Node_Program,d_gray); 
              addChild((yyval.treenode),(yyvsp[0].treenode),1); 
            }
#line 2123 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 441 "./syntax.y" /* yacc.c:1646  */
    { 
              (yyval.treenode) = createNode("Args"," ",Node_Program,d_gray); 
              addChild((yyval.treenode),(yyvsp[-2].treenode),1); 
              addChild((yyval.treenode),(yyvsp[-1].treenode),2); 
              addChild((yyval.treenode),(yyvsp[0].treenode),3); 
            }
#line 2134 "./syntax.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 447 "./syntax.y" /* yacc.c:1646  */
    { 
              (yyval.treenode) = createNode("Args"," ",Node_Program,d_gray); 
              addChild((yyval.treenode),(yyvsp[0].treenode),1);
            }
#line 2143 "./syntax.tab.c" /* yacc.c:1646  */
    break;


#line 2147 "./syntax.tab.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }

  yyerror_range[1] = yylloc;

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
                      yytoken, &yylval, &yylloc);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  yyerror_range[1] = yylsp[1-yylen];
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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 484 "./syntax.y" /* yacc.c:1906  */

int main(int argc,char **argv)
{
  FILE* f=fopen(argv[1],"r");
  if(!f){ 
    perror(argv[1]);
    return 1;
  } 
  yylineno=1;
  //yyin=f;  
  yyrestart(f);
  yyparse();
  if(!error_exist){
    //No tree will be printed;
    //printTree(Root,0);
    initHashTable();
    traverse(Root);
    //validateTable();
    //debugShowSymbol();
  }
  else
    PrintHint("Solve the errors come first\n");
  return 0;
}

int yyerror(const char *s)
{
  fprintf(stderr, NONE"Error type B at Line %d:%s\n",yylineno,s);
  //fprintf(stderr, "error: %s\n", s);
}

