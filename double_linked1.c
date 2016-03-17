#include "linked_lib.h"

/** Double linked list implementation */

int main() {
    node *head = NULL, *tail = NULL;
    double_add_node_sorted(&head, &tail, 10);
    double_add_node_sorted(&head, &tail, 20);
    double_add_node_sorted(&head, &tail, 30);
    double_add_node_sorted(&head, &tail, 5);
    double_add_node_sorted(&head, &tail, 30);
    print_list(head);
}
