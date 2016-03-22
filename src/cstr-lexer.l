/* Erik Schluter
 * 3/21/2016
 */
%{
#include <stdlib.h>
#include <string.h>
#include "compilerAPI.h"
#include "y.tab.h"
%}

%array

RESERV_IF	"if"
RESERV_ELSE	"else"
RESERV_WHILE	"while"
RESERV_DO	"do"
RESERV_FOR	"for"
RESERV_RETURN	"return"
TYPE_INT	"int"
TYPE_STRING	"string"
TYPE_EXTERN	"extern"
IDENT		[a-zA-Z][a-zA-Z0-9_]*
CONSTINT	0|[1-9][0-9]*
CONSTSTR	\"[^\"]*\"
ASSIGN_OP	"="
ADD_OP		"+"
SUB_OP		"-"
LEFT_SHIFT	"<<"
RIGHT_SHIFT	">>"
IS_EQUAL	"=="
NOT_EQUAL	"!="
LESS_THAN	"<"
GRE_THAN	">"
LEQ		"<="
GREQ		">="
MULT_OP		"*"
DIV_OP		"/"
MOD_OP		"%"
SEMICOLON	";"
COMMA		","
LPAREN		"("
RPAREN		")"
LBRACE		"{"
RBRACE		"}"
LBRACKET	"["
RBRACKET	"]"
WHITESPACE	[ \t\f\v]
NEWLINE		[\n]
LINE_COMMENT	"//"
BEGIN_COMMENT	"/*"
IGNOREMACRO	"#"

%%

{RESERV_IF}	{ return IF; }
{RESERV_ELSE}	{ return ELSE; }
{RESERV_WHILE}	{ return WHILE; }
{RESERV_DO}	{ return DO; }
{RESERV_FOR}	{ return FOR; }
{RESERV_RETURN}	{ return RETURN; }
{TYPE_INT}	{ return INTT; }
{TYPE_STRING}	{ return STRINGT; }
{TYPE_EXTERN}	{ return EXTERNT; }
{IDENT}		{ yylval.idptr = strcpy( (char*)malloc(strlen(yytext)+1), yytext ); return IDENT; }
{CONSTINT}	{ yylval.itype = atoi(yytext); return CONST_INT; }
{CONSTSTR}	{ 	
			// remove the parenthesis
			char * tempstr; unsigned int len;//char * tok; unsigned int i; unsigned int endindex; int sub = 3;
			len = strlen(yytext);
			tempstr = strcpy( (char*)malloc(len), &yytext[1] );
			tempstr[len-2] = '\0';
			yylval.strval = tempstr;
			return CONST_STRING;
		}
{ASSIGN_OP}	{ return ASSIGNMENT; }
{ADD_OP}	{ return PLUS; }
{SUB_OP}	{ return MINUS; }
{LEFT_SHIFT}	{ return SHIFTLEFT; }
{RIGHT_SHIFT}	{ return SHIFTRIGHT; }
{IS_EQUAL}	{ return EGAL; }
{NOT_EQUAL}	{ return DIFF; }
{LESS_THAN}	{ return INF; }
{GRE_THAN}	{ return SUP; }
{LEQ}		{ return INFEQUAL; }
{GREQ}		{ return SUPEQUAL; }
{MULT_OP}	{ return MULTI; }
{DIV_OP}	{ return DIV; }
{MOD_OP}	{ return MODULO; }
{SEMICOLON}	{ return ';'; }
{COMMA}		{ return ','; }
{LPAREN}	{ return '('; }
{RPAREN}	{ return ')'; }
{LBRACE}	{ return '{'; }
{RBRACE}	{ return '}'; }
{LBRACKET}	{ return '['; }
{RBRACKET}	{ return ']'; }

{LINE_COMMENT}	{ while ( input() != '\n' ); }
{IGNOREMACRO}	{
		  while ( input() != '\n' );
		  reset_line_counter();
		}

{BEGIN_COMMENT}	{
			char in, prev;
			for (;;) {
				while ( (in = input()) != '/' )
					prev = in;

				if ( prev == '*' ) {
					input();
					break;
				}
			}
}

{WHITESPACE}	{}
{NEWLINE}	{ increment_line_counter(); }

.		{
		  printf("%s:\t Lex ERROR (line %d): invalid token\n", yytext, get_line_number() );
		  goto_exit();
		}

%%

int yywrap() {
	return(1);
}
