#include <stdlib.h>
/** generic functions for linked lists */

typedef struct node {
    struct node *next;
    struct node *prev;
    int data;
} node;

/** Add a node sorted to a sorted double linked list. */
void double_add_node_sorted(node **, node **, int);

/** Finds the last, tail node of the list. */
node *tail(node *);

/** Returns a newly allocated node. */
node *new_node(int);

/** Prints one node. */
void print_node(node *);

/** Prints a list of nodes from linked_list. */
void print_list(node *);
