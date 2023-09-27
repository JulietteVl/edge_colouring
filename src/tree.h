// Semi dynamic tree. Subject to insertion/deletion at the left and updates.

#ifndef TREE_H
#define TREE_H

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

class Tree
{
private:
    vector<int> leaves;

public:
    Tree();
    ~Tree();
    void update(int k, ll x);
    ll sum(int a, int b);
};

Tree::Tree()
{
}

Tree::~Tree()
{
}

void Tree::update(int k, ll x)
{
    // k += n - 1;
    // tree[k] = x;
    // for (k /= 2; k >= 1; k /= 2)
    // {
    //     tree[k] = tree[2 * k] + tree[2 * k + 1];
    // }
}

// Elements at position a and b are included

ll Tree::sum(int a, int b)
{
    // a += n - 1;
    // b += n - 1;
    // ll s = 0;
    // while (a <= b)
    // {
    //     if (a % 2 == 1)
    //         s += tree[a++];
    //     if (b % 2 == 0)
    //         s += tree[b--];
    //     a /= 2;
    //     b /= 2;
    // }
    // return s;
}

#endif // TREE_H
