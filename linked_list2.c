#include <stdlib.h>
#include <stdio.h>
#include "linked_lib.h"

/** Different implementation which passes *head as an argument
    that should be modified inside the funcion */

/** Add node to list. This will not return the head, but the argument
    `head` will point to the new head after its completion. */
void add_node_to_list(node **head, int data) {
    node *new = new_node(data);
    if (*head == NULL) { *head = new; return; };

    node *last = tail(*head);
    last->next = new;
}

int main() {
    node *head = NULL;
    add_node_to_list(&head, 10);
    add_node_to_list(&head, 20);
    add_node_to_list(&head, 30);

    print_list(head);
}
