#include <stdio.h>
#include <stdlib.h>

/* Will look for the m-th to last element of list. */

typedef struct Node {
    struct Node *next;
    int value;
} Node;

Node *new_node(int value) {
    Node *new = malloc(sizeof(Node));
    if (new) {
        new->next = NULL;
        new->value = value;
        return new;
    }
    return NULL;
}

void append_to_list(Node **head, int value) {
    /* Append at the end of the list. */
    if (!*head) {
        *head = new_node(value);
        return;
    }
    Node *current = *head;
    while (current->next) current = current->next;
    current->next = new_node(value);
}

Node *mth_to_last(Node *head, int mth) {
    /* Find the mth to last element. */
    Node *tmp = head;
    while (head) {
        if (!mth) tmp = tmp->next;
        else --mth;
        head = head->next;
    }
    return tmp;
}

/** Finds the last, tail node of the list. */
Node *tail(Node *head) {
    if (head == NULL) { return NULL; };
    while (head->next != NULL) { head = head->next; };
    return head;
}


int is_cyclic(Node *head) {
    /* Will check if list is cyclic. */
    if (!head) { return 0; }
    Node *tmp = head;
    int i = 0;
    while (head && tmp) {
        if (++i % 2 == 0) tmp = tmp->next;
        head = head->next;
        if (head == tmp) { return 0; }
    }
    return 1;
}

void print_list(Node *head) {
    Node *current = head;
    while (current) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}

int main() {
    int collection[] = { 100, 50, 25, 75, 150, 125, 110, 175};
    Node *head = NULL;
    for (unsigned long i = 0; i < sizeof(collection)/sizeof(collection[0]); i++) {
        append_to_list(&head, collection[i]);
    }
    //print_list(head);

    print_list(mth_to_last(head, 4));
    Node *mth4 = mth_to_last(head, 4);
    tail(head)->next = mth4;
    printf("%s\n", (is_cyclic(head)? "is_cyclic": "not cyclic"));

    return 0;
}
