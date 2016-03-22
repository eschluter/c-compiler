/* original parser id follows */
/* yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93" */
/* (use YYMAJOR/YYMINOR for ifdefs dependent on parser version) */

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20141128

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)
#define YYENOMEM       (-2)
#define YYEOF          0
#define YYPREFIX "yy"

#define YYPURE 0

#line 5 "src/cstr-parser.y"
#include "compilerAPI.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct ops {
	COMPT compar;
	char * idptr;
	TYPE typ;
	MEMTYPE mtyp;
	int ival;
	char * sval;
} EXPT;

typedef struct decl_t {
	char * idptr;
	KIND idtype;
	TYPE dectype;
} decl_t;
#line 25 "src/cstr-parser.y"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union {
	decl_t dclt;
	char * idptr;
	char * strval;
	TYPE tval;
	int itype;
	EXPT exp;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 56 "y.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define INTT 257
#define STRINGT 258
#define CONST_INT 259
#define CONST_STRING 260
#define IDENT 261
#define EXTERNT 262
#define IF 263
#define ELSE 264
#define WHILE 265
#define DO 266
#define RETURN 267
#define FOR 268
#define THEN 269
#define ASSIGNMENT 270
#define INF 271
#define EGAL 272
#define SUP 273
#define INFEQUAL 274
#define SUPEQUAL 275
#define DIFF 276
#define PLUS 277
#define MINUS 278
#define MULTI 279
#define DIV 280
#define SHIFTRIGHT 281
#define SHIFTLEFT 282
#define MODULO 283
#define YYERRCODE 256
typedef short YYINT;
static const YYINT yylhs[] = {                           -1,
    0,    0,    6,    6,    6,    4,    8,    3,    1,    1,
    5,    5,   10,   10,   10,   10,    2,    2,    7,    7,
   11,   11,   12,   13,   13,   13,   13,   13,   13,   14,
   14,   19,   19,   19,    9,    9,    9,    9,   20,   22,
   21,   21,   16,   16,   23,   15,   15,   15,   17,   24,
   25,   25,   25,   25,   25,   25,   18,   18,   18,   26,
   26,   26,   27,   27,   27,   27,   28,   28,   29,   29,
   29,   30,   30,   30,   32,   32,   31,   31,   31,   31,
};
static const YYINT yylen[] = {                            2,
    1,    2,    1,    2,    1,    4,    0,    3,    1,    1,
    1,    3,    1,    2,    7,   10,    1,    1,    3,    4,
    1,    3,    2,    1,    1,    1,    1,    1,    1,    2,
    2,    3,    6,    9,    4,    3,    3,    2,    1,    1,
    1,    2,    2,    4,    4,    5,    6,    9,    3,    3,
    1,    1,    1,    1,    1,    1,    1,    3,    3,    1,
    3,    3,    1,    3,    3,    3,    1,    2,    1,    4,
    7,    1,    4,    3,    1,    3,    1,    1,    1,    3,
};
static const YYINT yydefred[] = {                         0,
    9,   10,    0,    0,    0,    3,    5,    1,    0,    4,
    2,    0,   11,    0,    0,   18,    0,    8,    0,    0,
   19,    0,    0,   21,   12,   39,    6,    0,   23,    0,
   20,   78,   79,    0,    0,    0,    0,    0,    0,    0,
   24,    0,   40,   13,   25,    0,   41,   26,   27,   28,
   29,    0,    0,    0,   38,    0,    0,    0,   63,   67,
   69,   72,   22,    0,    0,    0,    0,    0,    0,    0,
    0,    0,   68,    0,    0,   14,    0,   36,    0,    0,
   30,   31,   42,   37,    0,    0,    0,    0,    0,    0,
    0,    0,   74,    0,    0,    0,    0,    0,    0,    0,
   49,    0,    0,   80,    0,   35,    0,    0,    0,    0,
    0,   64,   65,   66,    0,    0,   73,   53,   51,   54,
   55,   56,   52,    0,   45,    0,    0,    0,    0,    0,
    0,   44,    0,    0,    0,    0,   46,    0,    0,    0,
    0,    0,    0,    0,   47,    0,    0,    0,    0,    0,
    0,    0,    0,   15,    0,    0,   71,    0,    0,    0,
    0,    0,   48,    0,   16,
};
static const YYINT yydgoto[] = {                          4,
    9,   13,    6,    7,   14,    8,   16,   20,   45,   46,
   23,   24,   47,   48,   49,   50,   51,   52,   53,   28,
   54,   55,   56,   97,  124,   57,   58,   59,   60,   61,
   62,   95,
};
static const YYINT yysindex[] = {                      -159,
    0,    0, -171, -159, -233,    0,    0,    0, -233,    0,
    0,   19,    0,  -24,    0,    0,  -40,    0, -233,  -90,
    0, -224,   13,    0,    0,    0,    0,   73,    0, -171,
    0,    0,    0,    6,   29,   40,  154,  111,   53,  111,
    0,  111,    0,    0,    0,   87,    0,    0,    0,    0,
    0,  -54,    3,  101,    0,  154, -177, -172,    0,    0,
    0,    0,    0,  111,  111,   97,  111,  111, -190,  -18,
   18, -166,    0,  -17, -156,    0,  101,    0,  111,  111,
    0,    0,    0,    0, -154,  111,  111,  111,  111,  111,
 -158,  -91,    0, -158,   23, -107,   71,   77,   74,  111,
    0,  -85,   72,    0,   42,    0, -177, -177,  154, -172,
 -172,    0,    0,    0,  -84,  111,    0,    0,    0,    0,
    0,    0,    0,  111,    0,  154,  111,  -89,  111,  111,
 -125,    0,  111,  111, -158, -158,    0,   94,   45,  -82,
   80,   49, -158,  -79,    0,  111,  -83, -166,  -36, -127,
  -76,  111,  104,    0, -115,  111,    0,  -74,  154,   54,
 -158, -127,    0,   89,    0,
};
static const YYINT yyrindex[] = {                         0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  -23,    0,    0,  -34,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  103,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   22,  -15,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,  -41,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  265,    0,    0,    0,    0,    0,
  -14,    0,    0,   75,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   35,   47,    0,   -3,
    9,    0,    0,    0,  114,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   76,  -11,    0,    0,  -28,    0,
    0,    0,    1,    0,    0,    0,    0,    0,    0,  121,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    2,    0,    0,    0,    0,
};
static const YYINT yygindex[] = {                         0,
   92,  130,   12,    0,    0,  146,  147,    0,  133,    0,
    0,  125,   -5,    0,    0,    0,    0,  388,  -63,    0,
  110,   -7,    0,  -56,    0,   46,   43,   -6,    0,    0,
    0,    0,
};
#define YYTABLESIZE 544
static const YYINT yytable[] = {                         77,
   21,  115,   77,  139,   81,  129,  134,  152,  103,   18,
  147,   98,   70,  150,   10,   70,  157,   77,  162,   19,
   17,   66,  154,  104,   18,   60,   32,   12,   60,   50,
   70,   69,   26,   73,   18,   17,   29,   61,   78,   44,
   61,   33,   34,   60,   32,   66,   84,   50,   83,   62,
   85,   77,   62,   31,  155,   61,   30,   76,   17,   33,
   34,   82,   57,  117,   70,   57,  116,   62,   67,  106,
  138,   83,  100,  141,   99,   59,  101,   60,   59,   68,
   57,  112,  113,  114,  153,    1,    2,   58,    7,   61,
   58,    5,   72,   59,  102,    5,   65,    1,    2,   86,
   87,   62,    3,  132,  105,   58,   88,   89,   22,  109,
   90,  125,   42,  127,   57,   75,   76,  126,   75,   76,
  137,   22,   79,   80,  107,  108,   42,   59,  110,  111,
  130,   41,  131,  142,  145,  146,   42,   93,  148,   58,
   42,  149,  156,  160,  159,   41,  164,  165,   25,   11,
   42,   15,   27,  163,   63,   77,    0,    0,    0,   41,
    0,   77,    0,  118,  119,  120,  121,  122,  123,    0,
    0,    0,   70,   79,   80,    0,    0,    0,    0,   71,
    0,    0,    0,    0,   64,  133,  133,    0,    0,   79,
   80,   79,   80,   42,    0,   26,    0,   43,   79,   80,
    0,   79,   80,    0,   79,   80,   79,   80,    0,   26,
    0,   43,   41,    0,    0,    0,    1,    2,    0,    0,
    0,    0,    0,   26,    0,   43,   79,   80,    0,   77,
   77,   77,   77,   77,   77,   77,   77,   77,   77,   77,
   77,   77,   70,   70,   70,   70,   70,   70,   70,   70,
   70,   70,   70,   70,   70,   60,   60,   60,   60,   60,
   60,   60,   60,   79,   80,   60,   60,   61,   61,   61,
   61,   61,   61,   61,   61,   64,   26,   61,   61,   62,
   62,   62,   62,   62,   62,   62,   62,    0,    0,   62,
   62,    0,   57,   57,   57,   57,   57,   57,   79,   80,
    0,    0,   57,   57,   43,   59,   59,   59,   59,   59,
   59,    0,    0,    0,    0,   59,   59,   58,   58,   58,
   58,   58,   58,   43,    0,    0,    0,   58,   58,    1,
    2,   32,   33,   34,    0,   35,    0,   36,   37,   38,
   39,    0,    0,   75,    2,   32,   33,   34,    0,   35,
   40,   36,   37,   38,   39,   32,   33,   70,    0,   32,
   33,   34,    0,   35,   40,   36,   37,   38,   39,   32,
   33,   70,    0,    0,   40,    0,    0,    0,   40,   77,
   77,   77,   77,   77,   77,   77,    0,   43,   40,   43,
   70,   70,   70,   70,   70,   70,   70,   71,   71,   71,
   71,   71,   71,   71,    0,    0,    0,    0,    0,    0,
    0,    0,   32,   33,   34,    0,   35,    0,   36,   37,
   38,   39,    0,    0,    0,   71,    0,    0,    0,   74,
    0,   40,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   91,   92,   94,   96,   96,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  128,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  135,    0,    0,    0,    0,    0,    0,
    0,  136,    0,    0,   96,    0,  140,   96,    0,    0,
  143,  144,    0,   43,   43,   43,    0,   43,    0,   43,
   43,   43,   43,  151,    0,    0,    0,    0,    0,  158,
    0,    0,   43,  161,
};
static const YYINT yycheck[] = {                         41,
   41,   93,   44,   93,   59,   91,   91,   91,   72,   44,
   93,   68,   41,   93,    3,   44,   93,   59,   93,   44,
   44,   40,   59,   41,   59,   41,   41,  261,   44,   41,
   59,   37,  123,   40,   59,   59,  261,   41,   46,   28,
   44,   41,   41,   59,   59,   40,   54,   59,   54,   41,
   56,   93,   44,   41,   91,   59,   44,   46,   40,   59,
   59,   59,   41,   41,   93,   44,   44,   59,   40,   77,
  127,   77,   91,  130,  265,   41,   59,   93,   44,   40,
   59,   88,   89,   90,  148,  257,  258,   41,  123,   93,
   44,    0,   40,   59,  261,    4,   91,  257,  258,  277,
  278,   93,  262,  109,  261,   59,  279,  280,   17,  264,
  283,   41,   40,   40,   93,   41,   41,   41,   44,   44,
  126,   30,  281,  282,   79,   80,   40,   93,   86,   87,
   59,   59,   91,  259,   41,   91,   40,   41,   59,   93,
   40,   93,  270,  259,   41,   59,   93,   59,   19,    4,
   40,    5,   20,  159,   30,   46,   -1,   -1,   -1,   59,
   -1,   59,   -1,  271,  272,  273,  274,  275,  276,   -1,
   -1,   -1,   59,  281,  282,   -1,   -1,   -1,   -1,   59,
   -1,   -1,   -1,   -1,  270,  270,  270,   -1,   -1,  281,
  282,  281,  282,   40,   -1,  123,   -1,  125,  281,  282,
   -1,  281,  282,   -1,  281,  282,  281,  282,   -1,  123,
   -1,  125,   59,   -1,   -1,   -1,  257,  258,   -1,   -1,
   -1,   -1,   -1,  123,   -1,  125,  281,  282,   -1,  271,
  272,  273,  274,  275,  276,  277,  278,  279,  280,  281,
  282,  283,  271,  272,  273,  274,  275,  276,  277,  278,
  279,  280,  281,  282,  283,  271,  272,  273,  274,  275,
  276,  277,  278,  281,  282,  281,  282,  271,  272,  273,
  274,  275,  276,  277,  278,  270,  123,  281,  282,  271,
  272,  273,  274,  275,  276,  277,  278,   -1,   -1,  281,
  282,   -1,  271,  272,  273,  274,  275,  276,  281,  282,
   -1,   -1,  281,  282,   40,  271,  272,  273,  274,  275,
  276,   -1,   -1,   -1,   -1,  281,  282,  271,  272,  273,
  274,  275,  276,   59,   -1,   -1,   -1,  281,  282,  257,
  258,  259,  260,  261,   -1,  263,   -1,  265,  266,  267,
  268,   -1,   -1,  257,  258,  259,  260,  261,   -1,  263,
  278,  265,  266,  267,  268,  259,  260,  261,   -1,  259,
  260,  261,   -1,  263,  278,  265,  266,  267,  268,  259,
  260,  261,   -1,   -1,  278,   -1,   -1,   -1,  278,  277,
  278,  279,  280,  281,  282,  283,   -1,  123,  278,  125,
  277,  278,  279,  280,  281,  282,  283,  277,  278,  279,
  280,  281,  282,  283,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,  259,  260,  261,   -1,  263,   -1,  265,  266,
  267,  268,   -1,   -1,   -1,   38,   -1,   -1,   -1,   42,
   -1,  278,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   64,   65,   66,   67,   68,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  100,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  116,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,  124,   -1,   -1,  127,   -1,  129,  130,   -1,   -1,
  133,  134,   -1,  259,  260,  261,   -1,  263,   -1,  265,
  266,  267,  268,  146,   -1,   -1,   -1,   -1,   -1,  152,
   -1,   -1,  278,  156,
};
#define YYFINAL 4
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 283
#define YYUNDFTOKEN 318
#define YYTRANSLATE(a) ((a) > YYMAXTOKEN ? YYUNDFTOKEN : (a))
#if YYDEBUG
static const char *const yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"'('","')'",0,0,"','",0,0,0,0,0,0,0,0,0,0,0,0,0,0,"';'",0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'['",0,"']'",0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'{'",0,"'}'",0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"INTT","STRINGT","CONST_INT","CONST_STRING","IDENT","EXTERNT","IF","ELSE",
"WHILE","DO","RETURN","FOR","THEN","ASSIGNMENT","INF","EGAL","SUP","INFEQUAL",
"SUPEQUAL","DIFF","PLUS","MINUS","MULTI","DIV","SHIFTRIGHT","SHIFTLEFT",
"MODULO",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
"illegal-symbol",
};
static const char *const yyrule[] = {
"$accept : program",
"program : external_declaration",
"program : program external_declaration",
"external_declaration : declaration",
"external_declaration : EXTERNT declaration",
"external_declaration : function_definition",
"function_definition : type function_declarator decl_glb_fct compound_instruction",
"decl_glb_fct :",
"declaration : type declarator_list ';'",
"type : INTT",
"type : STRINGT",
"declarator_list : declarator",
"declarator_list : declarator_list ',' declarator",
"declaration_list : declaration",
"declaration_list : declaration_list declaration",
"declaration_list : declaration_list INTT IDENT '[' CONST_INT ']' ';'",
"declaration_list : declaration_list INTT IDENT '[' CONST_INT ']' '[' CONST_INT ']' ';'",
"declarator : IDENT",
"declarator : function_declarator",
"function_declarator : IDENT '(' ')'",
"function_declarator : IDENT '(' parameter_list ')'",
"parameter_list : parameter_declaration",
"parameter_list : parameter_list ',' parameter_declaration",
"parameter_declaration : type IDENT",
"instruction : ';'",
"instruction : compound_instruction",
"instruction : expression_instruction",
"instruction : iteration_instruction",
"instruction : select_instruction",
"instruction : jump_instruction",
"expression_instruction : expression ';'",
"expression_instruction : assignment ';'",
"assignment : IDENT ASSIGNMENT expression",
"assignment : IDENT '[' expression ']' ASSIGNMENT expression",
"assignment : IDENT '[' expression ']' '[' expression ']' ASSIGNMENT expression",
"compound_instruction : block_start declaration_list instruction_list block_end",
"compound_instruction : block_start declaration_list block_end",
"compound_instruction : block_start instruction_list block_end",
"compound_instruction : block_start block_end",
"block_start : '{'",
"block_end : '}'",
"instruction_list : instruction",
"instruction_list : instruction_list instruction",
"select_instruction : cond_instruction instruction",
"select_instruction : cond_instruction instruction ELSE instruction",
"cond_instruction : IF '(' condition ')'",
"iteration_instruction : WHILE '(' condition ')' instruction",
"iteration_instruction : DO instruction WHILE '(' condition ')'",
"iteration_instruction : FOR '(' assignment ';' condition ';' assignment ')' instruction",
"jump_instruction : RETURN expression ';'",
"condition : expression comparison_operator expression",
"comparison_operator : EGAL",
"comparison_operator : DIFF",
"comparison_operator : INF",
"comparison_operator : SUP",
"comparison_operator : INFEQUAL",
"comparison_operator : SUPEQUAL",
"expression : expression_additive",
"expression : expression SHIFTLEFT expression_additive",
"expression : expression SHIFTRIGHT expression_additive",
"expression_additive : expression_multiplicative",
"expression_additive : expression_additive PLUS expression_multiplicative",
"expression_additive : expression_additive MINUS expression_multiplicative",
"expression_multiplicative : unary_expression",
"expression_multiplicative : expression_multiplicative MULTI unary_expression",
"expression_multiplicative : expression_multiplicative DIV unary_expression",
"expression_multiplicative : expression_multiplicative MODULO unary_expression",
"unary_expression : array_expression",
"unary_expression : MINUS unary_expression",
"array_expression : expression_postfixee",
"array_expression : IDENT '[' expression ']'",
"array_expression : IDENT '[' expression ']' '[' expression ']'",
"expression_postfixee : primary_expression",
"expression_postfixee : IDENT '(' argument_expression_list ')'",
"expression_postfixee : IDENT '(' ')'",
"argument_expression_list : expression",
"argument_expression_list : argument_expression_list ',' expression",
"primary_expression : IDENT",
"primary_expression : CONST_INT",
"primary_expression : CONST_STRING",
"primary_expression : '(' expression ')'",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 10000
#define YYMAXDEPTH  10000
#endif
#endif

#define YYINITSTACKSIZE 200

typedef struct {
    unsigned stacksize;
    YYINT    *s_base;
    YYINT    *s_mark;
    YYINT    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 481 "src/cstr-parser.y"

#include "lex.yy.c"

int yyerror(s) char *s; {
	fprintf(stderr, "line %d - %s\n", get_line_number(), s);
	exit(1);
}

int main() {
	int ret;
	initialize_symboltable();
	ret=yyparse();
	destroy_symboltable();
	return ret;
}

// main function definition for a two pass compiler (TODO)
//-------------------------------------------------
/*int main(int argc, char ** argv) { 
	int ret;
	FILE * ifp;
	initialize_symboltable ();
	// open source code file and associate with stdin
	ifp = freopen(argv[1], "r", stdin);
	// first pass
	ret=yyparse();
	// close file and reopen
	ifp = freopen(argv[1], "r", stdin);
	//second pass
	printf ("\nSECOND PASS\n\n");
	ret = yyparse();
	// close file
	fclose (ifp);
	destroy_symboltable ();
	return ret;
}*/
#line 501 "y.tab.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    YYINT *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return YYENOMEM;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = (int) (data->s_mark - data->s_base);
    newss = (YYINT *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return YYENOMEM;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return YYENOMEM;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack) == YYENOMEM) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    YYERROR_CALL("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == YYEOF) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = yyname[YYTRANSLATE(yychar)];
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 3:
#line 83 "src/cstr-parser.y"
	{ process_declaration (yystack.l_mark[0].dclt.dectype); }
break;
case 4:
#line 85 "src/cstr-parser.y"
	{ process_extern(yystack.l_mark[0].dclt.dectype); }
break;
case 5:
#line 87 "src/cstr-parser.y"
	{ process_declaration (yystack.l_mark[0].dclt.dectype); }
break;
case 6:
#line 92 "src/cstr-parser.y"
	{ 	type_check_return(yystack.l_mark[-2].idptr, yystack.l_mark[-3].tval);
		push_back_dec(yystack.l_mark[-2].idptr, FUNC); 
		yyval.dclt.dectype = yystack.l_mark[-3].tval; }
break;
case 7:
#line 98 "src/cstr-parser.y"
	{ generate_function_header (); }
break;
case 8:
#line 103 "src/cstr-parser.y"
	{ yyval.dclt.dectype = yystack.l_mark[-2].tval; }
break;
case 9:
#line 107 "src/cstr-parser.y"
	{yyval.tval=INT;}
break;
case 10:
#line 108 "src/cstr-parser.y"
	{yyval.tval=STRING;}
break;
case 11:
#line 113 "src/cstr-parser.y"
	{ push_back_dec (yystack.l_mark[0].dclt.idptr, yystack.l_mark[0].dclt.idtype); }
break;
case 12:
#line 115 "src/cstr-parser.y"
	{ push_back_dec (yystack.l_mark[0].dclt.idptr, yystack.l_mark[0].dclt.idtype); }
break;
case 13:
#line 120 "src/cstr-parser.y"
	{ process_declaration (yystack.l_mark[0].dclt.dectype); }
break;
case 14:
#line 122 "src/cstr-parser.y"
	{ process_declaration (yystack.l_mark[0].dclt.dectype); }
break;
case 15:
#line 124 "src/cstr-parser.y"
	{ process_matrix_declaration (yystack.l_mark[-4].idptr, yystack.l_mark[-2].itype, 0); }
break;
case 16:
#line 126 "src/cstr-parser.y"
	{ process_matrix_declaration (yystack.l_mark[-7].idptr, yystack.l_mark[-5].itype, yystack.l_mark[-2].itype); }
break;
case 17:
#line 131 "src/cstr-parser.y"
	{ yyval.dclt.idptr = yystack.l_mark[0].idptr; yyval.dclt.idtype = VAR; }
break;
case 18:
#line 133 "src/cstr-parser.y"
	{ yyval.dclt.idptr = yystack.l_mark[0].idptr; yyval.dclt.idtype = FUNC; }
break;
case 19:
#line 138 "src/cstr-parser.y"
	{ yyval.idptr=yystack.l_mark[-2].idptr; set_function_id (yystack.l_mark[-2].idptr); }
break;
case 20:
#line 140 "src/cstr-parser.y"
	{ yyval.idptr=yystack.l_mark[-3].idptr; set_function_id (yystack.l_mark[-3].idptr); }
break;
case 23:
#line 150 "src/cstr-parser.y"
	{ process_p_declaration (yystack.l_mark[-1].tval, yystack.l_mark[0].idptr); }
break;
case 25:
#line 155 "src/cstr-parser.y"
	{ generate_else(); }
break;
case 26:
#line 156 "src/cstr-parser.y"
	{ generate_else(); }
break;
case 27:
#line 157 "src/cstr-parser.y"
	{ }
break;
case 28:
#line 158 "src/cstr-parser.y"
	{ }
break;
case 29:
#line 159 "src/cstr-parser.y"
	{ generate_else(); }
break;
case 32:
#line 169 "src/cstr-parser.y"
	{
	/* TC*/
		type_check_assignment ( get_id_type(yystack.l_mark[-2].idptr), yystack.l_mark[0].exp.typ );
		yyval.idptr = yystack.l_mark[-2].idptr; /*free($1);*/
	/* CG*/
		generate_assignment (yystack.l_mark[-2].idptr, yystack.l_mark[0].exp.idptr, yystack.l_mark[0].exp.ival, yystack.l_mark[0].exp.typ, yystack.l_mark[0].exp.mtyp);
	}
break;
case 33:
#line 177 "src/cstr-parser.y"
	{
	/* TC*/
		type_check_array_index (yystack.l_mark[-3].exp.typ);
		type_check_assignment ( yystack.l_mark[-5].exp.typ, yystack.l_mark[0].exp.typ );
	/* CG*/
		index_array (yystack.l_mark[-5].idptr, yystack.l_mark[-3].exp.idptr, yystack.l_mark[-3].exp.ival, yystack.l_mark[-3].exp.mtyp, 1);
		generate_assignment (yystack.l_mark[-5].idptr, yystack.l_mark[0].exp.idptr, yystack.l_mark[0].exp.ival, yystack.l_mark[0].exp.typ, yystack.l_mark[0].exp.mtyp);
	}
break;
case 34:
#line 186 "src/cstr-parser.y"
	{
	/* TC*/
		type_check_matrix_index (yystack.l_mark[-6].exp.typ, yystack.l_mark[-3].exp.typ);
		type_check_assignment ( yystack.l_mark[-8].exp.typ, yystack.l_mark[0].exp.typ);
	/* CG*/
		index_matrix (yystack.l_mark[-8].idptr, yystack.l_mark[-6].exp.idptr, yystack.l_mark[-6].exp.ival, yystack.l_mark[-6].exp.mtyp, yystack.l_mark[-3].exp.idptr, yystack.l_mark[-3].exp.ival, yystack.l_mark[-3].exp.mtyp, 1);
		generate_assignment (yystack.l_mark[-8].idptr, yystack.l_mark[0].exp.idptr, yystack.l_mark[0].exp.ival, yystack.l_mark[0].exp.typ, yystack.l_mark[0].exp.mtyp);
	}
break;
case 39:
#line 206 "src/cstr-parser.y"
	{ 
	/* CG*/
		generate_loop_beg_block ();
	/**/
		enter_scope ();
	}
break;
case 40:
#line 216 "src/cstr-parser.y"
	{ exit_scope (); }
break;
case 43:
#line 226 "src/cstr-parser.y"
	{
	/*CG*/
		generate_ifend ();
	}
break;
case 44:
#line 231 "src/cstr-parser.y"
	{ 
	/* CG*/
		generate_ifend ();
	}
break;
case 45:
#line 239 "src/cstr-parser.y"
	{
	/* CG*/
		generate_if (yystack.l_mark[-1].exp.compar);
	}
break;
case 46:
#line 247 "src/cstr-parser.y"
	{
	/* CG*/
		terminate_while ();
	}
break;
case 47:
#line 252 "src/cstr-parser.y"
	{ 
	/* CG*/
		terminate_do_while (yystack.l_mark[-1].exp.compar);
	}
break;
case 48:
#line 257 "src/cstr-parser.y"
	{ 
	/* CG*/
		terminate_for ();
	}
break;
case 49:
#line 265 "src/cstr-parser.y"
	{
	/* TC*/
		push_back_returntype (yystack.l_mark[-1].exp.typ);
	/* CG*/
		generate_freturn (yystack.l_mark[-1].exp.idptr, yystack.l_mark[-1].exp.ival, yystack.l_mark[-1].exp.typ, yystack.l_mark[-1].exp.mtyp);
	}
break;
case 50:
#line 275 "src/cstr-parser.y"
	{
		OP opoverride = COMPARISON;
		yyval.exp = yystack.l_mark[-1].exp;
	/* TC*/
		if ( yystack.l_mark[-2].exp.typ == STRING && (yystack.l_mark[-1].exp.compar == EQUAL || yystack.l_mark[-1].exp.compar == NEQUAL) ) {
			type_check_equality (yystack.l_mark[-2].exp.typ, yystack.l_mark[0].exp.typ);
			if (yystack.l_mark[-1].exp.compar == EQUAL) {
				yyval.exp.compar = STREQUAL;
			} else {
				yyval.exp.compar = STRNEQUAL;
			}
			opoverride = STRCMP;
		} else {
			type_check_comparison (yystack.l_mark[-2].exp.typ, yystack.l_mark[0].exp.typ);
		}
	/* CG*/
		generate_loop_begin (yyval.exp.compar);	/* by default label each comparison - handle IF individually*/
		generate_operation (opoverride);
	}
break;
case 51:
#line 297 "src/cstr-parser.y"
	{yyval.exp.compar = EQUAL;}
break;
case 52:
#line 298 "src/cstr-parser.y"
	{yyval.exp.compar = NEQUAL;}
break;
case 53:
#line 299 "src/cstr-parser.y"
	{yyval.exp.compar = INFERIOR;}
break;
case 54:
#line 300 "src/cstr-parser.y"
	{yyval.exp.compar = SUPERIOR;}
break;
case 55:
#line 301 "src/cstr-parser.y"
	{yyval.exp.compar = INFERIOREQ;}
break;
case 56:
#line 302 "src/cstr-parser.y"
	{yyval.exp.compar = SUPERIOREQ;}
break;
case 57:
#line 307 "src/cstr-parser.y"
	{ yyval.exp = yystack.l_mark[0].exp; }
break;
case 58:
#line 309 "src/cstr-parser.y"
	{ 	
	/* TC*/
		yyval.exp.typ	= type_check_bitwise (yystack.l_mark[-2].exp.typ, yystack.l_mark[0].exp.typ); 
		yyval.exp.mtyp	= RESULT;
	/* CG*/
		generate_operation (LSHIFT);
	}
break;
case 59:
#line 317 "src/cstr-parser.y"
	{ 
	/* TC*/
		yyval.exp.typ	= type_check_bitwise (yystack.l_mark[-2].exp.typ, yystack.l_mark[0].exp.typ); 
		yyval.exp.mtyp	= RESULT;
	/* CG*/
		generate_operation (RSHIFT);
	}
break;
case 60:
#line 328 "src/cstr-parser.y"
	{ yyval.exp = yystack.l_mark[0].exp; }
break;
case 61:
#line 330 "src/cstr-parser.y"
	{ 	
	/* TC*/
		yyval.exp.typ	= type_check_addition (yystack.l_mark[-2].exp.typ, yystack.l_mark[0].exp.typ); 
		yyval.exp.mtyp	= RESULT;
	/* CG*/
		switch (yyval.exp.typ) {
			case INT:
				generate_operation (ADDITION);
				break;
			case STRING:
				generate_operation (STRCAT);
				break;
		}
	}
break;
case 62:
#line 345 "src/cstr-parser.y"
	{ 
	/* TC*/
		yyval.exp.typ	= type_check_numerical (yystack.l_mark[-2].exp.typ, yystack.l_mark[0].exp.typ); 
		yyval.exp.mtyp	= RESULT;
	/* CG*/
		generate_operation (SUBTRACTION);
	}
break;
case 63:
#line 356 "src/cstr-parser.y"
	{ yyval.exp = yystack.l_mark[0].exp; }
break;
case 64:
#line 358 "src/cstr-parser.y"
	{ 	
	/* TC*/
		yyval.exp.typ	= type_check_numerical (yystack.l_mark[-2].exp.typ, yystack.l_mark[0].exp.typ); 
		yyval.exp.mtyp	= RESULT;
	/* CG*/
		generate_operation (MULTIPLY);
	}
break;
case 65:
#line 366 "src/cstr-parser.y"
	{ 	
	/* TC*/
		yyval.exp.typ	= type_check_numerical (yystack.l_mark[-2].exp.typ, yystack.l_mark[0].exp.typ); 
		yyval.exp.mtyp	= RESULT;
	/* CG*/
		generate_operation (DIVIDE);
	}
break;
case 66:
#line 374 "src/cstr-parser.y"
	{ 
	/* TC*/
		yyval.exp.typ 	= type_check_modulo (yystack.l_mark[-2].exp.typ, yystack.l_mark[0].exp.typ);
		yyval.exp.mtyp	= RESULT;
	/* CG*/
		generate_operation (MOD);
	}
break;
case 67:
#line 385 "src/cstr-parser.y"
	{ yyval.exp = yystack.l_mark[0].exp; }
break;
case 68:
#line 387 "src/cstr-parser.y"
	{ 
		yystack.l_mark[0].exp.mtyp	= RESULT;
		yyval.exp 	= yystack.l_mark[0].exp;
	/* CG*/
		generate_operation (UNARY_MINUS);
	}
break;
case 69:
#line 397 "src/cstr-parser.y"
	{ yyval.exp = yystack.l_mark[0].exp; }
break;
case 70:
#line 399 "src/cstr-parser.y"
	{ 
	/* TC*/
		yyval.exp.typ = type_check_array_index (yystack.l_mark[-1].exp.typ);
		yyval.exp.idptr = yystack.l_mark[-3].idptr;
		yyval.exp.mtyp = RESULT;
	/* CG*/
		index_array (yystack.l_mark[-3].idptr, yystack.l_mark[-1].exp.idptr, yystack.l_mark[-1].exp.ival, yystack.l_mark[-1].exp.mtyp, 0);
	}
break;
case 71:
#line 408 "src/cstr-parser.y"
	{
	/* TC*/
		yyval.exp.typ = type_check_matrix_index (yystack.l_mark[-4].exp.typ, yystack.l_mark[-1].exp.typ);
		yyval.exp.idptr = yystack.l_mark[-6].idptr;
		yyval.exp.mtyp = RESULT;
	/* CG*/
		index_matrix (yystack.l_mark[-6].idptr, yystack.l_mark[-4].exp.idptr,yystack.l_mark[-4].exp.ival,yystack.l_mark[-4].exp.mtyp, yystack.l_mark[-1].exp.idptr,yystack.l_mark[-1].exp.ival,yystack.l_mark[-1].exp.mtyp,0);
	}
break;
case 72:
#line 420 "src/cstr-parser.y"
	{ yyval.exp = yystack.l_mark[0].exp; }
break;
case 73:
#line 422 "src/cstr-parser.y"
	{ 	
		yyval.exp.typ 	= get_id_type (yystack.l_mark[-3].idptr);
		type_check_fparams (yystack.l_mark[-3].idptr);
		call_function (yystack.l_mark[-3].idptr);
		yyval.exp.idptr 	= yystack.l_mark[-3].idptr; 
		/*free($1);*/
		yyval.exp.mtyp 	= RESULT;
	}
break;
case 74:
#line 431 "src/cstr-parser.y"
	{ 	
		yyval.exp.typ 	= get_id_type (yystack.l_mark[-2].idptr);
		call_function (yystack.l_mark[-2].idptr);
		yyval.exp.idptr 	= yystack.l_mark[-2].idptr;
		/*free($1);*/
		yyval.exp.mtyp 	= RESULT;
	}
break;
case 75:
#line 442 "src/cstr-parser.y"
	{ push_fparam (yystack.l_mark[0].exp.idptr, yystack.l_mark[0].exp.typ, yystack.l_mark[0].exp.mtyp, yystack.l_mark[0].exp.ival); }
break;
case 76:
#line 444 "src/cstr-parser.y"
	{ push_fparam (yystack.l_mark[0].exp.idptr, yystack.l_mark[0].exp.typ, yystack.l_mark[0].exp.mtyp, yystack.l_mark[0].exp.ival); }
break;
case 77:
#line 449 "src/cstr-parser.y"
	{ 
		yyval.exp.typ 	= get_id_type (yystack.l_mark[0].idptr);
		yyval.exp.idptr 	= yystack.l_mark[0].idptr; /*free($1);*/ 
		yyval.exp.ival 	= 0; /*empty value*/
		yyval.exp.mtyp 	= REFERENCE;
	/* CG*/
		push_operand (yystack.l_mark[0].idptr, 0, REFERENCE);
	}
break;
case 78:
#line 458 "src/cstr-parser.y"
	{ 
		yyval.exp.typ 	= INT;
		yyval.exp.ival 	= yystack.l_mark[0].itype;
		yyval.exp.idptr 	= NULL; 
		yyval.exp.mtyp 	= IMMEDIATE;
	/* CG*/
		push_operand (NULL, yystack.l_mark[0].itype, IMMEDIATE);
	}
break;
case 79:
#line 467 "src/cstr-parser.y"
	{ 
		yyval.exp.typ 	= STRING;
		yyval.exp.sval 	= yystack.l_mark[0].strval;
		yyval.exp.ival	= 0; /*empty value*/
		yyval.exp.idptr 	= NULL; 
		yyval.exp.mtyp	= IMMEDIATE;
	/* CG*/
		push_string (yystack.l_mark[0].strval);
	}
break;
case 80:
#line 477 "src/cstr-parser.y"
	{ yyval.exp = yystack.l_mark[-1].exp; }
break;
#line 1142 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = YYEOF;
#if YYDEBUG
            if (yydebug)
            {
                yys = yyname[YYTRANSLATE(yychar)];
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == YYEOF) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack) == YYENOMEM)
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (YYINT) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    YYERROR_CALL("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
