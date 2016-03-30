/* Implementation of a BFS using a linked list. */

#include <stdio.h>
#include "prlib.h"


int main() {
    // LinkedListNode *head = NULL;
    BTreeNode *root = NULL;
    int collection[] = { 100, 50, 25, 75, 150, 125, 110, 175};
    for (unsigned long i = 0; i < sizeof(collection)/sizeof(int); i++) {
        bt_add_to_list_sorted(&root, collection[i]);
    }

    bt_print_list_in_order(root); printf("\n");
    bt_bfs(root, NULL, 0);
    return 0;
}
