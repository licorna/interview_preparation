#include <stdio.h>
#include <stdlib.h>
#include "prlib.h"

int main() {
    BTreeNode *root = NULL;
    int collection[] = { 10, 20, 40, 30, 100, 110, 90, 35 };
    for (unsigned long i = 0;
         i < sizeof(collection)/sizeof(collection[0]);
         i++) {
        bt_add_to_list_sorted(&root, collection[i]);
    }
    // bt_print_list_in_order(root);

    int size = 0;

    // now we will put the tree into the array
    int *array = bt_to_array(root, &size);

    // print its contents to check everything is working
    for (int i = 0; i < size; i++) {
        printf("%d ", *(array + i));
    }
    printf("\n");

    quicksort(array, 0, size);

    arr_print(array, size);
}
