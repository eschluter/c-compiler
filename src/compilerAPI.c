#include "compilerAPI.h"
#include <stdio.h>
#include <string.h>

// private data members
//-----------------------------------------------------------------------
st_stack * sts;    // the big daddy symbol table stack
istack * paramstack; // keep function call parameters to check
List * returncheck; // keep type of all return calls to check
istack * inststack; // stack to keep track of machine stack
istack * globstack; // store globals
istack * strstack; // store string literals
typedef enum errors { 	TYPE_WARNING, TYPE_ERROR, TYPE_ERROR_COMP, TYPE_ERROR_STR_COMP, TYPE_ERROR_BITWISE,
			TYPE_ERROR_MODULO, TYPE_ERROR_ASSIGNMENT, TYPE_ERROR_FPARAM, TYPE_ERROR_FRETURN,
			OVERLOADED_DECL_ERROR, VAR_CONFLICT_ERROR,
			UNDECLARED_ID_ERROR,
			MATRIX_DIM_ERROR, ARRAY_IND_TYPE_ERROR, MATRIX_IND_TYPE_ERROR, NON_ARRAY_INDEX
} ERRORS; 
int shouldSetExtern = 0; // boolean flag for extern attribute
unsigned int lineCounter = 1;
FILE * fp; // output file pointer;
char * fdecl_id = NULL; // holds the function id name to create label in assembly output
 // stack offsets
unsigned int currentOffset = 0; // keeps track of the offset frontier for locals declared on the stack
unsigned int param_spoffset = 0; // keep track of parameter offset from stack pointer for eval'd parameters
 // label counters
unsigned int looplabelcount = 2; // keep track of loop jump labels
unsigned int strlabelcount  = 0; // keep track of string labels
COMPT loopevaltype; // propogate the comparison type for while and for loops
unsigned int suppressIter = 1; // suppressIter for iter inst output
unsigned int suppressBody = 1;
unsigned int functionBlock = 0; // suppressIter do when declaring function labels

// private functions
//-----------------------------------------------------------------------
void roll_back_params(List * pl);
void reallocate_paramslist();
void process_single_declaration (node * d, TYPE t);
void error_handler( ERRORS e, char * id );
void goto_exit ();
void generate_main();
void generate_printandexit();
void generate_globals();
void generate_strings();
void generate_strcat();
void generate_strcmp();
void generate_num2str();
void flush_istack(unsigned int convertint);
void dump_operands();
unsigned int flush_paramstack(unsigned int numParams);
void push_back_global (char * id);
void generate_jump_conditional (COMPT cpt, unsigned int label);
void generate_for_iter_inst ();
void clean_loop_labels ();


//implementation
//-----------------------------------------------------------------------

void increment_line_counter () {
	lineCounter++;
}

void reset_line_counter () {
	lineCounter = 1;
}

int get_line_number () {
	return lineCounter;
}

// in case of overloaded function declaration, parameters inserted into
//  symbol table will be removed when this is called
void roll_back_params (List * pl) {
	node * current = pl->head;
	// run through params list
	while ( current != NULL ) {
		remove_from_table (sts->current_scope->table, current->name); 
		current = current->next;
	}
}

void reallocate_paramslist() {
	sts->current_scope->paramslist = (List*) malloc (sizeof(List));
	list_initialize (sts->current_scope->paramslist);
}


void initialize_symboltable () {
	// allocate space for symbol stack
	sts = (st_stack*) malloc (sizeof(st_stack));
	stack_init (sts);
	// allocate list for type checking
	paramstack = (istack*) malloc (sizeof(List));
	istack_init (paramstack);
	// allocate return call check list
	returncheck = (List*) malloc (sizeof(List));
	list_initialize (returncheck);
	// allocate operator stack
	inststack = (istack*) malloc (sizeof(istack));
	istack_init (inststack);
	// allocate global param stack
	globstack = (istack*) malloc (sizeof(istack));
	istack_init (globstack);
	// allocate string stack
	strstack = (istack*) malloc (sizeof(istack));
	istack_init (strstack);
	// open output assembly file
	fp = fopen("out.s","w");
}

void destroy_symboltable () {
	generate_globals();
	generate_strings();
	// free stack
	stack_destroy (sts);
	free (sts);
	// free params type check list
	istack_destroy(paramstack);
	free(paramstack);
	// free return call check list
	list_destroy(returncheck);
	free(returncheck);
	// free operator stack
	istack_destroy (inststack);
	free (inststack);
	// free global stack
	istack_destroy (globstack);
	free (globstack);
	// free string stack
	istack_destroy (strstack);
	free (strstack);
	// close output file
	fclose(fp);
}


void push_back_dec (char * id, KIND k) {
	// append node onto decl list
	append_node (sts->current_scope->declist, id, k, UNKNOWN, 0, sts->current_scope->paramslist);
	// generate new params list
	reallocate_paramslist ();
}

void process_extern (TYPE t) {
	shouldSetExtern = 1;
	process_declaration (t);
	shouldSetExtern = 0;
}
	
void process_declaration (TYPE t) {
	node * n;
	// run through declaration list
	n = sts->current_scope->declist->head;
	while (n != NULL) {
		process_single_declaration (n, t);
		// set param pointer to NULL so list destroy won't kill it
		n->plist = NULL;
		n = n->next;
	}
	list_destroy (sts->current_scope->declist);
	// reset extern flag
	shouldSetExtern = 0;
}

void process_single_declaration (node * decl, TYPE t) {
	node * n;
	char * idcpy;
	KIND koverride;
	int offsetoverride = 0; // you can't have zero offset for stack elements so this marks global ref
	// make a copy of id name
	idcpy = strcpy ( (char*)malloc(strlen(decl->name)+1), decl->name);
	// check extern flag and print action +++++++++
	if (shouldSetExtern) {
		koverride = EXTERN;
	} else {
		koverride = decl->k;
		if (koverride == VAR) {
			if (sts->current_scope->s == LOCAL) {
				fprintf (fp, "\tsubl\t$4, %%esp\n");
				currentOffset -= 4;	
				offsetoverride = currentOffset;
			} else {
				push_back_global (idcpy); //TODO-check this for memory things
			}
		}
	}
	// insert symbol
	if ( (n = st_insert_id (sts, idcpy, koverride, t, offsetoverride, decl->plist)) != NULL ) {
		if (compare_symbol (n, koverride, t, decl->plist) > 0)
			error_handler(OVERLOADED_DECL_ERROR, NULL);
		roll_back_params(decl->plist);
		list_destroy(decl->plist);
		free(decl->plist);
	}
}


void process_p_declaration (TYPE t, char * id) {
	char * idcpy;
	int baseoffset;
	// calculate base pointer offset
	baseoffset = 8 + (4 * sts->current_scope->paramslist->size);
	// for function parameter declarations
	st_insert_id (sts, id, PARAM, t, baseoffset, NULL);
	// make copy of id name
	idcpy = strcpy( (char*)malloc(strlen(id)+1), id );
	// fill the paramslist
	append_node (sts->current_scope->paramslist, idcpy, PARAM, t, baseoffset, NULL);
}

void process_matrix_declaration (char * id, int dim1, int dim2) {
	int subOff = 0;
	int offsetoverride;
	KIND koverride;
	List * dimlist;
	node * n;
	char * idcpy;
	// check for invalid dimensions
	if ( (dim1 <= 0) || (dim2 < 0) ) {
		error_handler (MATRIX_DIM_ERROR, id);
	}
	// make a copy of id name
	idcpy = strcpy ( (char*)malloc(strlen(id)+1), id);
	// build list to hold dimensions
	dimlist = (List*) malloc (sizeof(List));
	list_initialize (dimlist);
	// determine total space on stack and set dimensions
	if (dim2 == 0) {
		subOff = dim1 * 4;
		koverride = ARRAY;
		append_node (dimlist, NULL, ARRAY, UNKNOWN, dim1, NULL);
	} else {
		subOff = dim1 * dim2 * 4;
		koverride = MATRIX;
		append_node (dimlist, NULL, MATRIX, UNKNOWN, dim1, NULL);
		append_node (dimlist, NULL, MATRIX, UNKNOWN, dim2, NULL);
	}
	// create space on stack
	fprintf (fp, "\tsubl\t$%d, %%esp\n", subOff);
	offsetoverride = currentOffset - 4; // save the array stack beginning into symtab
	currentOffset -= subOff;	
	// insert into symtab
	if ( (n = st_insert_id (sts, idcpy, koverride, INT, offsetoverride, dimlist)) != NULL ) {
		if (compare_symbol (n, koverride, INT, dimlist) > 0)
			error_handler(OVERLOADED_DECL_ERROR, NULL);
	}
}

void enter_scope () {
	st_enter_scope (sts, LOCAL);
}

void exit_scope () {
	st_exit_scope (sts);
}


/* TYPE CHECKING ---------------------------------------------------------- */

TYPE get_id_type ( char * id ) {
	node * symb;
	// table lookup
	symb = lookup (sts, id);
	if (symb != NULL) {
		return symb->t;
	} else {
		error_handler (UNDECLARED_ID_ERROR, id);
	}
}

TYPE type_check_assignment ( TYPE left, TYPE right ) {
	// right operand must match left's type
	if ( right != left )
		error_handler (TYPE_ERROR_ASSIGNMENT, NULL);
	return right;
}	

TYPE type_check_comparison ( TYPE left, TYPE right ) {
	// both operands need to be of same type (int or float)
	// no strings allowed
	if ( left == STRING || right == STRING ) {
		error_handler (TYPE_ERROR_STR_COMP, NULL);
	} else if ( left != right ) {
		error_handler (TYPE_ERROR_COMP, NULL);
	}
	return left;
}

TYPE type_check_equality ( TYPE left, TYPE right ) {
	// both operands of same type
	if ( left != right ) {
		error_handler (TYPE_ERROR_COMP, NULL);
	}
	return left;
}

TYPE type_check_bitwise ( TYPE left, TYPE right ) {
	// both must be of integral type
	if ( left != INT || right != INT )
		error_handler (TYPE_ERROR_BITWISE, NULL);
	return left;
}

TYPE type_check_numerical ( TYPE left, TYPE right ) {
	// comparison type checking is identical
	if ( left == STRING || right == STRING ) {
		error_handler (TYPE_ERROR, NULL);
	} else if ( left != right ) {
		error_handler (TYPE_ERROR, NULL);
	}
	return left;
}

TYPE type_check_addition ( TYPE left, TYPE right ) {
	// addition can handle mixed string and integer
	// for this case return string type then convert the integer later
	if ( left != right ) {
		return STRING;
	}
	return left;
}

TYPE type_check_modulo (TYPE left, TYPE right) {
	// modulo only takes integral types
	if ( left != INT || right != INT )
		error_handler (TYPE_ERROR_MODULO, NULL);
	return left;
}

TYPE type_check_array_index (TYPE ind) {
	// only integer indices allowed
	if (ind != INT)
		error_handler (ARRAY_IND_TYPE_ERROR, NULL);
	return ind;
}

TYPE type_check_matrix_index (TYPE d1, TYPE d2) {
	// only integer
	if ( (d1 != INT) || (d2 != INT) )
		error_handler (MATRIX_IND_TYPE_ERROR, NULL);
	return d1;
}

void type_check_fparams ( char * fid ) {
	node * tcurrent;
	inode * checkcurrent;
	unsigned int numParams;
	//tcurrent = (lookup(sts, fid))->plist->head;
	tcurrent  = lookup(sts, fid);
	numParams = tcurrent->plist->size;
	tcurrent  = tcurrent->plist->head;
	//checkcurrent = paramstack->base;
	checkcurrent = paramstack->current;
	// first find the start in the paramstack
	for (int i = 0; i < numParams-1; i++)
		checkcurrent = checkcurrent->prev;
	// run through table params list and check list
	while ( tcurrent != NULL && checkcurrent != NULL ) {
		if ( tcurrent->t != checkcurrent->t ) {
			error_handler (TYPE_ERROR_FPARAM, fid);
		}
		tcurrent = tcurrent->next;
		checkcurrent = checkcurrent->up;
	}
	// check to make sure we have same number of params
	// both should be NULL
	if ( (tcurrent != NULL) || (checkcurrent != NULL) ) {
		printf ("number of param error\n");
		error_handler (TYPE_ERROR_FPARAM, fid);
	}
}

void type_check_return ( char * fid, TYPE ft ) {
	node * current;
	current = returncheck->head;
	// run through all return calls
	while ( current != NULL ) {
		if ( current->t != ft )
			error_handler (TYPE_ERROR_FRETURN, fid);
		current = current->next;
	}
	// empty return check list
	list_destroy (returncheck);
}

void push_back_returntype ( TYPE t ) {
	// push return type onto save list	
	append_node (returncheck, NULL, FUNC, t, 0, NULL);
}


/* CODE GENERATION ------------------------------------------------------------------- */

void push_back_global ( char * id ) {
	// push on global declaration stack
	ipush (globstack, id, UNKNOWN, 0, 0, REFERENCE);
}

void push_string (char * str) {
	// push onto string stack
	// save the label value into the offset field
	ipush (strstack, str, UNKNOWN, 0, strlabelcount, REFERENCE);
	// push onto operand stack - store offset in val field
	ipush (inststack, NULL, STRING, strlabelcount, 0, IMMEDIATE);
	// increment string label
	strlabelcount++;
}

void push_fparam ( char * id, TYPE t, MEMTYPE mt, int val ) {
	unsigned int offsetoverride = 0;
	int valoverride = val;
	// check for arithmetic result argument and mark stack position
	if (mt == RESULT) {
		param_spoffset += 4;
		offsetoverride = param_spoffset;
	} else if (mt == IMMEDIATE && t == STRING) {
		valoverride = strlabelcount-1;
		dump_operands (); // dump unused operands remaining in inststack
	} else {
		dump_operands ();
	}
	ipush (paramstack, id, t, valoverride, offsetoverride, mt);
}

void generate_globals () {
	inode * current;
	current = globstack->current;
	// declare global section
	while (current != NULL) {
		fprintf (fp, "\t.comm\t%s,4,4\n", current->id);
		current = current->prev;
	}
}

void generate_strings () {
	inode * current;
	current = strstack->base;
	fprintf (fp, "\t.section\t.rodata\n");
	// run through string list - all strings literals in the source
	while (current != NULL) {
		fprintf (fp, ".LC%d:\n", current->offset);
		fprintf (fp, "\t.string\t\"%s\"\n", current->id);
		current = current->up;
	}
}

void index_array (char * arr_id, char * ind_id, int ind_val, MEMTYPE m, int is_assignment) {
	node * arrsymb;
	node * refsymb;
	// make sure array exists in symbol table
	if ( (arrsymb = lookup (sts, arr_id)) == NULL )
		error_handler (UNDECLARED_ID_ERROR, arr_id);
	// make sure we are indexing an array
	if ( arrsymb->k != ARRAY )
		error_handler (NON_ARRAY_INDEX, NULL);
	// process by index type
	switch (m) {
		case IMMEDIATE:
			if (is_assignment) {
				fprintf (fp, "\tmovl\t$%d, %%eax\n", arrsymb->offset / 4 - ind_val);
			} else {
				fprintf (fp, "\tpushl\t%d(%%ebp)\n", arrsymb->offset - 4*ind_val);
			}
			break;
		case REFERENCE:
			// check for global or local ref
			refsymb = lookup (sts, ind_id);
			// move array starting offset into register
			fprintf (fp, "\tmovl\t$%d, %%eax\n", arrsymb->offset / 4);
			if (refsymb->offset == 0) {
				fprintf (fp, "\tsubl\t%s, %%eax\n", ind_id);
			} else {
				fprintf (fp, "\tsubl\t%d(%%ebp), %%eax\n", refsymb->offset);
			}
			// now push the correct index value
			if (!is_assignment)
				fprintf (fp, "\tpushl\t(%%ebp, %%eax, 4)\n");
			break;
		case RESULT:
			// move array starting offset into register
			fprintf (fp, "\tmovl\t$%d, %%eax\n", arrsymb->offset / 4);
			fprintf (fp, "\tpopl\t%%ebx\n");
			fprintf (fp, "\tsubl\t%%ebx, %%eax\n");
			if (!is_assignment)
				fprintf (fp, "\tpushl\t(%%ebp, %%eax, 4)\n");
			break;
	}
	dump_operands();
}

void index_matrix (char * mat_id, char * ind1_id, int ind1_val, MEMTYPE m1, char * ind2_id, int ind2_val, MEMTYPE m2, int is_assignment) {
	node * matsymb;
	node * refsymb;
	// make sure matrix exists in symbol table
	if ( (matsymb = lookup (sts, mat_id)) == NULL )
		error_handler (UNDECLARED_ID_ERROR, mat_id);
	// make sure we are indexing a matrix
	if ( matsymb->k != MATRIX )
		error_handler (NON_ARRAY_INDEX, NULL);
	// check for two result indices and switch stack order if so
	if (m1 == RESULT && m2 == RESULT) {
		fprintf (fp, "\tpopl\t%%ecx\n");
		fprintf (fp, "\tpopl\t%%ebx\n");
		fprintf (fp, "\tpushl\t%%ecx\n");
		fprintf (fp, "\tpushl\t%%ebx\n");
	}
	// handle two constant indices
	if (m1 == IMMEDIATE && m2 == IMMEDIATE) {
		if (is_assignment) {
			fprintf (fp, "\tmovl\t%d, %%eax\n", (matsymb->offset / 4) - (ind1_val * matsymb->plist->head->offset + ind2_val));
		} else {
			fprintf (fp, "\tpushl\t%d(%%ebp)\n", matsymb->offset - 4*(ind1_val * matsymb->plist->head->offset + ind2_val));
		}
		return;
	}
	// handle first index (multiply)
	fprintf (fp, "\tmovl\t$%d, %%ebx\n", matsymb->plist->head->offset);
	switch (m1) {
		case REFERENCE:
			// check for global or local ref
			refsymb = lookup (sts, ind1_id);
			if (refsymb->offset == 0) {
				fprintf (fp, "\timull\t%s, %%ebx\n", ind1_id);
			} else {
				fprintf (fp, "\timull\t%d(%%ebp), %%ebx\n", refsymb->offset);
			}
			break;
		case RESULT:
			fprintf (fp, "\tpopl\t%%ecx\n");
			fprintf (fp, "\timull\t%%ecx, %%ebx\n", ind1_id);
			break;
	}
	// handle second index (add)
	//   move array starting offset into register
	fprintf (fp, "\tmovl\t$%d, %%eax\n", matsymb->offset / 4);
	switch (m2) {
		case REFERENCE:
			// check for global or local ref
			refsymb = lookup (sts, ind2_id);
			if (refsymb->offset == 0) {
				fprintf (fp, "\taddl\t%s, %%ebx\n", ind2_id);
			} else {
				fprintf (fp, "\taddl\t%d(%%ebp), %%ebx\n", refsymb->offset);
			}
			break;
		case RESULT:
			fprintf (fp, "\tpopl\t%%ecx\n");
			fprintf (fp, "\taddl\t%%ecx, %%ebx\n");
			break;
	}
	// subtract total offset from start offset
	fprintf (fp, "\tsubl\t%%ebx, %%eax\n");
	// now push the correct index value
	if (!is_assignment)
		fprintf (fp, "\tpushl\t(%%ebp, %%eax, 4)\n");
}

void generate_operation ( OP o ) {
	// first push operands onto assembly stack
	flush_istack(o == STRCAT);
	// print code based on operation type
	// must first handle top two operands on instruction stack
	if (o == UNARY_MINUS) {
		fprintf (fp, "\tpopl\t%%eax\n");
	} else if (o == STRCAT) {
		fprintf (fp, "\tpopl\t%%ecx\n");
		fprintf (fp, "\tpopl\t%%ebx\n");
	} else {
		fprintf (fp, "\tpopl\t%%ecx\n");
		fprintf (fp, "\tpopl\t%%eax\n");
	}
	switch (o) {
		case ADDITION:
			fprintf (fp, "\taddl\t%%ecx, %%eax\n");
			break;
		case SUBTRACTION:
			fprintf (fp, "\tsubl\t%%ecx, %%eax\n");
			break;
		case MULTIPLY:
			fprintf (fp, "\timull\t%%ecx, %%eax\n");
			break;
		case DIVIDE:
		case MOD:
			fprintf (fp, "\tmovl\t$0, %%edx\n"); //zero register EDX
			fprintf (fp, "\tcltd\n");
			fprintf (fp, "\tidivl\t%%ecx\n");
			break;
		case UNARY_MINUS: //TODO - there might be a better way to do this with bitwise ops
			fprintf (fp, "\timull\t$(-1), %%eax\n");
			break;
		case LSHIFT:
			fprintf (fp, "\tsall\t%%cl, %%eax\n");
			break;
		case RSHIFT:
			fprintf (fp, "\tsarl\t%%cl, %%eax\n");
			break;
		case COMPARISON:
			fprintf (fp, "\tcmpl\t%%ecx, %%eax\n");
			break;
		case STRCAT:
			generate_strcat ();
			fprintf (fp, "\taddl\t$8, %%esp\n");
			break;
		case STRCMP:
			generate_strcmp ();
			break;
	}
	// push result back on stack
	if (o == MOD) {
		// in the case of modulo we want the remainder in EDX
		fprintf (fp, "\tpushl\t%%edx\n");
	} else if (o != COMPARISON && o != STRCMP) {
		fprintf (fp, "\tpushl\t%%eax\n");
	}
}

void push_operand ( char * id, int val, MEMTYPE m ) {
	node * temp;
	TYPE tt;
	// check if this is a FOR loop condition
	if (sts->current_scope->loopBegLabel > 0 && !suppressIter) {
		//fprintf (fp, "set for iteration\n");
		generate_for_iter_inst ();
		suppressIter = 1;
	}
	// if we're pushing an id then we need to lookup in the symtab
	if (m == REFERENCE) {
		if ( (temp = lookup (sts, id)) == NULL )
			error_handler(UNDECLARED_ID_ERROR, id);
		tt = temp->t;
	} else {
		tt = INT;
	}
	// push operand onto instruction stack
	ipush (inststack, id, tt, val, 0, m);
}

void flush_istack (unsigned int convertint) {
	// For arithmetic operations we must use the stack like
	//   a queue. Therefore we start from the bottom and
	//   work upwards (see istack.h)
	node * refsymb;
	inode * current;
	current = inststack->base;
	// generate instruction
	while (current != NULL) {
		switch (current->memt) {
			case IMMEDIATE:
				switch (current->t) {
					case INT:
						fprintf (fp, "\tpushl\t$%d\n", current->val);
						if (convertint)
							generate_num2str();
						break;
					case STRING:
						fprintf (fp, "\tpushl\t$.LC%d\n", current->val);
						break;
				}
				break;
			case REFERENCE:
				// check for global or local ref
				refsymb = lookup (sts, current->id);
				if (refsymb->offset == 0) {
					fprintf (fp, "\tpushl\t%s\n", current->id);
				} else {
					fprintf (fp, "\tpushl\t%d(%%ebp)\n", refsymb->offset);
				}
				// check for integer conversion in the case of string cat
				if ( convertint && (refsymb->t == INT) )
					generate_num2str();
				break;
		}
		current = current->up;
	}
	istack_destroy(inststack);
}

void dump_operands () {
	// empty inststack
	istack_destroy (inststack);
}

void set_function_id (char * id) {
	fdecl_id = id;
}

void generate_function_header () {
	if (fdecl_id == NULL) {
		printf ("ERROR in write_function_label () : id pointer NULL\n Check code.");
		goto_exit();
	}
	// reset the stack pointer offset
	currentOffset = 0;
	// generate assembler global directives
	fprintf (fp, "\t.text\n");
	fprintf (fp, "\t.globl\t%s\n", fdecl_id);
	fprintf (fp, "\t.type\t%s, @function\n", fdecl_id);
	// output function section label
	fprintf (fp, "%s:\n", fdecl_id);
	fprintf (fp, "\tpushl\t%%ebp\n");
	fprintf (fp, "\tmovl\t%%esp, %%ebp\n");
	// set back to NULL. no free necessary - bound to symbol table entry
	//fdecl_id = NULL;
	// set function block flag
	functionBlock = 1;
} 

void call_function (char * func_id) {
	unsigned int cleansize;
	// push args onto stack if not a recursive call
	cleansize = flush_paramstack( (lookup(sts, func_id))->plist->size );
	// call function
	fprintf (fp, "\tcall\t%s\n", func_id);
	// clean up parameters
	fprintf (fp, "\taddl\t$%d, %%esp\n", cleansize);
	// push return value onto stack
	fprintf (fp, "\tpushl\t%%eax\n");
}

unsigned int flush_paramstack (unsigned int numParams) {
	int offset;
	inode * current;
	node * refsymb;
	current = paramstack->current;
	// run through params stack and push args in reverse order
	//while (current != NULL) {
	for (unsigned int i = 0; i < numParams; i++) {
		switch (current->memt) {
			case IMMEDIATE:
				switch (current->t) {
					case INT:
						fprintf (fp, "\tpushl\t$%d\n", current->val);
						break;
					case STRING:
						fprintf (fp, "\tpushl\t$.LC%d\n", current->val);
						break;
				}
				break;
			case REFERENCE:
				// check for global or local ref
				refsymb = lookup (sts, current->id);
				if (refsymb->offset == 0) {
					fprintf (fp, "\tpushl\t%s\n", current->id);
				} else {
					fprintf (fp, "\tpushl\t%d(%%ebp)\n", refsymb->offset);
				}
				break;
			case RESULT:
				// calculate offset from current stack position
				// only push if offset is greater than zero, otherwise param is already in position
				offset = param_spoffset - current->offset;
				if (offset > 0)
					fprintf (fp, "\tpushl\t%d(%%esp)\n", offset);
				break;
		}
		// increment esp counter
		param_spoffset += 4;
		// move to next param
		current = current->prev;
	}
	// mark the new current inode
	paramstack->current = current;
	// reinitialize stack and reset esp counter
	if (current == NULL)
		istack_destroy (paramstack);
	param_spoffset = 0;
	return (4 * numParams);
}

void generate_freturn ( char * id, int ival, TYPE t, MEMTYPE mt ) {
	node * refsymb;
	// handle based on expression type
	switch (mt) {
		case IMMEDIATE:
			switch (t) {
				case INT:
					fprintf (fp, "\tmovl\t$%d, %%eax\n", ival);
					break;
				case STRING:
					fprintf (fp, "\tmovl\t$.LC%d, %%eax\n", strlabelcount-1); // count incremented
					break;
			}
			break;
		case REFERENCE:
			// check for global or local ref
			refsymb = lookup (sts, id);
			if (refsymb == NULL)
				error_handler (UNDECLARED_ID_ERROR, id);
			if (refsymb->offset == 0) {
				fprintf (fp, "\tmovl\t%s, %%eax\n", id);
			} else {
				fprintf (fp, "\tmovl\t%d(%%ebp), %%eax\n", refsymb->offset);
			}
			break;
		case RESULT:
			fprintf (fp, "\tpopl\t%%eax\n");
			break;
	}
	fprintf (fp, "\tleave\n");
	fprintf (fp, "\tret\n");
	// purge the inststack
	dump_operands();
}

void generate_assignment(char * id, char * exp_id, int ival, TYPE t, MEMTYPE mt) {
	node * refsymb;
	char * tempstr;
	// lookup reference to assignment id
	//   no need to check presence of symbol because we already type checked
	refsymb = lookup (sts, id);
	// allocate space for string representing assignment location
	if (refsymb->k == ARRAY || refsymb->k == MATRIX) {
		tempstr = (char*) malloc (20*sizeof(char));
		sprintf (tempstr, "(%%ebp, %%eax, 4)");
	} else {
		if (strlen(id) > 9) {
			tempstr = (char*) malloc (strlen(id)*sizeof(char));
		} else {
			tempstr = (char*) malloc (10*sizeof(char));
		}
		if (refsymb->offset == 0) {
			sprintf (tempstr, "%s", id);
		} else {
			sprintf (tempstr, "%d(%%ebp)", refsymb->offset);
		}
	}
	// handle right expression based on type
	switch (mt) {
		case IMMEDIATE:
			switch (t) {
				case INT:
					fprintf (fp, "\tmovl\t$%d, %s\n", ival, tempstr);
					break;
				case STRING:
					fprintf (fp, "\tmovl\t$.LC%d, %s\n", strlabelcount-1, tempstr);
					break;
			}
			break;
		case REFERENCE:
			// check for global or local ref
			refsymb = lookup (sts, exp_id);
			if (refsymb->offset == 0) {
				fprintf (fp, "\tmovl\t%s, %%edx\n", exp_id);
			} else {
				fprintf (fp, "\tmovl\t%d(%%ebp), %%edx\n", refsymb->offset);
			}
			fprintf (fp, "\tmovl\t%%edx, %s\n", tempstr);
			break;
		case RESULT:
			fprintf (fp, "\tpopl\t%s\n", tempstr);
			break;
	}
	free (tempstr);
	// check FOR loop wait
	if (suppressIter && !suppressBody) {
		// jump to beginning
		fprintf (fp, "\tjmp\t.L%d\n", sts->current_scope->loopBegLabel);
		// print body label
		fprintf (fp, ".L%d:\n", sts->current_scope->forBodyBeg);
		suppressBody = 1;
	}
	dump_operands();
}

void generate_strcat () {
	fprintf (fp, "\tpushl\t%%ecx\n");
	fprintf (fp, "\tpushl\t$128\n");
	fprintf (fp, "\tcall\tmalloc\n");
	fprintf (fp, "\taddl\t$4, %%esp\n");
	fprintf (fp, "\tpushl\t%%eax\n");
	fprintf (fp, "\tpushl\t%%ebx\n");
	fprintf (fp, "\tpushl\t4(%%esp)\n");
	fprintf (fp, "\tcall\tstrcpy\n");
	fprintf (fp, "\taddl\t$12, %%esp\n");
	fprintf (fp, "\tpushl\t%%eax\n");
	fprintf (fp, "\tcall\tstrcat\n");
}

void generate_strcmp () {
	fprintf (fp, "\tpushl\t%%ecx\n");
	fprintf (fp, "\tpushl\t%%eax\n");
	fprintf (fp, "\tcall\tstrcmp\n");
	fprintf (fp, "\taddl\t$8, %%esp\n");
	fprintf (fp, "\tmovl\t$0, %%ecx\n");
	fprintf (fp, "\tcmpl\t%%ecx, %%eax\n");
}

void generate_num2str () {
	fprintf (fp, "\tpushl\t$12\n");
	fprintf (fp, "\tcall\tmalloc\n");
	fprintf (fp, "\taddl\t$4, %%esp\n");
	fprintf (fp, "\tpushl\t$.LC%d\n", strlabelcount);
	fprintf (fp, "\tpushl\t%%eax\n");
	fprintf (fp, "\tcall\tsprintf\n");
	fprintf (fp, "\tmovl\t0(%%esp), %%eax\n");
	fprintf (fp, "\taddl\t$12, %%esp\n");
	fprintf (fp, "\tpushl\t%%eax\n");
	// write format integer string to strstack
	ipush (strstack, "%d", UNKNOWN, 0, strlabelcount, REFERENCE);
	strlabelcount++;
}

/* Code Generation: control flow --------------------------------------------------------*/

void generate_if (COMPT cpt) {
	// get a false label and set
	sts->current_scope->falseLabel = looplabelcount++;
	// zero out loop labels generated from condition
	sts->current_scope->loopBegLabel = 0;
	sts->current_scope->loopEndLabel = 0;
	// generate jump conditonal statement
	generate_jump_conditional (cpt, sts->current_scope->falseLabel);
}

void generate_jump_conditional (COMPT cpt, unsigned int label) {
	// generate jump command on the false condition
	switch (cpt) {
		case EQUAL:
			fprintf (fp, "\tjne\t.L%d\n", label);
			break;
		case NEQUAL:
			fprintf (fp, "\tje\t.L%d\n", label);
			break;
		case INFERIOR:
			fprintf (fp, "\tjge\t.L%d\n", label);
			break;
		case SUPERIOR:
			fprintf (fp, "\tjle\t.L%d\n", label);
			break;
		case INFERIOREQ:
			fprintf (fp, "\tjg\t.L%d\n", label);
			break;
		case SUPERIOREQ:
			fprintf (fp, "\tjl\t.L%d\n", label);
			break;
		case STREQUAL:
			fprintf (fp, "\tjne\t.L%d\n", label);
			break;
		case STRNEQUAL:
			fprintf (fp, "\tje\t.L%d\n", label);
	}
}

void generate_else () {
	//fprintf (fp, "generate else\n");
	if (sts->current_scope->falseLabel > 0) {
		// if no end label has been set get new end label
		if (sts->current_scope->endLabel == 0)
			sts->current_scope->endLabel = looplabelcount++;
		// generate if exit label jump
		fprintf (fp, "\tjmp\t.L%d\n", sts->current_scope->endLabel);
		// generate false label from original if conditional eval
		fprintf (fp, ".L%d:\n", sts->current_scope->falseLabel);
	}
	// zero false label - gets reset on new if decl
	sts->current_scope->falseLabel = 0;
}

void generate_ifend () {
	if (sts->current_scope->endLabel > 0) {
		// generate end label if it exists
		if (sts->current_scope->endLabel != 0) {
			fprintf (fp, ".L%d:\n", sts->current_scope->endLabel);
			sts->current_scope->endLabel = 0;//reset labels
			sts->current_scope->falseLabel = 0;
		}
	}
}

void generate_loop_begin (COMPT c) {
	// check for current if else block
	// add label at the beggining of every comparison operator call
	if (sts->current_scope->endLabel == 0 && sts->current_scope->falseLabel == 0
		&& sts->current_scope->loopBegLabel == 0) { //also check for a do while block
		fprintf (fp, ".L%d:\n", looplabelcount);
		sts->current_scope->loopBegLabel = looplabelcount++;
		sts->current_scope->loopEndLabel = looplabelcount++;
	}
	// set eval type global
	loopevaltype = c;
	// unblock for iter labeling
	suppressIter = 0;
	suppressBody = 0;
}

void generate_loop_beg_block () {
	// check for loop
	if (sts->current_scope->loopBegLabel > 0) {
		//fprintf (fp, "set up while loop, %d\n", sts->current_scope->loopBegLabel);
		// this means we are in a while loop
		generate_jump_conditional (loopevaltype, sts->current_scope->loopEndLabel);
	} else if (sts->current_scope->falseLabel == 0 && sts->current_scope->endLabel == 0 && !functionBlock) {
		//fprintf (fp, "set up do while, %d\n",functionBlock);
		//finally this is a DO while
		fprintf (fp, ".L%d:\n", looplabelcount);
		sts->current_scope->loopBegLabel = looplabelcount++;
	}
	// suppressIter for iter output if not already
	suppressIter = 1;
	suppressBody = 1;
	functionBlock = 0;
}

void generate_for_iter_inst () {
	// get 2 more labels
	sts->current_scope->forIterBeg = looplabelcount++;
	sts->current_scope->forBodyBeg = looplabelcount++;
	// printf body jump and iter label
	generate_jump_conditional (loopevaltype, sts->current_scope->loopEndLabel);
	fprintf (fp, "\tjmp\t.L%d\n", sts->current_scope->forBodyBeg);
	fprintf (fp, ".L%d:\n", sts->current_scope->forIterBeg);
}
	
void terminate_for () {
	// jump to iteration label
	fprintf (fp, "\tjmp\t.L%d\n", sts->current_scope->forIterBeg);
	fprintf (fp, ".L%d:\n", sts->current_scope->loopEndLabel);
	// zero all labels
	clean_loop_labels ();
}

void terminate_while () {
	// jump to iteration label
	fprintf (fp, "\tjmp\t.L%d\n", sts->current_scope->loopBegLabel);
	fprintf (fp, ".L%d:\n", sts->current_scope->loopEndLabel);
	clean_loop_labels();
}

void terminate_do_while (COMPT cpt) {
	// generate jump command on the TRUE condition
	//  opposite of usual conditional evaluation
	switch (cpt) {
		case EQUAL:
			fprintf (fp, "\tje\t.L%d\n", sts->current_scope->loopBegLabel);
			break;
		case NEQUAL:
			fprintf (fp, "\tjne\t.L%d\n", sts->current_scope->loopBegLabel);
			break;
		case INFERIOR:
			fprintf (fp, "\tjl\t.L%d\n", sts->current_scope->loopBegLabel);
			break;
		case SUPERIOR:
			fprintf (fp, "\tjg\t.L%d\n", sts->current_scope->loopBegLabel);
			break;
		case INFERIOREQ:
			fprintf (fp, "\tjle\t.L%d\n", sts->current_scope->loopBegLabel);
			break;
		case SUPERIOREQ:
			fprintf (fp, "\tjge\t.L%d\n", sts->current_scope->loopBegLabel);
			break;
	}
	clean_loop_labels();
}

void clean_loop_labels () {
	sts->current_scope->loopBegLabel = 0;
	sts->current_scope->loopEndLabel = 0;
	sts->current_scope->forIterBeg 	= 0;
	sts->current_scope->forBodyBeg 	= 0;
}	
	


/* ERROR HANDLING -------------------------------------------------------------------- */

void error_handler (ERRORS e, char * id) {
	
	switch (e) {
		case TYPE_WARNING:
			printf ("WARNING (line %d): different but compatible types\n", lineCounter);
			break;
		case TYPE_ERROR:
			printf ("ERROR (line %d): Incompatible types\n", lineCounter);
			goto_exit();
			break;
		case TYPE_ERROR_FRETURN:
			printf ("ERROR (line %d): function '%s' - incompatible return type\n", lineCounter, id);
			goto_exit();
			break; 
		case TYPE_ERROR_FPARAM:
			printf ("ERROR (line %d): function '%s' - incompatable arguments\n", lineCounter, id);
			goto_exit();
			break;
		case TYPE_ERROR_ASSIGNMENT:
			printf ("ERROR (line %d): Assigning incompatible types\n", lineCounter);
			goto_exit();
			break;
		case TYPE_ERROR_COMP:
			printf ("ERROR (line %d): Incompatible comparison types\n", lineCounter);
			goto_exit();
			break;
		case TYPE_ERROR_STR_COMP:
			printf ("ERROR (line %d): String comparisons not allowed\n", lineCounter);
			goto_exit();
			break;
		case TYPE_ERROR_BITWISE:
			printf ("ERROR (line %d): Bitwise operators must be of intergral type\n", lineCounter);
			goto_exit();
			break;
		case TYPE_ERROR_MODULO:
			printf ("ERROR (line %d): Modulo only takes integral operands\n", lineCounter);
			goto_exit();
			break;
		case OVERLOADED_DECL_ERROR:
			printf ("ERROR (line %d): overloaded declaration\n", lineCounter);
			goto_exit();
			break;
		case VAR_CONFLICT_ERROR:
			printf ("ERROR (line %d): variable name conflict\n", lineCounter);
			goto_exit();
			break;
		case UNDECLARED_ID_ERROR:
			printf ("ERROR (line %d): undeclared identifier: %s\n", lineCounter, id);
			goto_exit();
			break;
		case MATRIX_DIM_ERROR:
			printf ("ERROR (line %d): invalid matrix dimensions: %s\n", lineCounter, id);
			goto_exit();
			break;
		case ARRAY_IND_TYPE_ERROR:
		case MATRIX_IND_TYPE_ERROR:
			printf ("ERROR (line %d): only integer indices allowed\n", lineCounter);
			goto_exit();
			break;
		case NON_ARRAY_INDEX:
			printf ("ERROR (line %d): cannot index a non-array object\n", lineCounter);
			goto_exit();
			break;
	}
}

void goto_exit() {
	destroy_symboltable();
	exit(1);
}
