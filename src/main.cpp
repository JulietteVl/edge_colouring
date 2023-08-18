<<<<<<< HEAD
#ifndef GRAPH_H
#define GRAPH_H

#include <bits/stdc++.h>
#include <numeric> // iota

using namespace std;

template <int N>
class Graph
{
private:
    vector<int> adj[N];
    vector<int> hpartition[N];

public:
    // constructor: build an empty graph
    Graph();

    // Copy constructor
    Graph(const Graph &g);

    // Destructor
    ~Graph();

    // Insertion
    void insert(int u, int v);

    // Make Partition
    void make_partition(int d);

    // Get Partition
    vector<int> *get_partition();
};

// Declaration needed before compilation time as a template is used.

template <int N>
Graph<N>::Graph()
{
}

template <int N>
Graph<N>::~Graph()
{
}

template <int N>
Graph<N>::Graph(const Graph &g)
{
    adj = new vector<int>[N];
    for (int i = 0; i < N; i++)
    {
        adj[i] = vector(g < -adj[i]);
    }
}

/*
For initialization
Insert the edge uv into the adjacency list.
In the dynamic setting, we might want it to update the data structure.
*/
template <int N>
void Graph<N>::insert(int u, int v)
{
    adj[u].push_back(v);
    adj[v].push_back(u);
    return;
}

// To make the H-partition
template <int N>
void Graph<N>::make_partition(int d)
{
    // Get the active degrees. TODO test this.
    int active_degree[N];
    list<int> index(N);
    iota(index.begin(), index.end(), 0);
    for (int i = 0; i < N; i++)
    {
        active_degree[i] = adj[i].size();
    }

    //  Recursively create partitions:
    int level = 0;
    while (index.size() > 0)
    {
        auto it = index.begin();
        vector<list<int>::iterator> inserted;
        for (auto v : index)
        {
            // Pick degree less than d, reduce active degree of neighbour, put in partition i.
            if (active_degree[v] <= d)
            {
                for (auto neighbour : adj[v])
                {
                    active_degree[neighbour]--;
                }
                hpartition[level].push_back(v);
                inserted.push_back(it);
            }
            it++;
        }
        for (auto it : inserted)
        {
            index.erase(it);
        }
        level++;
    }
    return;
}

template <int N>
vector<int> *Graph<N>::get_partition()
{
    return hpartition;
}

#endif
=======
/*
Properties to test:
- at most d out neighbours
- at most ceil(log N) partitions
*/

#include <iostream>
#include "graph.h"

using namespace std;

const int N = 5;

int main()
{
    Graph<5> G;
    G.insert(0, 1);
    G.insert(1, 2);
    G.insert(2, 3);
    G.insert(2, 4);

    G.make_partition(1);

    vector<int> *hpartition;
    hpartition = G.get_partition();
    for (auto v : hpartition[0])
    {
        cout << v << " ";
    }
    cout << endl;
    return 0;
}
>>>>>>> main
