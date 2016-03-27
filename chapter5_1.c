/* Binary Trees */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    struct Node *left;
    struct Node *right;
    int value;
} Node;

Node *new_node(int value) {
    /* Allocates a new node. */
    Node *root = malloc(sizeof(Node));
    if (root) {
        root->left = NULL;
        root->right = NULL;
        root->value = value;
        return root;
    }
    return NULL;
}

void recursive_add_to_tree(Node **root, int value) {
    /* Recursively adds to tree. */
    printf("Using recursive_add_to_tree: %d\n", value);
    if (!*root) {
        /* This is not symetric as it will only affect the root node
           of the "main" tree, not the subtrees */
        *root = new_node(value);
    }
    if ((*root)->value < value) {
        if ((*root)->left == NULL) {
            (*root)->left = new_node(value);
        } else {
            recursive_add_to_tree(&(*root)->left, value);
        }
    } else if ((*root)->value > value) {
        if ((*root)->right == NULL) {
            (*root)->right = new_node(value);
        } else {
            recursive_add_to_tree(&(*root)->right, value);
        }
    }
}

void add_to_tree(Node **root, int value) {
    /* Adds a new node to root tree. */
    printf("Using add_to_tree: %d\n", value);
    if (!(*root)) {
        printf("primer nodo\n");
        *root = new_node(value);
        return;
    }
    Node *last = NULL;
    Node *current = *root;
    while (current) {
        if (current->value == value) {
            printf("es el mismo valor!\n");
            return;
        }
        last = current;
        if (current->value < value) {
            printf("es menor que!\n");
            current = current->left;
        } else {
            printf("es mayor que!\n");
            current = current->right;
        }
    }
    Node *new = new_node(value);
    if (last->value < value) {
        last->left = new;
    } else {
        last->right = new;
    }
}

void print_in_order(Node *root) {
    if (!root) return;
    print_in_order(root->left);
    printf("%d ", root->value);
    print_in_order(root->right);
}

int main(int argc, char *argv[]) {
    Node *tree = NULL;
    int collection[] = {1, 2, 3, 10, 20, 14, 7, 8, 0};
    typedef unsigned long ulong;
    for (ulong i = 0;
         i < sizeof(collection)/sizeof(collection[0]);
         i++) {
        ((argc > 1 && !strcmp(argv[1], "-r")) ? recursive_add_to_tree : add_to_tree)(&tree, collection[i]);
    }
    print_in_order(tree);
}
