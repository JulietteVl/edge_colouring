#ifndef STATIC_GRAPH_H
#define STATIC_GRAPH_H

#include"graph.h"

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
    adj[u].push_back(make_pair(v, &edge.back()));
    adj[v].push_back(make_pair(u, &edge.back()));
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
                    active_degree[neighbour.first]--;
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
        lv_max = ++i;
    }
    return;
}

template <int N>
void StaticGraph<N>::colour()
{
    vector<Edge *> *edge_by_level = new vector<Edge *>[lv_max];
    int lv;
    auto it = edge.begin();
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
        edge_by_level[lv].push_back(&(*it));
        it++;
    }
    for (int i = lv_max; i--; i >= 0)
    {
        for (auto address : edge_by_level[i])
        {
            Edge &e = *address;
            int c = find_colour(palette[e.u], palette[e.v], e);
            e.colour = c;
            palette[e.u].add(c, &e);
            palette[e.v].add(c, &e);
        }
    }
    delete[] edge_by_level;
}

template <int N>
void Graph<N>::print_edges()
{
    for (Edge e : edge)
    {
        cout << e.u << " -- " << e.v << " colour " << e.colour << endl;
    }
}

#endif // STATIC_GRAPH_H