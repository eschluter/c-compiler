%{
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
%}

%union {
	decl_t dclt;
	char * idptr;
	char * strval;
	TYPE tval;
	int itype;
	EXPT exp;
}

%token INTT
%token STRINGT
%token <itype> CONST_INT
%token <strval> CONST_STRING

%token <idptr> IDENT

%token EXTERNT

%token IF
%token ELSE
%token WHILE
%token DO
%token RETURN
%token FOR
%token THEN

%token ASSIGNMENT
%token INF
%token EGAL
%token SUP
%token INFEQUAL
%token SUPEQUAL
%token DIFF

%token PLUS
%token MINUS
%token MULTI
%token DIV

%token SHIFTRIGHT
%token SHIFTLEFT
%token MODULO

%type <tval> type
%type <dclt> declarator
%type <dclt> declaration
%type <dclt> function_definition
%type <dclt> declarator_list

%%

program :  
external_declaration 
| program external_declaration 
;

external_declaration :  
declaration 	// Declaration Global			
	{ process_declaration ($1.dectype); }
| EXTERNT declaration // Set Extern attribute			
	{ process_extern($2.dectype); }
| function_definition 
	{ process_declaration ($1.dectype); }
;

function_definition :  
type function_declarator decl_glb_fct compound_instruction // generate code function
 	{ 	type_check_return($<idptr>2, $1);
		push_back_dec($<idptr>2, FUNC); 
		$$.dectype = $1; } 
;

decl_glb_fct :
	{ generate_function_header (); }
;

declaration :  
type declarator_list ';' 		// pass type to next level
	{ $$.dectype = $1; }
;

type :  
INTT		{$$=INT;}		// set INT
| STRINGT	{$$=STRING;}		// set STRING
;

declarator_list :  
declarator 				// create declaration list entry (see documentation)
	{ push_back_dec ($1.idptr, $1.idtype); }
| declarator_list ',' declarator
	{ push_back_dec ($3.idptr, $3.idtype); }	
;

declaration_list :  
declaration				// local declarations
	{ process_declaration ($1.dectype); }
| declaration_list declaration
	{ process_declaration ($2.dectype); }
| declaration_list INTT IDENT '[' CONST_INT ']' ';'
	{ process_matrix_declaration ($3, $5, 0); }	// array decl
| declaration_list INTT IDENT '[' CONST_INT ']' '[' CONST_INT ']' ';'	// matrix decl - only local allowed - stack'd
	{ process_matrix_declaration ($3, $5, $8); }
;

declarator :  
IDENT 
	{ $$.idptr = $1; $$.idtype = VAR; }		// Set Variable
| function_declarator 
	{ $$.idptr = $<idptr>1; $$.idtype = FUNC; }	// Set Function
;

function_declarator :  
IDENT '(' ')' 
	{ $<idptr>$=$1; set_function_id ($1); }		// Create function name
| IDENT '(' parameter_list ')' 
	{ $<idptr>$=$1; set_function_id ($1); }  	// Create partial function 
;

parameter_list :  
parameter_declaration 			
| parameter_list ',' parameter_declaration 		// Insert parameters
;

parameter_declaration :  
type IDENT 						// insert parameters into symbol table
	{ process_p_declaration ($1, $2); }
;

instruction :  
';'  
| compound_instruction 		{ generate_else(); }
| expression_instruction  	{ generate_else(); }
| iteration_instruction  	{ }
| select_instruction  		{ }
| jump_instruction 		{ generate_else(); }
;

expression_instruction :              
expression ';'   
| assignment ';' 
;

assignment :  
IDENT ASSIGNMENT expression 
	{
	// TC
		type_check_assignment ( get_id_type($1), $<exp>3.typ );
		$<idptr>$ = $1; /*free($1);*/
	// CG
		generate_assignment ($1, $<exp>3.idptr, $<exp>3.ival, $<exp>3.typ, $<exp>3.mtyp);
	}
| IDENT '[' expression ']' ASSIGNMENT expression
	{
	// TC
		type_check_array_index ($<exp>3.typ);
		type_check_assignment ( $<exp>1.typ, $<exp>6.typ );
	// CG
		index_array ($1, $<exp>3.idptr, $<exp>3.ival, $<exp>3.mtyp, 1);
		generate_assignment ($1, $<exp>6.idptr, $<exp>6.ival, $<exp>6.typ, $<exp>6.mtyp);
	}
| IDENT '[' expression ']' '[' expression ']' ASSIGNMENT expression
	{
	// TC
		type_check_matrix_index ($<exp>3.typ, $<exp>6.typ);
		type_check_assignment ( $<exp>1.typ, $<exp>9.typ);
	// CG
		index_matrix ($1, $<exp>3.idptr, $<exp>3.ival, $<exp>3.mtyp, $<exp>6.idptr, $<exp>6.ival, $<exp>6.mtyp, 1);
		generate_assignment ($1, $<exp>9.idptr, $<exp>9.ival, $<exp>9.typ, $<exp>9.mtyp);
	}
;

compound_instruction :  
block_start declaration_list instruction_list block_end 
| block_start declaration_list block_end 
| block_start instruction_list block_end 
| block_start block_end 
;


block_start :  
'{'  // enter new scope - create new symbol table on stack
	{ 
	// CG
		generate_loop_beg_block ();
	//
		enter_scope ();
	}
;

block_end :  
'}' // Exit current scope - Empty hash table
	{ exit_scope (); }
;

instruction_list :  
instruction  
| instruction_list instruction 
;

select_instruction :  
cond_instruction instruction 
	{
	//CG
		generate_ifend ();
	}
| cond_instruction instruction ELSE instruction 
	{ 
	// CG
		generate_ifend ();
	}
;

cond_instruction :  
IF '(' condition ')' 
	{
	// CG
		generate_if ($<exp>3.compar);
	} 
;

iteration_instruction :  
WHILE '(' condition ')' instruction // Handle while loop
	{
	// CG
		terminate_while ();
	}
| DO instruction WHILE '(' condition ')' 
	{ 
	// CG
		terminate_do_while ($<exp>5.compar);
	}
| FOR '(' assignment ';' condition ';' assignment ')' instruction 
	{ 
	// CG
		terminate_for ();
	}
;

jump_instruction:  
RETURN expression ';' 
	{
	// TC
		push_back_returntype ($<exp>2.typ);
	// CG
		generate_freturn ($<exp>2.idptr, $<exp>2.ival, $<exp>2.typ, $<exp>2.mtyp);
	}
;

condition :
expression comparison_operator expression
	{
		OP opoverride = COMPARISON;
		$<exp>$ = $<exp>2;
	// TC
		if ( $<exp>1.typ == STRING && ($<exp>2.compar == EQUAL || $<exp>2.compar == NEQUAL) ) {
			type_check_equality ($<exp>1.typ, $<exp>3.typ);
			if ($<exp>2.compar == EQUAL) {
				$<exp>$.compar = STREQUAL;
			} else {
				$<exp>$.compar = STRNEQUAL;
			}
			opoverride = STRCMP;
		} else {
			type_check_comparison ($<exp>1.typ, $<exp>3.typ);
		}
	// CG
		generate_loop_begin ($<exp>$.compar);	// by default label each comparison - handle IF individually
		generate_operation (opoverride);
	}
;

comparison_operator :  
EGAL  		{$<exp>$.compar = EQUAL;}
| DIFF 		{$<exp>$.compar = NEQUAL;} 
| INF  		{$<exp>$.compar = INFERIOR;}
| SUP  		{$<exp>$.compar = SUPERIOR;}
| INFEQUAL 	{$<exp>$.compar = INFERIOREQ;}
| SUPEQUAL 	{$<exp>$.compar = SUPERIOREQ;} 
;

expression :  
expression_additive
	{ $<exp>$ = $<exp>1; }
| expression SHIFTLEFT expression_additive //  Compute expression
	{ 	
	// TC
		$<exp>$.typ	= type_check_bitwise ($<exp>1.typ, $<exp>3.typ); 
		$<exp>$.mtyp	= RESULT;
	// CG
		generate_operation (LSHIFT);
	}
| expression SHIFTRIGHT expression_additive // Compute expression
	{ 
	// TC
		$<exp>$.typ	= type_check_bitwise ($<exp>1.typ, $<exp>3.typ); 
		$<exp>$.mtyp	= RESULT;
	// CG
		generate_operation (RSHIFT);
	}
;

expression_additive :  
expression_multiplicative
	{ $<exp>$ = $<exp>1; }
| expression_additive PLUS expression_multiplicative // Compute expression
	{ 	
	// TC
		$<exp>$.typ	= type_check_addition ($<exp>1.typ, $<exp>3.typ); 
		$<exp>$.mtyp	= RESULT;
	// CG
		switch ($<exp>$.typ) {
			case INT:
				generate_operation (ADDITION);
				break;
			case STRING:
				generate_operation (STRCAT);
				break;
		}
	}
| expression_additive MINUS expression_multiplicative // Compute expression
	{ 
	// TC
		$<exp>$.typ	= type_check_numerical ($<exp>1.typ, $<exp>3.typ); 
		$<exp>$.mtyp	= RESULT;
	// CG
		generate_operation (SUBTRACTION);
	}
;

expression_multiplicative :  
unary_expression
	{ $<exp>$ = $<exp>1; }
| expression_multiplicative MULTI unary_expression
	{ 	
	// TC
		$<exp>$.typ	= type_check_numerical ($<exp>1.typ, $<exp>3.typ); 
		$<exp>$.mtyp	= RESULT;
	// CG
		generate_operation (MULTIPLY);
	}
| expression_multiplicative DIV unary_expression
	{ 	
	// TC
		$<exp>$.typ	= type_check_numerical ($<exp>1.typ, $<exp>3.typ); 
		$<exp>$.mtyp	= RESULT;
	// CG
		generate_operation (DIVIDE);
	}
| expression_multiplicative MODULO unary_expression
	{ 
	// TC
		$<exp>$.typ 	= type_check_modulo ($<exp>1.typ, $<exp>3.typ);
		$<exp>$.mtyp	= RESULT;
	// CG
		generate_operation (MOD);
	}
;

unary_expression:  
array_expression
	{ $<exp>$ = $<exp>1; }
| MINUS unary_expression
	{ 
		$<exp>2.mtyp	= RESULT;
		$<exp>$ 	= $<exp>2;
	// CG
		generate_operation (UNARY_MINUS);
	}
;

array_expression:
expression_postfixee
	{ $<exp>$ = $<exp>1; }
| IDENT '[' expression ']'
	{ 
	// TC
		$<exp>$.typ = type_check_array_index ($<exp>3.typ);
		$<exp>$.idptr = $1;
		$<exp>$.mtyp = RESULT;
	// CG
		index_array ($1, $<exp>3.idptr, $<exp>3.ival, $<exp>3.mtyp, 0);
	}
| IDENT '[' expression ']' '[' expression ']'
	{
	// TC
		$<exp>$.typ = type_check_matrix_index ($<exp>3.typ, $<exp>6.typ);
		$<exp>$.idptr = $1;
		$<exp>$.mtyp = RESULT;
	// CG
		index_matrix ($1, $<exp>3.idptr,$<exp>3.ival,$<exp>3.mtyp, $<exp>6.idptr,$<exp>6.ival,$<exp>6.mtyp,0);
	}
;

expression_postfixee :  
primary_expression 
	{ $<exp>$ = $<exp>1; }
| IDENT '(' argument_expression_list')' 
	{ 	
		$<exp>$.typ 	= get_id_type ($1);
		type_check_fparams ($1);
		call_function ($1);
		$<exp>$.idptr 	= $1; 
		/*free($1);*/
		$<exp>$.mtyp 	= RESULT;
	}
| IDENT '(' ')' 
	{ 	
		$<exp>$.typ 	= get_id_type ($1);
		call_function ($1);
		$<exp>$.idptr 	= $1;
		/*free($1);*/
		$<exp>$.mtyp 	= RESULT;
	}
;

argument_expression_list:  
expression
	{ push_fparam ($<exp>1.idptr, $<exp>1.typ, $<exp>1.mtyp, $<exp>1.ival); }
| argument_expression_list',' expression 
	{ push_fparam ($<exp>3.idptr, $<exp>3.typ, $<exp>3.mtyp, $<exp>3.ival); }
;

primary_expression :  
IDENT  
	{ 
		$<exp>$.typ 	= get_id_type ($1);
		$<exp>$.idptr 	= $1; /*free($1);*/ 
		$<exp>$.ival 	= 0; //empty value
		$<exp>$.mtyp 	= REFERENCE;
	// CG
		push_operand ($1, 0, REFERENCE);
	}
| CONST_INT
	{ 
		$<exp>$.typ 	= INT;
		$<exp>$.ival 	= $1;
		$<exp>$.idptr 	= NULL; 
		$<exp>$.mtyp 	= IMMEDIATE;
	// CG
		push_operand (NULL, $1, IMMEDIATE);
	}
| CONST_STRING 
	{ 
		$<exp>$.typ 	= STRING;
		$<exp>$.sval 	= $1;
		$<exp>$.ival	= 0; //empty value
		$<exp>$.idptr 	= NULL; 
		$<exp>$.mtyp	= IMMEDIATE;
	// CG
		push_string ($1);
	}
| '(' expression ')'
	{ $<exp>$ = $<exp>2; }
;

%%

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
