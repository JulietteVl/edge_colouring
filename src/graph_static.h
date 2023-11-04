#ifndef STATIC_GRAPH_H
#define STATIC_GRAPH_H

#include "graph.h"

template <int N>
class StaticGraph : public Graph<N>
{
private:
    list<Edge> edge;
public:
    StaticGraph();
    ~StaticGraph();
    void insert(int u, int v);
    void make_partition(int d);
    void colour();
    list<Edge> get_edges();
    void print_edges();
};

// Definition needed before compilation time as a template is used.

template <int N>
StaticGraph<N>::StaticGraph()
{
}

template <int N>
StaticGraph<N>::~StaticGraph()
{
}

/*
For initialization
Insert the edge uv into the adjacency list.
In the dynamic setting, we will want it to update the data structure.
*/
template <int N>
void StaticGraph<N>::insert(int u, int v)
{
    Edge e;
    e.u = u;
    e.v = v;
    e.colour = -1;
    edge.push_back(e);
    this->adj[u].push_back(make_pair(v, &edge.back()));
    this->adj[v].push_back(make_pair(u, &edge.back()));
    return;
}

// To make the H-partition
template <int N>
void StaticGraph<N>::make_partition(int d)
{
    // Get the active degrees. TODO test this.
    int active_degree[N];
    list<int> index(N);
    iota(index.begin(), index.end(), 0);
    for (int v = 0; v < N; v++)
    {
        active_degree[v] = this->adj[v].size();
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
                for (auto neighbour : this->adj[v])
                {
                    active_degree[neighbour.first]--;
                }
                this->hpartition[i].push_back(v);
                this->level[v] = i;
                inserted.push_back(it);
            }
            it++;
        }
        for (auto it : inserted)
        {
            index.erase(it);
        }
        this->lv_max = ++i;
    }
    return;
}

template <int N>
void StaticGraph<N>::colour()
{
    vector<Edge *> *edge_by_level = new vector<Edge *>[this->lv_max];
    int lv;
    auto it = edge.begin();
    for (Edge e : edge)
    {
        if (this->level[e.u] < this->level[e.v])
        {
            lv = this->level[e.u];
        }
        else
        {
            lv = this->level[e.v];
        }
        edge_by_level[lv].push_back(&(*it));
        it++;
    }
    for (int i = this->lv_max; i--; i >= 0)
    {
        for (auto address : edge_by_level[i])
        {
            Edge &e = *address;
            int c = find_colour(this->palette[e.u], this->palette[e.v], e);
            e.colour = c;
            this->palette[e.u].add(c, &e);
            this->palette[e.v].add(c, &e);
        }
    }
    delete[] edge_by_level;
}

template <int N>
list<Edge> StaticGraph<N>::get_edges()
{
    return edge;
}

template <int N>
void StaticGraph<N>::print_edges()
{
    for (Edge e : edge)
    {
        cout << e.u << " -- " << e.v << " colour " << e.colour << endl;
    }
}

#endif // STATIC_GRAPH_H