#include <gtest/gtest.h>
#include "../src/graph.h"

TEST(MyTestSuite, MyTestCase)
{
    Graph<5> G;
    G.insert(0, 1);
    G.insert(1, 2);
    G.insert(2, 3);
    G.insert(2, 4);

    G.make_partition(1);

    int s = G.get_partition()[0].size();
    ASSERT_EQ(s, 4);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
