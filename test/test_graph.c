#include "../src/graph.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


/*
 * Cleanup functions for tests
 *
 */
void free_dict(Dictionary *edges)
{
    if (edges == nullptr) {
        return;
    }

    for (usize i = 0; i < edges->size; i++) {
        // Free the edge.
        free(edges->entries[i]->value);
        // Free the Entry object
        free(edges->entries[i]);
    }
    // Free the entries array
    free(edges->entries);
    // free the dictionary
    free(edges);
}

void free_node(Node *node)
{
    if (node == nullptr) {
        return;
    }
    
    free_dict(node->edges);
    free(node);
}

void free_graph(Graph *graph)
{
    if (graph == nullptr) return;

    for (size_t i = 0; i < graph->num_nodes; i++) {
        free_node(graph->nodes[i]);
    }
    free(graph->nodes);
    free(graph);
}

/*
 * Tests
 */
void test_create_node()
{
    Node *node = create_node(10);
    if (node == nullptr) {
        fprintf(stderr, "failed to create test node\n");
        exit(1);
    }
    assert(node->idx == 10);
    assert(node->edges->capacity == 0);
    assert(node->edges->size == 0);

    free_node(node);
}

void test_number_of_edges()
{
    Node *node = create_node(10);
    assert(node != nullptr);

    usize edges_count = number_of_edges(node);
    assert(edges_count == 0);

    free_node(node);
}

void test_add_edge()
{
    Node *node_10 = create_node(10);
    Node *node_20 = create_node(20);
    Node *node_80 = create_node(80);

    add_edge(node_10, 20, 2024);
    add_edge(node_10, 80, 948);

    assert(node_10->edges->size == 2);
    assert(node_10->edges->capacity == 2);

    assert(node_10->edges->entries[0]->key == 20);
    assert(node_10->edges->entries[0]->value->weight == 2024);
  
    // Free all memory

    free_node(node_10);
    free_node(node_20);
    free_node(node_80);
}

void test_get_edge()
{
    Node *node_10 = create_node(10);
    Node *node_20 = create_node(20);
    Node *node_80 = create_node(80);
    Node *node_25 = create_node(25);

    add_edge(node_10, 20, 2024);
    add_edge(node_10, 80, 948);
    add_edge(node_25, 20, 1990);

    // Returns nullptr if the edge doesn't exist
    // Should return a valid edge;
    Edge *edge = get_edge(node_25, 20);
    assert(edge != nullptr);
    assert(edge->from_node == 25);
    assert(edge->to_node == 20);
    assert(edge->weight == 1990);
    
    // Should return nullptr
    assert(get_edge(node_80, 10) == nullptr);

    free_node(node_10);
    free_node(node_20);
    free_node(node_80);
    free_node(node_25);
}

void test_remove_edge()
{
    Node *node_10 = create_node(10);
    Node *node_20 = create_node(20);
    Node *node_80 = create_node(80);
    Node *node_25 = create_node(25);
    Node *node_85 = create_node(85);


    add_edge(node_10, 20, 2024);
    add_edge(node_10, 80, 948);
    add_edge(node_25, 20, 1990);
    add_edge(node_10, 85, 90234);

    // Node 10 should have three neighbors.
    assert(node_10->edges->size == 3);

    remove_edge(node_10, 80);

    // Now it should have two neighbors.
    assert(node_10->edges->size == 2);

    // The remaining neighbors are nodes 20 and 85.
    Entry *first = node_10->edges->entries[0];
    Entry *second = node_10->edges->entries[1];

    assert(first->key == 20);
    assert(second->key == 85);

    free_node(node_10);
    free_node(node_20);
    free_node(node_80);
    free_node(node_25);
    free_node(node_85);
}

void test_creating_graph()
{
    Graph *graph = create_graph(5, true);

    assert(graph->num_nodes == 5);
    assert(graph->undirected == true);

    assert(graph->nodes[0]->idx == 0);
    assert(graph->nodes[0]->edges->entries == nullptr);
    assert(graph->nodes[0]->edges->size == 0);

    free_graph(graph);
}


int main(void)
{
    test_create_node();
    test_number_of_edges();
    test_add_edge();
    test_get_edge();
    test_remove_edge();
    test_creating_graph();

    return EXIT_SUCCESS;
}
