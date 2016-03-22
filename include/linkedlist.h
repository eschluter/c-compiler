/* Erik Schluter
 * 3/21/2016
 */
#pragma once
#include <stdlib.h>

typedef enum KIND_  { EXTERN, FUNC, PARAM, VAR, ARRAY, MATRIX } KIND;
typedef enum TYPE_  { INT, STRING, UNKNOWN } TYPE;
typedef enum SCOPE_ { GLOBAL, LOCAL } SCOPE;

struct List;

typedef struct node {
	char * name;
	KIND  k;
	TYPE  t;
	int offset; //for local variables - offset from base pointer
	struct List * plist;
	struct node * next;
} node;

typedef struct List {
	int size;
	node * head;
	node * tail;
} List;

void list_initialize(List * l);

void list_destroy(List * l);

void append_node(List * l, char * id, KIND k, TYPE t, int offs, List * pl);

void remove_node(List * l, node * n);

int compare_symbol (node * n, KIND k, TYPE t, List * pl);
