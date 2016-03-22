/* instruction stack */
#include <stdlib.h>
#include "linkedlist.h"

typedef enum memorytype { IMMEDIATE, REFERENCE, RESULT } MEMTYPE;

typedef struct inode {
	struct inode * prev;
	struct inode * up; // -> I dub thee the doubly-linked stack
	MEMTYPE memt;
	TYPE t;
	int val;
	char * id;
	int offset;
} inode;

typedef struct istack {
	inode * base;
	inode * current;
	unsigned int size;
} istack;

// instructions
void istack_init (istack * st);
void istack_destroy (istack * st);
void inode_destroy (inode * n);
void ipush (istack * st, char * id, TYPE t, int val, int offset, MEMTYPE m);
inode * ipop (istack * st);
