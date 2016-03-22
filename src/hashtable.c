#include "hashtable.h"
#include <string.h>

// hasing function from Louden,Mastering Algorithms with C, page 146
unsigned int hash (const char * key) {
	
	unsigned int val = 0;

	while (*key != '\0') {
		unsigned int temp;
		
		val = (val << 4) + (*key);
	
		if (temp = (val & 0xf0000000)) {
			val = val ^ (temp >> 24);
			val = val ^ temp;
		}
		key++;
	}
	return val;
}

void htbl_initialize (htbl * ht, int buckets) {
	
	ht->table = (List*) malloc ( buckets * sizeof(List) );

	for (int i = 0; i < buckets; i++)
		list_initialize (&ht->table[i]);

	ht->buckets 	= buckets;
	ht->size 	= 0;
}

void htbl_destroy (htbl * ht) {

	for (int i = 0; i < ht->buckets; i++)
		list_destroy (&ht->table[i]);

	free (ht->table);
}

node * insert_id (htbl *ht, char * id, KIND k, TYPE t, int offs, List * plist) {

	int index;
	node * n;

	index = hash (id) % ht->buckets;

	if ( (n = lookup_id(&ht->table[index], id)) == NULL ) {
		append_node (&ht->table[index], id, k, t, offs, plist);
		(ht->size)++;
	}
	// else id already exists in the table
	return n;
}

node * lookup_id (List * l, char * id) {

	node * current;

	current = l->head;
	if ( current == NULL )
		return NULL;

	while ( current != NULL ) {
		// check for id match (key is an identifier name string)
		if ( strcmp(id, current->name) == 0 )
			return current;
		current = current->next;
	}
	// if no matches exist in the bucket list return empty
	return NULL;
}

node * t_lookup_id (htbl * ht, char * id) {
	int index;
	index = hash (id) % ht->buckets;

	return lookup_id (&ht->table[index], id);
}

void remove_from_table (htbl * ht, char * id) {
	node * tmp;
	unsigned int index;
	index = hash (id) % ht->buckets;
	// remove node from list
	remove_node ( &ht->table[index], lookup_id(&ht->table[index], id) );
}
