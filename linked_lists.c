#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    struct node *next;
    int data;
} node;

node *tail(node *head) {
    if (head == NULL) {return NULL;};
    while (head->next != NULL) { head = head->next; };
    return head;
}

node *new_node(int data) {
    node *new = (node *) malloc(sizeof(node));
    new->data = data;
    new->next = NULL;
    return new;
}

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

void print_node(node *n) {
    printf("node with value: %d <%p>\n", n->data, n);
}

void print_list(node *head) {
    while (head != NULL) {
        print_node(head);
        head = head->next;
    }
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
    head = add_node_to_start(head, 10);
    head = add_node_to_start(head, 20);
    head = add_node_to_start(head, 30);
    head = add_node_to_end(head, 40);
    head = add_node_to_end(head, 50);
    head = add_node_to_start(head, 60);
    print_list(head);
}
