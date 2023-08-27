#ifndef PALETTE_H
#define PALETTE_H

#include "tree.h"

using namespace std;

struct Edge
{
    int u;
    int v;
    int colour;
};

/*
D bigger or equal to the degree of the vertex
We currently assume D to be the maximum degree.
*/
template <int D>
class Palette
{
private:
    Edge *edge[2 * D - 1];   // pointer to the edge where the colour is represented
    bool present[2 * D - 1]; // The colour is represented at v
    Tree<2 * D - 1> T;

public:
    Palette();
    ~Palette();
    void add(int c, Edge e);
    void remove(int c);
    int sum(int a, int b);
};

template <int D>
int find_colour(Palette<D> P1, Palette<D> P2, Edge e);

// Definition

template <int D>
Palette<D>::Palette() {}

template <int D>
Palette<D>::~Palette() {}

template <int D>
void Palette<D>::add(int c, Edge e)
{
    edge[c] = &e;
    present[c] = 1;
    T.update(c, 1);
}

template <int D>
void Palette<D>::remove(int c)
{
    edge[c] = NULL;
    present[c] = 0;
    T.update(c, 0);
}

template <int D>
int Palette<D>::sum(int a, int b)
{
    return T.sum(a, b);
}

template <int D>
int find_colour(Palette<D> P1, Palette<D> P2, Edge e)
{
    int l = 0, r = 2 * D - 1;
    while (l < r)
    {
        int z = (l + r + 1) / 2;
        if (P1.sum(l, z) + P2.sum(l, z))
        {
            r = z;
        }
        if (P1.sum(z, r) + P2.sum(z, r))
        {
            l = z;
        }
    }

    e.colour = l;
    P1.add(l, e);
    P2.add(l, e);
    return l;
}

#endif
