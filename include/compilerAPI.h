/* Erik Schluter
 * 3/21/2016
 */
#pragma once
#include "symboltable.h"
#include "istack.h"

// operation types
typedef enum opers {	ADDITION, SUBTRACTION, 
			MULTIPLY, DIVIDE, MOD,
			UNARY_MINUS,
			LSHIFT, RSHIFT,
			COMPARISON,
			STRCAT, STRCMP
} OP;

// comparison types
typedef enum compst { 	EQUAL, NEQUAL,
			INFERIOR, SUPERIOR,
			INFERIOREQ, SUPERIOREQ,
			STREQUAL, STRNEQUAL
} COMPT;

void initialize_symboltable ();
void destroy_symboltable ();

// declarations
void push_back_dec (char * id, KIND k);
void process_declaration (TYPE t);
void process_extern (TYPE t);
void process_p_declaration (TYPE t, char * id);
void process_matrix_declaration (char * id, int dim1, int dim2);

// stack management
void enter_scope ();
void exit_scope ();

// type checking
TYPE get_id_type (char * id);
void push_back_tcheckparam (TYPE t);
void push_back_returntype (TYPE t);
void type_check_return (char * fid, TYPE t);
void type_check_fparams (char * fid);
TYPE type_check_assignment (TYPE left, TYPE right);
TYPE type_check_comparison (TYPE left, TYPE right);
TYPE type_check_equality (TYPE left, TYPE right);
TYPE type_check_bitwise (TYPE left, TYPE right);
TYPE type_check_addition (TYPE left, TYPE right);
TYPE type_check_numerical (TYPE left, TYPE right);
TYPE type_check_modulo (TYPE left, TYPE right);
TYPE type_check_array_index (TYPE ind);
TYPE type_check_matrix_index (TYPE left, TYPE right);

// file line counter utilities
void increment_line_counter();
void reset_line_counter();
int get_line_number ();

// code generation
void generate_operation (OP o);
void index_array (char * arr_id, char * ind_id, int ind_val, MEMTYPE m, int is_assigment);
void index_matrix (char * mat_id, char * ind1_id,int ind1_val,MEMTYPE m1, char * ind2_id,int ind2_val,MEMTYPE m2, int is_assignment);
void push_fparam (char * id, TYPE t, MEMTYPE mt, int val);
void push_operand (char * id, int val, MEMTYPE m);
void push_string (char * id);
void set_function_id (char * id);
void generate_function_header ();
void call_function (char * func_id);
void generate_freturn (char * id, int ival, TYPE t, MEMTYPE mt);
void generate_assignment (char * id, char * exp_id, int val, TYPE t, MEMTYPE mt);
void generate_if (COMPT c);
void generate_else ();
void generate_ifend ();
void generate_loop_begin (COMPT c);
void generate_loop_beg_block ();
void terminate_for ();
void terminate_while ();
void terminate_do_while (COMPT c);
