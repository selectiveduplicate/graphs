#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>

typedef size_t usize;
typedef float f32;



typedef struct Edge {
    usize from_node;
    usize to_node;
    f32 weight;
} Edge;

typedef struct Entry {
    usize key;
    Edge *value;
} Entry;

typedef struct Dictionary {
    Entry **entries;
    // capacity indicates how many entries it can hold.
    // it should always be greater than the size.
    // when we see capacity becoming equal to size,
    // we reallocate.
    usize capacity;
    // size of the dictionary. it points to the next index where to place
    // the next dictionary entry.
    usize size;
} Dictionary;

typedef struct Node {
    usize idx;
    Dictionary *edges;
} Node;

typedef struct Graph {
    usize num_nodes;
    bool undirected;
    Node **nodes;
} Graph;

typedef enum ErrorType {
    GraphIndexOutOfBound,
    NodeNotFound,
    EdgeNotFound,
    None,
} ErrorType;

typedef struct InsertEdgeResult {
    ErrorType error_type;
    Edge *value;
} InsertEdgeResult;


typedef struct GetEdgeResult {
    ErrorType error_type;
    Edge *value;
} GetEdgeResult;

Node *create_node(usize idx);
usize number_of_edges(Node *node);
Edge *add_edge(Node* from_node, usize to_node, f32 weight);
Dictionary *create_dict(void);
Edge *get_edge(Node *from_node, usize to_node);
void remove_edge(Node *from_node, usize to_node);
Graph *create_graph(usize num_nodes, bool undirected);
InsertEdgeResult insert_edge(Graph *graph, usize from, usize to, f32 weight);
GetEdgeResult g_get_edge(Graph *graph, usize from, usize to);

#endif // !GRAPH_H
