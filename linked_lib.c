#include <stdlib.h>
#include <stdio.h>

/** generic functions for linked lists */

typedef struct node {
    struct node *next;
    int data;
} node;

/** Finds the last, tail node of the list. */
node *tail(node *head) {
    if (head == NULL) { return NULL; };
    while (head->next != NULL) { head = head->next; };
    return head;
}

/** Returns a newly allocated node. */
node *new_node(int data) {
    node *new = (node *) malloc(sizeof(node));
    new->data = data;
    new->next = NULL;
    return new;

}

void print_node(node *n) {
    printf("node with value: %d <%p>\n", n->data, n);
}

void print_list(node *head) {
    while (head != NULL) {
        print_node(head);
        head = head->next;
    }
}
