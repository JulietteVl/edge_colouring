#include <iostream>
#include <fstream>
#include <gtest/gtest.h>
#include "../src/tree.h"

using namespace std;

TEST(SumQueries, FromFile)
{
    ifstream input;
    input.open("in_out/range_sum/input_2.txt");

    ifstream output;
    output.open("in_out/range_sum/output_2.txt");

    ofstream test;
    test.open("in_out/range_sum/test_2.txt");

    int q, a, b, k, t;
    ll u, o;
    input >> q;

    const int n = 200000;
    Tree<n> T;

    for (int k = 1; k <= n; k++)
    {
        input >> u;
        T.update(k, u);
    }

    for (int j = 0; j < q; j++)
    {
        input >> t;
        if (t == 1)
        {
            input >> k >> u;
            T.update(k, u);
        }
        else
        {
            input >> a >> b;
            output >> o;
            ASSERT_EQ(T.sum(a, b), o);
        }
    }
    input.close();
    output.close();
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
