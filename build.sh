#!/bin/bash

FLAGS=$(cat compile_flags.txt)

mkdir -p build

# Compile graph.c to an object file
gcc $FLAGS -c src/graph.c -o build/graph.o

if [[ $1 == "test" ]]; then
    echo "Compiling and running tests..."

    # Compile test_graph.c and link with graph.o
    gcc $FLAGS -c test/test_graph.c -o build/test_graph.o
    gcc $FLAGS build/graph.o build/test_graph.o -o build/test_graph

    # Run the tests
    ./build/test_graph
else
    # Compile graph.c and create the executable (e.g., build/graph)
    gcc $FLAGS src/graph.c -o build/graph
fi
