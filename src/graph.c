#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

Node *create_node(size_t idx)
{
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "failed to allocate memory for node\n");
        exit(1);
    }
    new_node->idx = idx;
    new_node->edges = create_dict();
    return new_node;
}

size_t number_of_edges(Node *node)
{
    if (node == NULL) {
        return 0;
    }
    return node->edges->size;
}

Dictionary *create_dict(void)
{
    Dictionary *dict = (Dictionary*)malloc(sizeof(Dictionary));
    if (dict == NULL) {
       fprintf(stderr, "failed to allocate memory for dictionary\n");
       exit(1);
    }
    dict->capacity = 0;
    dict->size = 0;
    dict->entries = NULL;

    return dict;
}

void add_edge(Node* from_node, size_t to_node, size_t weight)
{
    if (from_node->edges->size == from_node->edges->capacity) {
        from_node->edges->capacity =
            (from_node->edges->capacity == 0)
                ? 1
                : from_node->edges->capacity * 2;
        from_node->edges->entries = (Entry**)realloc(
            from_node->edges->entries,
            from_node->edges->capacity * sizeof(Entry*)
        );
    }
    //Create the edge
    Edge *new_edge = (Edge*)malloc(sizeof(Edge));
    if (new_edge == NULL) {
        fprintf(stderr, "failed to allocate memory for new edge\n");
        exit(1);
    }
    new_edge->from_node = from_node->idx;
    new_edge->to_node = to_node;
    new_edge->weight = weight;

    // Create the dict entry
    //TODO: this edge might already exist so need to check
    Entry *new_entry = (Entry*)malloc(sizeof(Entry));
    if (new_entry == NULL) {
        fprintf(stderr, "failed to allocate memory for new entry\n");
        exit(1);
    }
    new_entry->key = to_node;
    new_entry->value = new_edge;

    from_node->edges->entries[from_node->edges->size] = new_entry;
    from_node->edges->size++;
}
