/* Graph implementation. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct GraphNode {
    char *key;
    int value;
    int visited;
    struct Adjacency *adjacency;
} GraphNode;

typedef struct Adjacency {
    struct GraphNode *adjacent_to;
    struct Adjacency *next;
} Adjacency;

GraphNode* new_graph_node(char *key, int value) {
    GraphNode *new = (GraphNode *) malloc(sizeof(GraphNode));
    asprintf(&new->key, "%s", key);
    new->value = value;
    new->adjacency = NULL;
    new->visited = 0;
    return new;
}

int add_to_adjacency(Adjacency **from, GraphNode *to) {
    if (!*from) {
        // add at the beginning
        Adjacency *new = (Adjacency *) malloc(sizeof(Adjacency));
        new->adjacent_to = to;
        new->next = NULL;
        *from = new; // returning the head
    } else {
        Adjacency *current = *from;
        while(current->next) {
            if (current->adjacent_to == to) {
                return 0;
            }
            current = current->next;
        }
        Adjacency *new = (Adjacency *) malloc(sizeof(Adjacency));
        new->adjacent_to = to;
        new->next = NULL;
        current->next = new;
    }
    return 1;
}

int add_edge(GraphNode *from, GraphNode *to) {
    if (!to || !from) { return 0; }

    return (add_to_adjacency(&from->adjacency, to) &&
            add_to_adjacency(&to->adjacency, from));
}

void _print_graph(GraphNode *vertex) {
    if (!vertex || vertex->visited > 0) { return; }

    printf("%s: %d\n", vertex->key, vertex->value);
    vertex->visited = 1;
    Adjacency *current = vertex->adjacency;
    while (current) {
        _print_graph(current->adjacent_to);
        current = current->next;
    }
}

void mark_as_unvisited(GraphNode *vertex) {
    if (!vertex || !vertex->visited) { return; }
    vertex->visited = 0;
    Adjacency *current = vertex->adjacency;
    while (current) {
        mark_as_unvisited(current->adjacent_to);
        current = current->next;
    }
}

void print_graph(GraphNode *vertex) {
    _print_graph(vertex);
    mark_as_unvisited(vertex); // back to normal
}

int main() {
    char *collection[] = {"jones", "theo", "threepio"};
    unsigned long size = sizeof(collection)/sizeof(collection[0]);
    GraphNode **graph = (GraphNode **) malloc(sizeof(GraphNode) * size);
    for (unsigned long i = 0;
         i < size;
         i++) {
        *(graph + i) = new_graph_node(collection[i], i);
    }

    add_edge(graph[0], graph[1]);
    add_edge(graph[0], graph[2]);
    add_edge(graph[1], graph[2]);

    print_graph(graph[0]);
    print_graph(graph[1]);
    print_graph(graph[2]);

    return 0;
}
