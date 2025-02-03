#include <stdio.h>
#include "graph.h"

Node *create_node(usize idx)
{
    Node *new_node = (Node*)malloc(sizeof(Node));
    if (new_node == nullptr) {
        fprintf(stderr, "failed to allocate memory for node\n");
        exit(1);
    }
    new_node->idx = idx;
    new_node->edges = create_dict();
    return new_node;
}

usize number_of_edges(Node *node)
{
    if (node == nullptr) {
        return 0;
    }
    return node->edges->size;
}

Dictionary *create_dict(void)
{
    Dictionary *dict = (Dictionary*)malloc(sizeof(Dictionary));
    if (dict == nullptr) {
       fprintf(stderr, "failed to allocate memory for dictionary\n");
       exit(1);
    }
    dict->capacity = 0;
    dict->size = 0;
    dict->entries = nullptr;

    return dict;
}

void add_edge(Node* from_node, usize to_node, usize weight)
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
    if (new_edge == nullptr) {
        fprintf(stderr, "failed to allocate memory for new edge\n");
        exit(1);
    }
    new_edge->from_node = from_node->idx;
    new_edge->to_node = to_node;
    new_edge->weight = weight;

    // Create the dict entry
    //TODO: this edge might already exist so need to check
    Entry *new_entry = (Entry*)malloc(sizeof(Entry));
    if (new_entry == nullptr) {
        fprintf(stderr, "failed to allocate memory for new entry\n");
        exit(1);
    }
    new_entry->key = to_node;
    new_entry->value = new_edge;

    from_node->edges->entries[from_node->edges->size] = new_entry;
    from_node->edges->size++;
}

/* 
 *
* Returns the edge object if edge exists between two nodes. Otherwise, 
* returns nullptr.
* */
Edge *get_edge(Node *from_node, usize to_node)
{
    Dictionary *edges = from_node->edges;
    
    for (usize i = 0; i < edges->size; i++) {
       if (edges->entries[i]->key == to_node) {
           return edges->entries[i]->value;
       } 
    }
    return nullptr;
}

void remove_edge(Node *from_node, usize to_node)
{
    Dictionary *edges = from_node->edges;
    
    for (usize i = 0; i < edges->size; i++) {
        if (edges->entries[i]->key == to_node) {
            //free the edge. 
            free(edges->entries[i]->value);
            //free the entry
            free(edges->entries[i]);
            
            for (usize j = i; j < edges->size - 1; j++) {
                edges->entries[j] = edges->entries[j+1];
            }
            edges->size--;
        }
    }
}

Graph *create_graph(usize num_nodes, bool undirected)
{
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    if (graph == nullptr) {
        fprintf(stderr, "failed to allocate memory for new graph\n");
        exit(1);
    }

    graph->nodes = (Node **)malloc(sizeof(Node) * num_nodes);
    if (graph->nodes == nullptr) {
        fprintf(stderr, "failed to allocate memory for nodes list in graph\n");
        exit(1);
    }

    for (size_t i = 0; i < num_nodes; i++) {
        Node *node = create_node(i);
        if (node == nullptr) {
            fprintf(stderr, "failed to create node\n");
            exit(1);
        }
        graph->nodes[i] = node;
    }
    graph->undirected = undirected;
    graph->num_nodes = num_nodes;
    return graph;

}