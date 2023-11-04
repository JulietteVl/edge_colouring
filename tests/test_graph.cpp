#include <gtest/gtest.h>
#include "../src/graph_static.h"

TEST(PartitionTest, SmallExample)
{
    StaticGraph<5> G;
    G.insert(0, 1);
    G.insert(1, 2);
    G.insert(2, 3);
    G.insert(2, 4);

    G.make_partition(1);

    int s = G.get_partition()[0].size();
    ASSERT_EQ(s, 4);
}

TEST(DifferentColours, SmallExample)
{
    int d = 2;
    const int N = 5;
    StaticGraph<N> G;
    G.insert(0, 1);
    G.insert(1, 2);
    G.insert(2, 3);
    G.insert(2, 4);

    G.make_partition(d);
    G.colour();

    vector<pair<int, Edge *>> *adj = G.get_adjency_list();
    for (int v = 0; v < N; v++)
    {
        int max_colour = adj[v].size() + d - 1;
        int *colour = new int[max_colour];
        fill(colour, colour + max_colour, 0);
        for (auto neighbour : adj[v])
        {
            Edge e = *neighbour.second;
            colour[e.colour]++;
        }
        for (int i = 0; i < max_colour; i++)
        {
            EXPECT_TRUE(colour[i] < 2);
        }
        delete[] colour;
    }
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
