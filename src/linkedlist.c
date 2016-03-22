#include "linkedlist.h"
#include <stdio.h>

void list_initialize (List * l) {
	l->size = 0;
	l->head = NULL;
	l->tail = NULL;
}

void list_destroy (List * l) {
	node * current;
	node * to_destroy;
	
	// check for empty list
	if ( (current = l->head) == NULL )
		return; // nothing to destroy

	// run through list until NULL
	while ( current != NULL ) {
		// check parameters list
		if (current->plist != NULL) {
			list_destroy(current->plist);
			free (current->plist);
		}
		to_destroy = current;
		current = current->next; // can't deallocate without saving pointer to next
		free (to_destroy->name);
		free (to_destroy);
	}
	// reset list fields
	l->size = 0;
	l->head = NULL;
	l->tail = NULL;
}

void append_node (List * l, char * id, KIND k, TYPE t, int offs, List * pl) {
	node * newn;
	// allocate space for new node
	newn = (node*) malloc ( sizeof(node) );
	
	// empty list case
	if ( l->size == 0 ) {
		l->head = newn;
	} else {
		l->tail->next = newn;
	}

	// fill fields and update pointers
	l->tail 	= newn;
	newn->name 	= id;
	newn->k		= k;
	newn->t		= t;
	newn->offset	= offs;
	newn->next 	= NULL;
	newn->plist	= pl;

	// increment list size
	(l->size)++;
}

void remove_node (List * l, node * n) {
	// update list and node pointers
	node * tmp = l->head;
	if ( l->size == 1 ) {
		l->head = NULL;
		l->tail = NULL;
	} else if ( n == l->head ) {
		l->head = n->next;
	} else if ( n == l->tail ) {
		while ( tmp->next != n )
			tmp = tmp->next;
		l->tail = tmp;
		tmp->next = NULL;
	} else {
		while ( tmp->next != n )
			tmp = tmp->next;
		tmp->next = n->next;
	}
	// check that params list is empty
	if ( n->plist != NULL )
		list_destroy (n->plist);
	// free the id name and node memory
	free (n->name);
	free (n);
	// decrement list size
	(l->size)--;
}
	

int compare_symbol (node * n, KIND k, TYPE t, List * pl) {
	if ( n->t != t )
		return 1;

	if ( (pl == NULL) && (n->plist == NULL) ) {
		return 0;	
	} else if ( (pl != NULL && n->plist == NULL) || (pl == NULL && n->plist != NULL) ) {
		return 1;
	}

	node * current1; current1 = n->plist->head;
	node * current2; current2 = pl->head;

	while ( (current1 != NULL) && (current2 != NULL) ) {
		if (current1->t != current2->t)
			return 1;
		current1 = current1->next;
		current2 = current2->next;
	}

	if ( current1 != current2 ) {
		return 1;
	} else {
		return 0;
	}
}
