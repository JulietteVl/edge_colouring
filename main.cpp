/*
Properties to test:
- at most d out neighbours
- at most ceil(log N) partitions
*/

#include <iostream>
#include <numeric> // iota
#include <bits/stdc++.h>

using namespace std;

void insert(int u, int v);
void make_partition(vector<int> *hpartition, vector<int> *adj, int d);

const int N = 5;
vector<int> adj[N];

int main()
{
    insert(0, 1);
    insert(1, 2);
    insert(2, 3);
    insert(2, 4);

    vector<int> hpartition[N];
    make_partition(hpartition, adj, 3);
    return 0;
}

void display(int *first, int *last)
{
    while (first <= last)
    {
        cout << *first++ << " ";
    }
    cout << endl;
    return;
}

// For initialization
void insert(int u, int v)
{
    /*
    Insert the edge uv into the adjacency list.

    In the dynamic setting, we might want it to update the data structure.
    */
    adj[u].push_back(v);
    adj[v].push_back(u);
    return;
}

// To make the H-partition
void make_partition(vector<int> *hpartition, vector<int> *adj, int d)
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
