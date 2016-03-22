/* Erik Schluter
 * 3/21/2016
 */
#include "istack.h"

void istack_init (istack * st) {
	st->base 	= NULL;
	st->current 	= NULL;
	st->size 	= 0;
}

void istack_destroy (istack * st) {
	inode * current;
	inode * to_destroy;
	current = st->current;
	// start at top and move down
	while (current != NULL) {
		// free id node
		/*if (current->id != NULL) {
			free (current->id);
			current->id = NULL;
		}*/
		to_destroy = current;
		current = current->prev;
		free (to_destroy);
	}
	st->current 	= NULL;
	st->base	= NULL;
	st->size	= 0;
}

void ipush (istack * st, char * id, TYPE t, int val, int baseoff, MEMTYPE m) {
	inode * new;
	new = (inode*) malloc (sizeof(inode));
	// set node pointer
	new->prev = st->current;
	// update istack pointer
	st->current = new;
	// handle empty stack
	if (st->size == 0) {
		st->base = new;
	} else {
		new->prev->up = new;
	}
	// fill node fields
	new->id 	= id;
	new->val 	= val;
	new->memt 	= m;
	new->up 	= NULL;
	new->offset 	= baseoff;
	new->t 		= t;
	// update size
	(st->size)++;
}

inode * ipop (istack * st) {
	inode * ret;
	// take top of stack
	ret = st->current;
	// update pointers
	if ( (st->current = ret->prev) == NULL )
		st->base = NULL; // stack size = 0
	// decrement size
	(st->size)--;
	return ret;
}

void inode_destroy (inode * n) {
	if (n->id != NULL)
		free(n->id);
	free (n);
}
