#ifndef DYNAMIC_MAX_GRAPH_H
#define DYNAMIC_MAX_GRAPH_H

#include"graph.h"

template <int N>
class DynamicGraph : public Graph<N>
{
private:
    map<pair, Edge> edge;
public:
    DynamicGraph();
    ~DynamicGraph();
    void insert(int u, int v);
    void del(int u, int v);
    vector<int> *get_partition();
    vector<pair<int, Edge *>> *get_adjency_list();
    list<Edge> get_edges();
    void print_edges();
};

// Definition needed before compilation time as a template is used.

template <int N>
DynamicGraph<N>::DynamicGraph()
{
}

template <int N>
DynamicGraph<N>::~DynamicGraph()
{
}

/*
For initialization
Insert the edge uv into the adjacency list.
In the dynamic setting, we will want it to update the data structure.
*/
template <int N>
void DynamicGraph<N>::insert(int u, int v)
{
    Edge e;
    e.u = u;
    e.v = v;
    e.colour = -1;
    edge.push_back(make_pair(u, v), e);
    adj[u].push_back(make_pair(v, &edge.back()));
    adj[v].push_back(make_pair(u, &edge.back()));
    // TODO update the partition
    // TODO recolour the edge
    return;
}

template <int N>
void DynamicGraph<N>::del(int u, int v)
{
    // TODO Delete edge from the adjacency lists of u and v and the list of edges
    // TODO update the H partition
    return;
}


#endif // DYNAMIC_MAX_GRAPH_H