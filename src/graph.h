#ifndef GRAPH_H
#define GRAPH_H

#include <bits/stdc++.h>
#include <numeric>   // iota
#include "palette.h" // and Edge

using namespace std;

template <int N>
class Graph
{
protected:
    vector<pair<int, Edge *>> adj[N];
    vector<int> hpartition[N];
    Palette<N> palette[N];
    int level[N];
    int lv_max;

public:
    Graph();
    ~Graph();
    virtual void insert(int u, int v) = 0;
    virtual vector<int> *get_partition();
    virtual vector<pair<int, Edge *>> *get_adjency_list();
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
vector<int> *Graph<N>::get_partition()
{
    return hpartition;
}

template <int N>
vector<pair<int, Edge *>> *Graph<N>::get_adjency_list()
{
    return adj;
}


#endif