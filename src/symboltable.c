/* Erik Schluter
 * 3/21/2016
 */
#include "symboltable.h"
#include <stdio.h>

// private functions ---------------------------------------------------
symtab * new_symboltable () {
	// allocate and initialize symbol table
	symtab * ret;
	ret 	   = (symtab*) malloc (sizeof(symtab));
	ret->table = (htbl*) malloc (sizeof(htbl));
	htbl_initialize (ret->table, 100);
	return ret;
}

List * new_list () {
	//allocate and initialize new list (for paramslist and declist)
	List * ret;
	ret	= (List*) malloc (sizeof(List));
	list_initialize(ret);
	return ret;
}
//----------------------------------------------------------------------
	

int stack_init (st_stack * sts) {
	if (sts == NULL) {
		printf ("ERROR: must allocate space for symbol table stack");
		return 1;
	}
	
	// allocate and initialize global scope symbol table
	sts->global_scope = new_symboltable();
	sts->global_scope->s = GLOBAL;
	sts->global_scope->higher_scope = NULL;
	sts->global_scope->lower_scope  = NULL;

	// set global to current scope
	sts->current_scope = sts->global_scope;

	// allocate and initialize paramslist
	sts->current_scope->paramslist = new_list();

	// allocate and initialize declist
	sts->current_scope->declist = new_list();

	// set size to one
	sts->size = 1;
	
	return 0;
}

void stack_destroy (st_stack * sts) {
	symtab * current;
	symtab * to_destroy;
	current = sts->current_scope;

	while (current != NULL) {
		// free table
		htbl_destroy(current->table);
		free (current->table);
		// free paramslist
		list_destroy (current->paramslist);
		free(current->paramslist);
		// free declist
		list_destroy (current->declist);
		free(current->declist);
		// proceed...
		to_destroy = current;
		current = current->higher_scope;
		free(to_destroy);
	}
	sts->current_scope = NULL;
	sts->global_scope  = NULL;
}

symtab * st_enter_scope (st_stack * sts, SCOPE s) {
	symtab * tempst;
	// allocate and initialize new table
	tempst = new_symboltable();
	tempst->paramslist = new_list();
	tempst->declist = new_list();
	tempst->s = s;
	// initialize loop labels
	tempst->endLabel 	= 0;
	tempst->falseLabel	= 0;
	tempst->loopBegLabel	= 0;
	tempst->loopEndLabel	= 0;
	tempst->forIterBeg	= 0;
	tempst->forBodyBeg	= 0;
	// update symboltable stack pointers
	sts->current_scope->lower_scope = tempst;
	tempst->higher_scope = sts->current_scope;
	sts->current_scope = tempst;
	(sts->size)++;
	return sts->current_scope;
}

symtab * st_exit_scope (st_stack * sts) {
	// destroy current hash table
	htbl_destroy (sts->current_scope->table);
	free (sts->current_scope->table);
	// destroy params and declist
	list_destroy(sts->current_scope->paramslist); free(sts->current_scope->paramslist);
	list_destroy(sts->current_scope->declist); free(sts->current_scope->declist);
	// update scope pointers
	sts->current_scope = sts->current_scope->higher_scope;
	free (sts->current_scope->lower_scope);
	sts->current_scope->lower_scope = NULL;
	(sts->size)--;
	return sts->current_scope;
}

node * st_insert_id (st_stack * sts, char * id, KIND k, TYPE t, int offs, List * plist) {
	// takes stack struct instead of hash table
	return insert_id (sts->current_scope->table, id, k, t, offs, plist);
}

// returns 1 (true) if symbol exists
node * lookup (st_stack * sts, char * id) {
	node * ret;
	symtab * current;
	current = sts->current_scope;
	while ( current != NULL ) {
		if ( (ret = t_lookup_id (current->table, id)) != NULL )
			return ret;
		// move up the stack
		current = current->higher_scope;
	}
	// if we fall through symbol wasn't found
	return NULL;
}
