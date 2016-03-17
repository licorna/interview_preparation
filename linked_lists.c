#include <stdio.h>
#include <stdlib.h>
#include "linked_lib.h"

node *add_node_to_end(node *head, int data) {
    if (head == NULL) { return new_node(data); };
    tail(head)->next = new_node(data);
    return head;
};

node *add_node_to_start(node *head, int data) {
    if (head == NULL) { return new_node(data); };
    node *new_head = new_node(data);
    new_head->next = head;
    return new_head;
}

node *add_node_sorted(node *head, int data) {
    /* 1st case, list is empty */
    if (head == NULL) { return new_node(data); }

    node *current = head;
    node *prev = NULL;
    /* traverse the list until the end or data is greater than current */
    while (current->next != NULL && data > current->data) {
        prev = current;
        current = current->next; }
    node *new = new_node(data);

    /* list only has 1 element */
    if (current == head) {
        if (data < head->data) {
            new->next = head;
            return new;
        }
        new->next = head->next;
        head->next = new;
        return head;
    }
    /* new value is less than first element of the list */
    if (prev == NULL) {
        new->next = head;
        return new;
    }
    /* new value is greater than last element of the list */
    if (current->next == NULL) {
        current->next = new;
        return head;
    }
    /* else */
    new->next = current;
    prev->next = new;
    return head;
}

void recursive_print_list(node *head) {
    print_node(head);
    if (head->next != NULL) {
        recursive_print_list(head->next);
    }
}

void recursive_reverse_print_list(node *head) {
    if (head != NULL) {
        recursive_reverse_print_list(head->next);
        print_node(head);
    }
}

int main() {
    node *head = NULL;
    /* head = add_node_to_start(head, 10); */
    /* head = add_node_to_start(head, 20); */
    /* head = add_node_to_start(head, 30); */
    /* head = add_node_to_end(head, 40); */
    /* head = add_node_to_end(head, 50); */
    /* head = add_node_to_start(head, 60); */

    for (int i = 1; i< 10; i++) {
        head = add_node_sorted(head, i);
    }

    head = add_node_sorted(head, 0);
    head = add_node_sorted(head, 3);
    head = add_node_sorted(head, 2);
    print_list(head);
}
