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
extern YYSTYPE yylval;
