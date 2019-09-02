#include <geo/Tile.hpp>
#include <gtest/gtest.h>
#include <boost/rational.hpp>
#include <cassert>


TEST(tile_test, left_bottom_corner)
{

    EXPECT_TRUE(Tile({0, 0}).contains({0, 0}));
    EXPECT_TRUE(Tile({0, 0}).contains({1, 1}));
    EXPECT_TRUE(Tile({0, 0}).contains({0, 1}));
    EXPECT_TRUE(Tile({0, 0}).contains({1, 0}));

    EXPECT_TRUE(Tile({1, 0}).contains({1, 1}));
    EXPECT_TRUE(Tile({0, 1}).contains({1, 1}));
    EXPECT_TRUE(Tile({1, 1}).contains({1, 1}));

    EXPECT_TRUE(Tile({0, 1}).contains({0, 1}));

    EXPECT_TRUE(Tile({1, 0}).contains({1, 0}));
}

TEST(tile_test, partial_rational_coordinates)
{
    using rt = boost::rational<int>;
    EXPECT_TRUE(Tile({0, 0}).contains({rt(1)/2, 1}));
    EXPECT_TRUE(Tile({0, 0}).contains({1, rt(1)/2}));
    EXPECT_TRUE(Tile({0, 0}).contains({rt(1)/2, 0}));
    EXPECT_TRUE(Tile({0, 0}).contains({0, rt(1)/2}));

    EXPECT_TRUE(Tile({0, 0}).contains({rt(1)/2, 1}));
    EXPECT_TRUE(Tile({0, 0}).contains({1, rt(1)/2}));
    EXPECT_TRUE(Tile({0, 0}).contains({rt(1)/2, 0}));
    EXPECT_TRUE(Tile({0, 0}).contains({0, rt(1)/2}));
}

TEST(tile_test, rational_coordinates)
{
    using rt = boost::rational<int>;
    EXPECT_TRUE(Tile({0, 0}).contains({rt(1)/2, rt(1)/2}));

    EXPECT_TRUE(Tile({0, 0}).contains({rt(1)/42, rt(1)/42}));
    EXPECT_TRUE(Tile({0, 0}).contains({rt(1)/42, rt(41)/42}));
    EXPECT_TRUE(Tile({0, 0}).contains({rt(41)/42, rt(1)/42}));
    EXPECT_TRUE(Tile({0, 0}).contains({rt(41)/42, rt(41)/42}));
}
