
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
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
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0

/* Substitute the variable and function names.  */
#define yyparse         Cminus_parse
#define yylex           Cminus_lex
#define yyerror         Cminus_error
#define yylval          Cminus_lval
#define yychar          Cminus_char
#define yydebug         Cminus_debug
#define yynerrs         Cminus_nerrs


/* Copy the first part of user declarations.  */

/* Line 189 of yacc.c  */
#line 7 "CminusParser.y"

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <util/general.h>
#include <util/symtab.h>
#include <util/symtab_stack.h>
#include <util/dlink.h>
#include <util/string_utils.h>
#include <codegen/symfields.h>
#include <codegen/types.h>
#include <codegen/codegen.h>
#include <codegen/reg.h>

#define SYMTABLE_SIZE 100

/*********************EXTERNAL DECLARATIONS***********************/

EXTERN(void,Cminus_error,(char*));

EXTERN(int,Cminus_lex,(void));

SymTable symtab;
SymtabStack symstack;

static DList instList;
static DList dataList;

char *fileName;

static int functionOffset;
int globalOffset = 0;

static char* functionName;
extern union YYSTYPE yylval;
extern int Cminus_lineno;



/* Line 189 of yacc.c  */
#line 122 "CminusParser.c"

/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     AND = 258,
     ELSE = 259,
     EXIT = 260,
     FLOAT = 261,
     FOR = 262,
     IF = 263,
     INTEGER = 264,
     NOT = 265,
     OR = 266,
     READ = 267,
     WHILE = 268,
     WRITE = 269,
     LBRACE = 270,
     RBRACE = 271,
     LE = 272,
     LT = 273,
     GE = 274,
     GT = 275,
     EQ = 276,
     NE = 277,
     ASSIGN = 278,
     COMMA = 279,
     SEMICOLON = 280,
     LBRACKET = 281,
     RBRACKET = 282,
     LPAREN = 283,
     RPAREN = 284,
     PLUS = 285,
     TIMES = 286,
     IDENTIFIER = 287,
     DIVIDE = 288,
     RETURN = 289,
     STRING = 290,
     INTCON = 291,
     FLOATCON = 292,
     MINUS = 293,
     DIVDE = 294
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 214 of yacc.c  */
#line 96 "CminusParser.y"

	char*	name;
	int     symIndex;
	DList	idList;
	int 	offset;



/* Line 214 of yacc.c  */
#line 206 "CminusParser.c"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif


/* Copy the second part of user declarations.  */


/* Line 264 of yacc.c  */
#line 218 "CminusParser.c"

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
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
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
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
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
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
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
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   145

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  32
/* YYNRULES -- Number of rules.  */
#define YYNRULES  66
/* YYNRULES -- Number of states.  */
#define YYNSTATES  131

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   294

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     8,    11,    12,    15,    18,    20,
      26,    29,    33,    38,    40,    44,    46,    51,    53,    55,
      57,    59,    61,    63,    65,    67,    69,    74,    79,    82,
      85,    89,    93,    97,    99,   105,   111,   117,   121,   124,
     128,   130,   133,   135,   139,   143,   146,   148,   152,   156,
     160,   164,   168,   172,   174,   178,   182,   184,   188,   192,
     194,   196,   200,   204,   206,   211,   213
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      41,     0,    -1,    42,    -1,    47,    42,    -1,    43,    42,
      -1,    -1,    44,    46,    -1,    45,    47,    -1,    45,    -1,
      50,    32,    28,    29,    15,    -1,    63,    16,    -1,    50,
      48,    25,    -1,    47,    50,    48,    25,    -1,    49,    -1,
      48,    24,    49,    -1,    32,    -1,    32,    26,    36,    27,
      -1,     9,    -1,     6,    -1,    52,    -1,    53,    -1,    56,
      -1,    59,    -1,    60,    -1,    61,    -1,    62,    -1,    69,
      23,    64,    25,    -1,     8,    54,     4,    62,    -1,     8,
      54,    -1,    55,    62,    -1,    28,    64,    29,    -1,    58,
      57,    51,    -1,    28,    64,    29,    -1,    13,    -1,    12,
      28,    69,    29,    25,    -1,    14,    28,    64,    29,    25,
      -1,    14,    28,    70,    29,    25,    -1,    34,    64,    25,
      -1,     5,    25,    -1,    15,    63,    16,    -1,    51,    -1,
      63,    51,    -1,    65,    -1,    64,    11,    65,    -1,    64,
       3,    65,    -1,    10,    65,    -1,    66,    -1,    65,    21,
      66,    -1,    65,    22,    66,    -1,    65,    17,    66,    -1,
      65,    18,    66,    -1,    65,    19,    66,    -1,    65,    20,
      66,    -1,    67,    -1,    66,    30,    67,    -1,    66,    38,
      67,    -1,    68,    -1,    67,    31,    68,    -1,    67,    33,
      68,    -1,    69,    -1,    71,    -1,    32,    28,    29,    -1,
      28,    64,    29,    -1,    32,    -1,    32,    26,    64,    27,
      -1,    35,    -1,    36,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   111,   111,   114,   120,   122,   126,   136,   142,   149,
     154,   158,   167,   178,   181,   186,   188,   208,   210,   212,
     214,   216,   218,   220,   222,   224,   228,   232,   234,   238,
     242,   246,   250,   254,   258,   260,   262,   266,   270,   274,
     278,   280,   284,   286,   288,   290,   294,   296,   298,   300,
     302,   304,   306,   310,   312,   314,   318,   320,   322,   326,
     328,   330,   332,   336,   338,   342,   347
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "AND", "ELSE", "EXIT", "FLOAT", "FOR",
  "IF", "INTEGER", "NOT", "OR", "READ", "WHILE", "WRITE", "LBRACE",
  "RBRACE", "LE", "LT", "GE", "GT", "EQ", "NE", "ASSIGN", "COMMA",
  "SEMICOLON", "LBRACKET", "RBRACKET", "LPAREN", "RPAREN", "PLUS", "TIMES",
  "IDENTIFIER", "DIVIDE", "RETURN", "STRING", "INTCON", "FLOATCON",
  "MINUS", "DIVDE", "$accept", "Program", "Procedures", "ProcedureDecl",
  "ProcedureHead", "FunctionDecl", "ProcedureBody", "DeclList",
  "IdentifierList", "VarDecl", "Type", "Statement", "Assignment",
  "IfStatement", "TestAndThen", "Test", "WhileStatement", "WhileExpr",
  "WhileToken", "IOStatement", "ReturnStatement", "ExitStatement",
  "CompoundStatement", "StatementList", "Expr", "SimpleExpr", "AddExpr",
  "MulExpr", "Factor", "Variable", "StringConstant", "Constant", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    40,    41,    41,    42,    42,    43,    44,    44,    45,
      46,    47,    47,    48,    48,    49,    49,    50,    50,    51,
      51,    51,    51,    51,    51,    51,    52,    53,    53,    54,
      55,    56,    57,    58,    59,    59,    59,    60,    61,    62,
      63,    63,    64,    64,    64,    64,    65,    65,    65,    65,
      65,    65,    65,    66,    66,    66,    67,    67,    67,    68,
      68,    68,    68,    69,    69,    70,    71
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     0,     2,     2,     1,     5,
       2,     3,     4,     1,     3,     1,     4,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     4,     4,     2,     2,
       3,     3,     3,     1,     5,     5,     5,     3,     2,     3,
       1,     2,     1,     3,     3,     2,     1,     3,     3,     3,
       3,     3,     3,     1,     3,     3,     1,     3,     3,     1,
       1,     3,     3,     1,     4,     1,     1
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       5,    18,    17,     0,     2,     5,     0,     8,     5,     0,
       1,     4,     0,     0,     0,     0,    33,     0,     0,    63,
       0,     6,    40,    19,    20,    21,     0,    22,    23,    24,
      25,     0,     0,     7,     0,     3,     0,    15,     0,    13,
       0,    38,     0,    28,     0,     0,     0,     0,     0,     0,
       0,    63,    66,     0,    42,    46,    53,    56,    59,    60,
       0,     0,    10,    41,     0,     0,    15,     0,     0,     0,
       0,    11,     0,     0,    29,     0,    65,     0,     0,    39,
       0,    45,     0,     0,     0,     0,    37,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    31,     0,
      12,     0,     0,    14,    30,    27,     0,     0,     0,    64,
      62,    61,    44,    43,    49,    50,    51,    52,    47,    48,
      54,    55,    57,    58,    32,    26,    16,     9,    34,    35,
      36
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     3,     4,     5,     6,     7,    21,     8,    38,    39,
       9,    22,    23,    24,    43,    44,    25,    61,    26,    27,
      28,    29,    30,    31,    53,    54,    55,    56,    57,    58,
      78,    59
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -49
static const yytype_int8 yypact[] =
{
      -2,   -49,   -49,     3,   -49,    -2,    37,    -2,    -2,   -12,
     -49,   -49,     6,    18,    46,    64,   -49,    80,    37,    52,
      34,   -49,   -49,   -49,   -49,   -49,    95,   -49,   -49,   -49,
     -49,     1,    40,    -2,    72,   -49,   -12,   -18,    76,   -49,
      98,   -49,    34,   125,   115,    99,    48,    14,    34,    66,
      34,    71,   -49,    78,    94,    35,    44,   -49,   -49,   -49,
      34,    37,   -49,   -49,    34,    72,   106,    82,    97,   105,
      72,   -49,    50,   115,   -49,   107,   -49,    56,   108,   -49,
      20,    94,    57,   109,    66,    66,   -49,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    66,    61,   -49,    85,
     -49,   112,   120,   -49,   -49,   -49,   116,   117,   118,   -49,
     -49,   -49,    94,    94,    35,    35,    35,    35,    35,    35,
      44,    44,   -49,   -49,   -49,   -49,   -49,   -49,   -49,   -49,
     -49
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -49,   -49,    16,   -49,   -49,   -49,   -49,   133,   -31,    74,
      49,   -29,   -49,   -49,   -49,   -49,   -49,   -49,   -49,   -49,
     -49,   -49,   -33,   127,    45,   -48,    30,    31,    32,    -6,
     -49,   -49
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const yytype_uint8 yytable[] =
{
      32,    81,    63,    10,     1,    67,    13,     2,    68,    14,
      69,    74,    32,    15,    16,    17,    18,    62,    63,    13,
      37,    11,    14,    84,    35,    32,    15,    16,    17,    18,
      79,    85,    98,    19,    67,    20,   112,   113,    40,    75,
     105,    32,    13,    41,    49,    14,    19,   109,    20,    15,
      16,    17,    18,    84,    12,    32,    34,    36,    49,    84,
      84,    85,    50,    64,    84,    93,    51,    85,    85,    19,
      52,    20,    85,    94,    42,    95,    50,    96,    48,   104,
      51,    84,    65,    76,    52,   107,   110,    72,    84,    85,
     124,    77,    45,    80,    50,    82,    85,    48,    51,    83,
      70,    71,    52,    86,    66,    97,    70,   100,    46,    99,
     125,    87,    88,    89,    90,    91,    92,   114,   115,   116,
     117,   118,   119,    60,   120,   121,    69,   122,   123,    73,
      18,    19,    68,   101,   102,   127,   106,   108,   111,   126,
      33,   128,   129,   130,   103,    47
};

static const yytype_uint8 yycheck[] =
{
       6,    49,    31,     0,     6,    36,     5,     9,    26,     8,
      28,    44,    18,    12,    13,    14,    15,    16,    47,     5,
      32,     5,     8,     3,     8,    31,    12,    13,    14,    15,
      16,    11,    61,    32,    65,    34,    84,    85,    32,    45,
      73,    47,     5,    25,    10,     8,    32,    27,    34,    12,
      13,    14,    15,     3,     5,    61,     7,     8,    10,     3,
       3,    11,    28,    23,     3,    30,    32,    11,    11,    32,
      36,    34,    11,    38,    28,    31,    28,    33,    26,    29,
      32,     3,    33,    35,    36,    29,    29,    42,     3,    11,
      29,    46,    28,    48,    28,    50,    11,    26,    32,    28,
      24,    25,    36,    25,    32,    60,    24,    25,    28,    64,
      25,    17,    18,    19,    20,    21,    22,    87,    88,    89,
      90,    91,    92,    28,    93,    94,    28,    95,    96,     4,
      15,    32,    26,    36,    29,    15,    29,    29,    29,    27,
       7,    25,    25,    25,    70,    18
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     6,     9,    41,    42,    43,    44,    45,    47,    50,
       0,    42,    50,     5,     8,    12,    13,    14,    15,    32,
      34,    46,    51,    52,    53,    56,    58,    59,    60,    61,
      62,    63,    69,    47,    50,    42,    50,    32,    48,    49,
      32,    25,    28,    54,    55,    28,    28,    63,    26,    10,
      28,    32,    36,    64,    65,    66,    67,    68,    69,    71,
      28,    57,    16,    51,    23,    50,    32,    48,    26,    28,
      24,    25,    64,     4,    62,    69,    35,    64,    70,    16,
      64,    65,    64,    28,     3,    11,    25,    17,    18,    19,
      20,    21,    22,    30,    38,    31,    33,    64,    51,    64,
      25,    36,    29,    49,    29,    62,    29,    29,    29,    27,
      29,    29,    65,    65,    66,    66,    66,    66,    66,    66,
      67,    67,    68,    68,    29,    25,    27,    15,    25,    25,
      25
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule)
#else
static void
yy_reduce_print (yyvsp, yyrule)
    YYSTYPE *yyvsp;
    int yyrule;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule); \
} while (YYID (0))

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
#ifndef	YYINITDEPTH
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
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
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
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

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yymsg, yytype, yyvaluep)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  YYUSE (yyvaluep);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */


/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{


    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

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

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

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
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

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
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
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
      if (yyn == 0 || yyn == YYTABLE_NINF)
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
  *++yyvsp = yylval;

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
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

/* Line 1455 of yacc.c  */
#line 111 "CminusParser.y"
    {
	emitDataPrologue(dataList);
	emitInstructions(instList);
;}
    break;

  case 3:

/* Line 1455 of yacc.c  */
#line 114 "CminusParser.y"
    {
	globalOffset = (yyvsp[(1) - (2)].offset);
	emitDataPrologue(dataList);
	emitInstructions(instList);
;}
    break;

  case 4:

/* Line 1455 of yacc.c  */
#line 120 "CminusParser.y"
    {

;}
    break;

  case 5:

/* Line 1455 of yacc.c  */
#line 122 "CminusParser.y"
    {

;}
    break;

  case 6:

/* Line 1455 of yacc.c  */
#line 126 "CminusParser.y"
    {
	emitEndFunction(instList);
	symtab = endScope(symstack);
	SymKillField(symtab,SYMTAB_REGISTER_INDEX_FIELD);
    SymKillField(symtab,SYMTAB_OFFSET_FIELD);
    SymKill(symtab);
	symtab = currentSymtab(symstack);
	emitExit(instList);
;}
    break;

  case 7:

/* Line 1455 of yacc.c  */
#line 136 "CminusParser.y"
    {
	emitProcedurePrologue(instList,symtab,(yyvsp[(1) - (2)].symIndex));
	emitStartFunction(instList, (yyvsp[(2) - (2)].offset));
	functionOffset = (yyvsp[(2) - (2)].offset);
	(yyval.symIndex) = (yyvsp[(1) - (2)].symIndex);
	
;}
    break;

  case 8:

/* Line 1455 of yacc.c  */
#line 142 "CminusParser.y"
    {
	emitProcedurePrologue(instList,symtab,(yyvsp[(1) - (1)].symIndex));
	emitStartFunction(instList, 0);
	functionOffset = 0;
	(yyval.symIndex) = (yyvsp[(1) - (1)].symIndex);
;}
    break;

  case 9:

/* Line 1455 of yacc.c  */
#line 149 "CminusParser.y"
    {
	symtab = beginScope(symstack);
	(yyval.symIndex) = SymIndex(symtab,(yyvsp[(2) - (5)].name));
;}
    break;

  case 10:

/* Line 1455 of yacc.c  */
#line 154 "CminusParser.y"
    {
	
;}
    break;

  case 11:

/* Line 1455 of yacc.c  */
#line 158 "CminusParser.y"
    {
	AddIdStructPtr data = (AddIdStructPtr)malloc(sizeof(AddIdStruct));
	data->offset = 0;
	data->symtab = symtab;
    data->typeIndex = (yyvsp[(1) - (3)].symIndex);
	dlinkApply1((yyvsp[(2) - (3)].idList),(DLinkApply1Func)addIdToSymtab,(Generic)data);
	(yyval.offset) = data->offset;
	dlinkFreeNodes((yyvsp[(2) - (3)].idList));
	free(data);
;}
    break;

  case 12:

/* Line 1455 of yacc.c  */
#line 167 "CminusParser.y"
    {
	AddIdStructPtr data = (AddIdStructPtr)malloc(sizeof(AddIdStruct));
	data->offset = (yyvsp[(1) - (4)].offset);
	data->typeIndex = (yyvsp[(2) - (4)].symIndex);
	data->symtab = symtab;
	dlinkApply1((yyvsp[(3) - (4)].idList),(DLinkApply1Func)addIdToSymtab,(Generic)data);
	(yyval.offset) = data->offset;
	dlinkFreeNodes((yyvsp[(3) - (4)].idList));
	free(data);
;}
    break;

  case 13:

/* Line 1455 of yacc.c  */
#line 178 "CminusParser.y"
    {
	(yyval.idList) = dlinkListAlloc(NULL);
	dlinkAppend((yyval.idList),dlinkNodeAlloc((Generic)(yyvsp[(1) - (1)].symIndex)));
;}
    break;

  case 14:

/* Line 1455 of yacc.c  */
#line 181 "CminusParser.y"
    {
	dlinkAppend((yyvsp[(1) - (3)].idList),dlinkNodeAlloc((Generic)(yyvsp[(3) - (3)].symIndex)));
	(yyval.idList) = (yyvsp[(1) - (3)].idList);
;}
    break;

  case 15:

/* Line 1455 of yacc.c  */
#line 186 "CminusParser.y"
    {
	(yyval.symIndex) = SymIndex(symtab,(yyvsp[(1) - (1)].name));
;}
    break;

  case 16:

/* Line 1455 of yacc.c  */
#line 188 "CminusParser.y"
    {
	int symIndex = SymIndex(symtab,(yyvsp[(3) - (4)].name));
	char* numElemString = (char*)SymGetFieldByIndex(symtab,symIndex,SYM_NAME_FIELD);
		
	char* typeString = nssave(4,SYMTAB_VOID_TYPE_STRING,"[",numElemString,"]");
		
	int typeIndex = SymIndex(symtab,typeString);
	SymPutFieldByIndex(symtab,typeIndex,SYMTAB_BASIC_TYPE_FIELD,(Generic)VOID_TYPE);
	
	int numElements = atoi(numElemString);
	SymPutFieldByIndex(symtab,typeIndex,SYMTAB_SIZE_FIELD,(Generic)(VOID_SIZE*numElements));
					   
	sfree(typeString);

	symIndex = SymIndex(symtab,(yyvsp[(1) - (4)].name));
    SymPutFieldByIndex(symtab,symIndex,SYMTAB_TYPE_INDEX_FIELD,(Generic)typeIndex);

	(yyval.symIndex) = symIndex;		  
;}
    break;

  case 17:

/* Line 1455 of yacc.c  */
#line 208 "CminusParser.y"
    {
    (yyval.symIndex) = SymQueryIndex(symtab,SYMTAB_INTEGER_TYPE_STRING);
;}
    break;

  case 19:

/* Line 1455 of yacc.c  */
#line 212 "CminusParser.y"
    {
	
;}
    break;

  case 20:

/* Line 1455 of yacc.c  */
#line 214 "CminusParser.y"
    {
	
;}
    break;

  case 21:

/* Line 1455 of yacc.c  */
#line 216 "CminusParser.y"
    {
	
;}
    break;

  case 22:

/* Line 1455 of yacc.c  */
#line 218 "CminusParser.y"
    {
	
;}
    break;

  case 23:

/* Line 1455 of yacc.c  */
#line 220 "CminusParser.y"
    {
	emitReturnFunction(instList, lastSymtab(symstack), symtab, (yyvsp[(1) - (1)].symIndex));
;}
    break;

  case 24:

/* Line 1455 of yacc.c  */
#line 222 "CminusParser.y"
    {
	
;}
    break;

  case 25:

/* Line 1455 of yacc.c  */
#line 224 "CminusParser.y"
    {
	
;}
    break;

  case 26:

/* Line 1455 of yacc.c  */
#line 228 "CminusParser.y"
    {
	emitAssignment(instList,lastSymtab(symstack),symtab,(yyvsp[(1) - (4)].symIndex),(yyvsp[(3) - (4)].symIndex));
;}
    break;

  case 27:

/* Line 1455 of yacc.c  */
#line 232 "CminusParser.y"
    {
	emitEndBranchTarget(instList,symtab,(yyvsp[(2) - (4)].symIndex));
;}
    break;

  case 28:

/* Line 1455 of yacc.c  */
#line 234 "CminusParser.y"
    {
	emitEndBranchTarget(instList,symtab,(yyvsp[(2) - (2)].symIndex));
;}
    break;

  case 29:

/* Line 1455 of yacc.c  */
#line 238 "CminusParser.y"
    {
	(yyval.symIndex) = emitThenBranch(instList,symtab,(yyvsp[(1) - (2)].symIndex));
;}
    break;

  case 30:

/* Line 1455 of yacc.c  */
#line 242 "CminusParser.y"
    {
	(yyval.symIndex) = emitIfTest(instList,symtab,(yyvsp[(2) - (3)].symIndex));
;}
    break;

  case 31:

/* Line 1455 of yacc.c  */
#line 246 "CminusParser.y"
    {
	emitWhileLoopBackBranch(instList,symtab,(yyvsp[(1) - (3)].symIndex),(yyvsp[(2) - (3)].symIndex));
;}
    break;

  case 32:

/* Line 1455 of yacc.c  */
#line 250 "CminusParser.y"
    {
	(yyval.symIndex) = emitWhileLoopTest(instList,symtab,(yyvsp[(2) - (3)].symIndex));
;}
    break;

  case 33:

/* Line 1455 of yacc.c  */
#line 254 "CminusParser.y"
    {
	(yyval.symIndex) = emitWhileLoopLandingPad(instList,symtab);
;}
    break;

  case 34:

/* Line 1455 of yacc.c  */
#line 258 "CminusParser.y"
    {
	emitReadVariable(instList,symtab,(yyvsp[(3) - (5)].symIndex));
;}
    break;

  case 35:

/* Line 1455 of yacc.c  */
#line 260 "CminusParser.y"
    {
	emitWriteExpression(instList,symtab,(yyvsp[(3) - (5)].symIndex),SYSCALL_PRINT_INTEGER);
;}
    break;

  case 36:

/* Line 1455 of yacc.c  */
#line 262 "CminusParser.y"
    {
	emitWriteExpression(instList,symtab,(yyvsp[(3) - (5)].symIndex),SYSCALL_PRINT_STRING);
;}
    break;

  case 37:

/* Line 1455 of yacc.c  */
#line 266 "CminusParser.y"
    {
	(yyval.symIndex) = (yyvsp[(2) - (3)].symIndex);
;}
    break;

  case 38:

/* Line 1455 of yacc.c  */
#line 270 "CminusParser.y"
    {
	emitExit(instList);
;}
    break;

  case 39:

/* Line 1455 of yacc.c  */
#line 274 "CminusParser.y"
    {
	
;}
    break;

  case 40:

/* Line 1455 of yacc.c  */
#line 278 "CminusParser.y"
    {
	
;}
    break;

  case 41:

/* Line 1455 of yacc.c  */
#line 280 "CminusParser.y"
    {

;}
    break;

  case 42:

/* Line 1455 of yacc.c  */
#line 284 "CminusParser.y"
    {
	(yyval.symIndex) = (yyvsp[(1) - (1)].symIndex);
;}
    break;

  case 43:

/* Line 1455 of yacc.c  */
#line 286 "CminusParser.y"
    {
	(yyval.symIndex) = emitOrExpression(instList,symtab,(yyvsp[(1) - (3)].symIndex),(yyvsp[(3) - (3)].symIndex));
;}
    break;

  case 44:

/* Line 1455 of yacc.c  */
#line 288 "CminusParser.y"
    {
	(yyval.symIndex) = emitAndExpression(instList,symtab,(yyvsp[(1) - (3)].symIndex),(yyvsp[(3) - (3)].symIndex));
;}
    break;

  case 45:

/* Line 1455 of yacc.c  */
#line 290 "CminusParser.y"
    {
	(yyval.symIndex) = emitNotExpression(instList,symtab,(yyvsp[(2) - (2)].symIndex));
;}
    break;

  case 46:

/* Line 1455 of yacc.c  */
#line 294 "CminusParser.y"
    {
	(yyval.symIndex) = (yyvsp[(1) - (1)].symIndex); 
;}
    break;

  case 47:

/* Line 1455 of yacc.c  */
#line 296 "CminusParser.y"
    {
	(yyval.symIndex) = emitEqualExpression(instList,symtab,(yyvsp[(1) - (3)].symIndex),(yyvsp[(3) - (3)].symIndex));
;}
    break;

  case 48:

/* Line 1455 of yacc.c  */
#line 298 "CminusParser.y"
    {
	(yyval.symIndex) = emitNotEqualExpression(instList,symtab,(yyvsp[(1) - (3)].symIndex),(yyvsp[(3) - (3)].symIndex));
;}
    break;

  case 49:

/* Line 1455 of yacc.c  */
#line 300 "CminusParser.y"
    {
	(yyval.symIndex) = emitLessEqualExpression(instList,symtab,(yyvsp[(1) - (3)].symIndex),(yyvsp[(3) - (3)].symIndex));
;}
    break;

  case 50:

/* Line 1455 of yacc.c  */
#line 302 "CminusParser.y"
    {
	(yyval.symIndex) = emitLessThanExpression(instList,symtab,(yyvsp[(1) - (3)].symIndex),(yyvsp[(3) - (3)].symIndex));
;}
    break;

  case 51:

/* Line 1455 of yacc.c  */
#line 304 "CminusParser.y"
    {
	(yyval.symIndex) = emitGreaterEqualExpression(instList,symtab,(yyvsp[(1) - (3)].symIndex),(yyvsp[(3) - (3)].symIndex));
;}
    break;

  case 52:

/* Line 1455 of yacc.c  */
#line 306 "CminusParser.y"
    {
	(yyval.symIndex) = emitGreaterThanExpression(instList,symtab,(yyvsp[(1) - (3)].symIndex),(yyvsp[(3) - (3)].symIndex));
;}
    break;

  case 53:

/* Line 1455 of yacc.c  */
#line 310 "CminusParser.y"
    {
	(yyval.symIndex) = (yyvsp[(1) - (1)].symIndex); 
;}
    break;

  case 54:

/* Line 1455 of yacc.c  */
#line 312 "CminusParser.y"
    {
	(yyval.symIndex) = emitAddExpression(instList,symtab,(yyvsp[(1) - (3)].symIndex),(yyvsp[(3) - (3)].symIndex));
;}
    break;

  case 55:

/* Line 1455 of yacc.c  */
#line 314 "CminusParser.y"
    {
	(yyval.symIndex) = emitSubtractExpression(instList,symtab,(yyvsp[(1) - (3)].symIndex),(yyvsp[(3) - (3)].symIndex));
;}
    break;

  case 56:

/* Line 1455 of yacc.c  */
#line 318 "CminusParser.y"
    {
	(yyval.symIndex) = (yyvsp[(1) - (1)].symIndex); 
;}
    break;

  case 57:

/* Line 1455 of yacc.c  */
#line 320 "CminusParser.y"
    {
	(yyval.symIndex) = emitMultiplyExpression(instList,symtab,(yyvsp[(1) - (3)].symIndex),(yyvsp[(3) - (3)].symIndex));
;}
    break;

  case 58:

/* Line 1455 of yacc.c  */
#line 322 "CminusParser.y"
    {
	(yyval.symIndex) = emitDivideExpression(instList,symtab,(yyvsp[(1) - (3)].symIndex),(yyvsp[(3) - (3)].symIndex));
;}
    break;

  case 59:

/* Line 1455 of yacc.c  */
#line 326 "CminusParser.y"
    {
	(yyval.symIndex) = emitLoadVariable(instList, lastSymtab(symstack), symtab, (yyvsp[(1) - (1)].symIndex));
;}
    break;

  case 60:

/* Line 1455 of yacc.c  */
#line 328 "CminusParser.y"
    { 
	(yyval.symIndex) = (yyvsp[(1) - (1)].symIndex);
;}
    break;

  case 61:

/* Line 1455 of yacc.c  */
#line 330 "CminusParser.y"
    {
	(yyval.symIndex) = emitCallFunction(instList,symtab,(yyvsp[(1) - (3)].name));
;}
    break;

  case 62:

/* Line 1455 of yacc.c  */
#line 332 "CminusParser.y"
    {
	(yyval.symIndex) = (yyvsp[(2) - (3)].symIndex);
;}
    break;

  case 63:

/* Line 1455 of yacc.c  */
#line 336 "CminusParser.y"
    {
	(yyval.symIndex) = emitComputeVarAddress(instList,lastSymtab(symstack), symtab, (yyvsp[(1) - (1)].name));
;}
    break;

  case 64:

/* Line 1455 of yacc.c  */
#line 338 "CminusParser.y"
    {
	(yyval.symIndex) = emitComputeArrayAddress(instList,lastSymtab(symstack),symtab,(yyvsp[(1) - (4)].name),(yyvsp[(3) - (4)].symIndex));
;}
    break;

  case 65:

/* Line 1455 of yacc.c  */
#line 342 "CminusParser.y"
    {
	int symIndex = SymIndex(symtab,(yyvsp[(1) - (1)].name));
	(yyval.symIndex) = emitLoadStringConstantAddress(instList,dataList,symtab,symIndex);
;}
    break;

  case 66:

/* Line 1455 of yacc.c  */
#line 347 "CminusParser.y"
    { 
	int symIndex = SymIndex(symtab,(yyvsp[(1) - (1)].name));
	(yyval.symIndex) = emitLoadIntegerConstant(instList,symtab,symIndex);
;}
    break;



/* Line 1455 of yacc.c  */
#line 2157 "CminusParser.c"
      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (yymsg);
	  }
	else
	  {
	    yyerror (YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
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
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
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


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


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

#if !defined(yyoverflow) || YYERROR_VERBOSE
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
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp);
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
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}



/* Line 1675 of yacc.c  */
#line 352 "CminusParser.y"



/********************C ROUTINES *********************************/

void Cminus_error(char *s) {
  fprintf(stderr,"%s: line %d: %s\n",fileName,Cminus_lineno,s);
}

int Cminus_wrap() {
	return 1;
}

static void initSymStack() {
	symstack = symtabStackInit();
}

static void initSymTable() {
	symtab = beginScope(symstack);
}

static void deleteSymTable() {
	while (stackSize(symstack) > 0) {
		symtab = endScope(symstack);
	    SymKillField(symtab,SYMTAB_REGISTER_INDEX_FIELD);
	    SymKillField(symtab,SYMTAB_OFFSET_FIELD);
	    SymKill(symtab);
	}
}

static void initialize(char* inputFileName) {
	stdin = freopen(inputFileName,"r", stdin);
    if (stdin == NULL) {
    	fprintf(stderr,"Error: Could not open file %s\n",inputFileName);
    	exit(-1);
    }

	char* dotChar = rindex(inputFileName,'.');
	int endIndex = strlen(inputFileName) - strlen(dotChar);
	char *outputFileName = nssave(2,substr(inputFileName,0,endIndex),".s");
	stdout = freopen(outputFileName,"w", stdout);
    if (stdout == NULL) {
    	fprintf(stderr,"Error: Could not open file %s\n",outputFileName);
    	exit(-1);
	} 

    initSymStack();
	initSymTable();
	initRegisters();

	instList = dlinkListAlloc(NULL);
	dataList = dlinkListAlloc(NULL);
}

static void finalize() {
    fclose(stdin);

    deleteSymTable();
    cleanupRegisters();
    
    dlinkFreeNodesAndAtoms(instList);
    dlinkFreeNodesAndAtoms(dataList);
}

int main(int argc, char** argv) {	
	fileName = argv[1];
	initialize(fileName);
    Cminus_parse();
  	finalize();
  
  	return 0;
}
/******************END OF C ROUTINES**********************/

