/* Elementary methods to work with:

 # linked lists
 # double linked lists
 # binary trees
 # binary search trees

*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "prlib.h"

/** Finds the last, tail node of the list. */
LinkedListNode *ll_tail(LinkedListNode *head) {
    if (head == NULL) { return NULL; };
    while (head->next != NULL) { head = head->next; };
    return head;
}

LinkedListNode *ll_new_node(int value) {
    LinkedListNode *new = (LinkedListNode *) malloc(sizeof(LinkedListNode));
    new->value = value;
    new->next = NULL;
    return new;
}

void ll_add_node(LinkedListNode **head, int value) {
    if (!*head) {
        *head = ll_new_node(value);
        return;
    }
    ll_tail(*head)->next = ll_new_node(value);
}

void ll_print_list(LinkedListNode *head) {
    while (head) {
        printf("%d ", head->value);
        head = head->next;
    }
    printf("\n");
}

void bt_bfs(BTreeNode *head, BTreeNode **children, int child_count) {
    /* Implements Breadth First Search. */
    if (!head) return;
    // place to store all the breadth child
    if (!*children) { // root of tree
        *children = (BTreeNode *) malloc(sizeof(BTreeNode) * 2);
        child_count = 2;
    }
    BTreeNode *new_child = (BTreeNode *) malloc(sizeof(BTreeNode) * child_count * 2);
    for (int i = 0; i < child_count; i += 2) {
        printf("%d ", children[i]->value);
        new_child[i] = *children[i]->left;
        new_child[i] = *children[i]->right;
    }
    bt_bfs(head, &new_child, child_count * 2);
}

void bt_dfs(BTreeNode *head) {
    /* Implements Depth First Search. */
    if (!head) return;
    printf("%d ", head->value);
}

void bt_to_array2(BTreeNode *head, int *arr) {
    static int idx = 0;
    if (!head) { return; }
    *(arr + idx++) = head->value;
    bt_to_array2(head->right, arr);
    bt_to_array2(head->left, arr);
}

int *bt_to_array(BTreeNode *head, int *size) {
    if (!head) {
        return NULL;
    }
    *size = bt_count_nodes(head);
    int *arr = (int *) malloc(sizeof(int) * (*size));
    bt_to_array2(head, arr);
    return arr;
}

int bt_count_nodes(BTreeNode *head) {
    if (!head) {
        return 0;
    }
    return 1 + bt_count_nodes(head->left) +
        bt_count_nodes(head->right);
}

void bt_add_to_list_sorted(BTreeNode **head, int value) {
    if (!*head) {
        *head = bt_new_node(value);
    }
    BTreeNode *current = *head, *prev = NULL;
    while (current) {
        prev = current;
        if (value == current->value) {
            return; // should not add the same value twice
        }
        if (value > current->value) {
            current = current->right;
        } else if (value < current->value) {
            current = current->left;
        }
    }
    if (value > prev->value) {
        prev->right = bt_new_node(value);
    } else if (value < prev->value) {
        prev->left = bt_new_node(value);
    } else {
        return;
    }
}

void bt_print_list_in_order(BTreeNode *root) {
    if (root) {
        bt_print_list_in_order(root->left);
        printf("%d ", root->value);
        bt_print_list_in_order(root->right);
    }
}

BTreeNode *bt_new_node(int value) {
    BTreeNode *new = (BTreeNode *) malloc(sizeof(BTreeNode));
    if (new) {
        new->left = NULL;
        new->right = NULL;
        new->value = value;
        return new;
    }
    return NULL;
}

void swap(int *arr, int i, int j) {
    int tmp = arr[i]; arr[i] = arr[j]; arr[j] = tmp;
}

void quicksort(int *arr, int st, int end) {
    if (st == end) return;

    int i, sep = st;
    for (i = st + 1; i < end; i++) {
        if (arr[i] < arr[st]) swap(arr, ++sep, i);
    }

    swap(arr, st, sep);
    quicksort(arr, st, sep);
    quicksort(arr, sep + 1, end);
}

void arr_print(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", *(arr + i));
    }
    printf("\n");
}
