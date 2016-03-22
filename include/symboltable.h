/* Erik Schluter
 * 3/21/2016
 */
#pragma once
#include "hashtable.h"

typedef struct symtab {
	htbl * table;
	SCOPE s;
	struct symtab * higher_scope;//previous
	struct symtab * lower_scope;//next
	List * paramslist;//list to hold declaration func parameters
	List * declist;//list to hold declaration queue
	unsigned int endLabel;
	unsigned int falseLabel;
	unsigned int loopBegLabel;
	unsigned int loopEndLabel;
	unsigned int forIterBeg;
	unsigned int forBodyBeg;
} symtab;

typedef struct st_stack {
	int size;
	symtab * global_scope;//head
	symtab * current_scope;//tail
} st_stack;

int stack_init (st_stack * sts);

void stack_destroy (st_stack * sts);

symtab * st_enter_scope (st_stack * sts, SCOPE s);

symtab * st_exit_scope (st_stack * sts);

node * st_insert_id (st_stack * sts, char * id, KIND k, TYPE t, int offs, List * plist);

node * lookup (st_stack * sts, char * id);
