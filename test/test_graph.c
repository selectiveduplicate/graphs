#include "../src/graph.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

void test_create_node()
{
    Node *node = create_node(10);
    if (node == NULL) {
        fprintf(stderr, "failed to create test node\n");
        exit(1);
    }
    assert(node->idx == 10);
    assert(node->edges->capacity == 0);
    assert(node->edges->size == 0);
}

void test_number_of_edges()
{
    Node *node = create_node(10);
    assert(node != NULL);
    size_t edges_count = number_of_edges(node);
}

void test_add_edge()
{
    Node *node_10 = create_node(10);
    Node *node_20 = create_node(20);
    add_edge(node_10, 20, 2024);

    assert(node_10->edges->size == 1);
    assert(node_10->edges->capacity == 1);
    assert(node_10->edges->entries[0]->key == 20);
    assert(node_10->edges->entries[0]->value->weight == 2024);
}

int main(void)
{
    test_create_node();
    test_number_of_edges();
    test_add_edge();

    return EXIT_SUCCESS;
}
