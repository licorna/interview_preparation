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
    if (!(*root)) {
        *root = new_node(value);
        return;
    }
    Node *last = NULL;
    Node *current = *root;
    while (current) {
        if (current->value == value) {
            return;
        }
        last = current;
        if (current->value < value) {
            current = current->left;
        } else {
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

Node *find_node(Node *tree, int value) {
    if (tree == NULL) {
        return NULL;
    }
    if (tree->value < value) {
        return find_node(tree->left, value);
    } else if (tree->value > value) {
        return find_node(tree->right, value);
    }
    /* if not > nor < then current node is what we are looking for */
    return tree;
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
    for (ulong i = 0; i < sizeof(collection)/sizeof(collection[0]); i++) {
        /* The next code is more concise but will scare away interviewers */
        /*
        ((argc > 1 && !strcmp(argv[1], "-r"))
        ? recursive_add_to_tree : add_to_tree)(&tree, collection[i]); // */
        if (argc > 1 && !strcmp(argv[1], "-r")) {
            recursive_add_to_tree(&tree, collection[i]);
        } else {
            add_to_tree(&tree, collection[i]);
        }
    }
    print_in_order(tree); printf("\n");

    Node *found = find_node(tree, 15);
    if (found) {
        printf("Node has been found! %d\n", found->value);
    } else {
        printf("Node not found\n");
    }
}
