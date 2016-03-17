#include <stdlib.h>
/** generic functions for linked lists */

typedef struct node {
    struct node *next;
    int data;
} node;

/** Finds the last, tail node of the list. */
node *tail(node *);

/** Returns a newly allocated node. */
node *new_node(int);

/** Prints one node. */
void print_node(node *);

/** Prints a list of nodes from linked_list. */
void print_list(node *);
