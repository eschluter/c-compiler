/* Erik Schluter
 * 3/21/2016
 */
#pragma once
#include "linkedlist.h"

typedef struct htbl {
	int buckets;
	int size;
	List * table;
} htbl;

void htbl_initialize (htbl * ht, int buckets);

void htbl_destroy (htbl * ht);

node * insert_id (htbl * ht, char * id, KIND k, TYPE t, int offs, List * plist);

node * lookup_id (List * l, char * id);

// use this for calls from outside source file
// hashing function not available so can't pass a list
node * t_lookup_id (htbl * ht, char *id);

// removes id from hashtable
void remove_from_table (htbl * ht, char * id);
