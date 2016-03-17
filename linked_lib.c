#include <stdlib.h>
#include <stdio.h>
#include "linked_lib.h"

/** generic functions for linked lists */


void double_add_node_sorted(node **head, node **tail, int data) {
    node *new = new_node(data);
    node *current = *head;
    if (*head == NULL) { *head = *tail = new; return; };
    while (current->next != NULL && current->data < data) { current = current->next; }

    if (current == *head) { /* current is head */
        if (current->data < data) {
            current->next = new;
            *tail = new;
            return;
        } else {
            current->prev = new;
            new->next = current;
            *head = new; // we have a new head!
            return;
        }
    }

    if (current->next == NULL) { /* current is tail */
        current->next = new;
        new->prev = current;
        *tail = new;
        return;
    }

    new->next = current->next;
    new->prev = current;
    current->next = new;
    new->next->prev = new;
}

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
    new->prev = NULL;
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
