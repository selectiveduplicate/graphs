#include <stddef.h>

typedef struct Edge {
    size_t from_node;
    size_t to_node;
    size_t weight;
} Edge;

typedef struct Entry {
    size_t key;
    Edge *value;
} Entry;

typedef struct Dictionary {
    Entry **entries;
    // capacity indicates how many entries it can hold.
    // it should always be greater than the size.
    // when we see capacity becoming equal to size,
    // we reallocate.
    size_t capacity;
    // size of the dictionary. it points to the next index where to place
    // the next dictionary entry.
    size_t size;
} Dictionary;

typedef struct Node {
    size_t idx;
    Dictionary *edges;
} Node;

Node *create_node(size_t idx);
size_t number_of_edges(Node *node);
void add_edge(Node* from_node, size_t to_node, size_t weight);
void check_dict(Node *node);
Dictionary *create_dict(void);
void create_entry(void);
