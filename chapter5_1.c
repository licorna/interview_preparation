/* Binary Trees */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct Node {
    struct Node *left;
    struct Node *right;
    int value;
} Node;

Node *new_node(int value) {
    /* Allocates a new node. */
    Node *root = malloc(sizeof(Node));
    if (root) {
        /* Left contains values lower than current,
           right contains values greater than current */
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
        if ((*root)->right == NULL) {
            (*root)->right = new_node(value);
        } else {
            recursive_add_to_tree(&(*root)->right, value);
        }
    } else if ((*root)->value > value) {
        if ((*root)->left == NULL) {
            (*root)->left = new_node(value);
        } else {
            recursive_add_to_tree(&(*root)->left, value);
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
            current = current->right;
        } else {
            current = current->left;
        }
    }
    Node *new = new_node(value);
    if (last->value < value) {
        last->right = new;
    } else {
        last->left = new;
    }
}

Node *find_node(Node *tree, int value) {
    if (tree == NULL) {
        return NULL;
    }
    if (tree->value < value) {
        return find_node(tree->right, value);
    } else if (tree->value > value) {
        return find_node(tree->left, value);
    }
    /* if not > nor < then current node is what we are looking for */
    return tree;
}

Node *lowest_common_ancestor(Node *tree, int v1, int v2) {
    if (find_node(tree->left, v1) && find_node(tree->left, v2)) {
        return lowest_common_ancestor(tree->left, v1, v2);
    } else if (find_node(tree->right, v1) && find_node(tree->right, v2)) {
        return lowest_common_ancestor(tree->right, v1, v2);
    }
    return tree;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(Node *tree) {
    if (!tree) return 0;
    return 1 + max(height(tree->left), height(tree->right));
}

void print_in_order(Node *root, int show_pointer) {
    if (!root) return;
    print_in_order(root->left, show_pointer);
    printf("%d ", root->value);
    if (show_pointer) { printf("%p\n", root); }
    print_in_order(root->right, show_pointer);
}

void print_post_order(Node *root) {
    if (!root) return;
    print_post_order(root->left);
    print_post_order(root->right);
    printf("%d ", root->value);
}

int main(int argc, char *argv[]) {
    Node *tree = NULL;
    int collection[] = { 100, 50, 25, 75, 150, 125, 110, 175};
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
    printf("Post Order: ");
    print_post_order(tree); printf ("\n");

    printf("In Order: ");
    print_in_order(tree, 0); printf ("\n");

    printf("Lowest Common Ancestor: ");
    Node *lca = lowest_common_ancestor(tree, 110, 20);
    printf("%d\n", lca->value);
}
