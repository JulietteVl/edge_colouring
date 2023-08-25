#ifndef GRAPH_H
#define GRAPH_H

#include <bits/stdc++.h>
#include <numeric>   // iota
#include "palette.h" // and Edge

using namespace std;

template <int N>
class Graph
{
private:
    list<Edge> edge;
    vector<int> adj[N];
    vector<int> hpartition[N];
    Palette<N> palette;
    int level[N];
    int lv_max;

public:
    Graph();
    Graph(const Graph &g);
    ~Graph();
    void insert(int u, int v);
    void make_partition(int d);
    vector<int> *get_partition();
    void colour();
};

// Definition needed before compilation time as a template is used.

template <int N>
Graph<N>::Graph()
{
}

template <int N>
Graph<N>::~Graph()
{
}

template <int N>
Graph<N>::Graph(const Graph<N> &g)
{
    adj = new vector<int>[N];
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            adj[i].pushback(g.adj[i][j]);
        }
    }
}

/*
For initialization
Insert the edge uv into the adjacency list.
In the dynamic setting, we will want it to update the data structure.
*/
template <int N>
void Graph<N>::insert(int u, int v)
{
    Edge e;
    e.u = u;
    e.v = v;
    e.colour = -1;
    edge.push_back(e);
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
    for (int v = 0; v < N; v++)
    {
        active_degree[v] = adj[v].size();
    }

    //  Recursively create partitions:
    int i = 0;
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
                hpartition[i].push_back(v);
                level[v] = i;
                inserted.push_back(it);
            }
            it++;
        }
        for (auto it : inserted)
        {
            index.erase(it);
        }
        lv_max = i;
        i++;
    }
    return;
}

template <int N>
vector<int> *Graph<N>::get_partition()
{
    return hpartition;
}

template <int N>
void Graph<N>::colour()
{
    vector<Edge> *edge_by_level = new vector<Edge>[lv_max];
    int lv;
    for (Edge e : edge)
    {
        if (level[e.u] < level[e.v])
        {
            lv = level[e.u];
        }
        else
        {
            lv = level[e.v];
        }
        edge_by_level[lv].push_back(e);
    }
    for (int i = lv_max; i--; i >= 0)
    {
        for (Edge e : edge_by_level[i])
        {
            e.colour = find_colour(palette[e.u], palette[e.v], e);
        }
    }
    delete[] edge_by_level;
}

#endif
