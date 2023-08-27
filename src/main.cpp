/*
Properties to test:
- at most d out neighbours
- at most ceil(log N) partitions
*/

#include <iostream>
#include "graph.h"

using namespace std;

int main()
{
    // graph quick test

    Graph<5> G;
    G.insert(0, 1);
    G.insert(1, 2);
    G.insert(2, 3);
    G.insert(2, 4);

    G.make_partition(1);
    G.colour();
    G.print_edges();
    return 0;
}
