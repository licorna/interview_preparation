typedef struct LinkedListNode {
    struct LinkedListNode *next;
    int value;
} LinkedListNode;

typedef struct DoubleLinkedListNode {
    struct DoubleLinkedListNode *next;
    struct DoubleLinkedListNode *prev;
    int value;
} DoubleLinkedListNode;

typedef struct BTreeNode {
    struct BTreeNode *left;
    struct BTreeNode *right;
    int value;
} BTreeNode;


LinkedListNode *ll_tail(LinkedListNode *);

LinkedListNode *ll_new_node(int);

void ll_add_node(LinkedListNode **, int);

int bt_count_nodes(BTreeNode *);
int *bt_to_array(BTreeNode *, int *);
void bt_bfs(BTreeNode *, BTreeNode **, int);
void bt_add_to_list(BTreeNode **, int);
void bt_add_to_list_sorted(BTreeNode **, int);
void bt_print_list_in_order(BTreeNode *);
BTreeNode *bt_new_node(int);

void ll_print_list(LinkedListNode *);
