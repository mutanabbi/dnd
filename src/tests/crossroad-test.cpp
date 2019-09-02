#include <geo/Crossroad.hpp>
#include <geo/Section.hpp>
#include <gtest/gtest.h>
#include <vector>
//#include <iostream>
#include <cassert>

namespace {

/*
auto prnt_trajectory(const std::vector<Coordinate>& vec)
{
    std::cout << "[";
    for (const auto& c : vec)
        std::cout << c << " | ";
    (std::cout << "]\n").flush();
};
*/

}                                                           // anonymous namespace

class crossroad_test : public ::testing::Test
{
protected:
    void SetUp() override
    {
        /*    +_____+
         *   5|###  |
         *   4| t   |
         *   3| #  #|
         *   2| #  #|
         *   1| f   |
         *   0|     |
         *    +-----+
         *     01234
         */
        ASSERT_FALSE(is_tile_occupied({1, 1}));
        ASSERT_TRUE (is_tile_occupied({1, 2}));
        ASSERT_TRUE (is_tile_occupied({1, 3}));
        ASSERT_FALSE(is_tile_occupied({1, 4}));
    }

    // void TearDown() override {}

    using pt = Coordinate;
    using tl = Tile;
    using vec = std::vector<Crossroad>;
    using rt = boost::rational<int>;

    Crossroad from{Coordinate{1, 1}, Tile{1, 1}};
    Tile tt{1, 4};
};


TEST_F(crossroad_test, to_south_west_corner)
{
    auto to = Crossroad{Coordinate{1, 4}, tt};
    auto sec = Section{from, to};
    auto sample = vec{
        {pt{1, 1}, tl{1, 1}}
      , {pt{1, 2}, tl{1, 1}}
      , {pt{1, 2}, tl{1, 2}}
      , {pt{1, 3}, tl{1, 2}}
      , {pt{1, 3}, tl{1, 3}}
      , {pt{1, 4}, tl{1, 3}}
      , {pt{1, 4}, tl{1, 4}}
    };
    EXPECT_EQ(sec.get_trajectory(), sample);
    //assert(true == sec.is_reachable());
}

TEST_F(crossroad_test, to_south_east_corner)
{
    auto to = Crossroad{Coordinate{2, 4}, tt};
    auto sec = Section{from, to};
    auto sample = vec{
        {pt{1, 1}, tl{1, 1}}
      , {pt{rt(4)/3, 2}, tl{1, 1}}
      , {pt{rt(4)/3, 2}, tl{1, 2}}
      , {pt{rt(5)/3, 3}, tl{1, 2}}
      , {pt{rt(5)/3, 3}, tl{1, 3}}
      , {pt{2, 4}, tl{1, 3}}
      , {pt{2, 4}, tl{1, 4}}
    };
    EXPECT_EQ(sec.get_trajectory(), sample);
    //assert(false == sec.is_reachable());
}

TEST_F(crossroad_test, to_north_east_corner)
{
    auto to = Crossroad{Coordinate{2, 5}, tt};
    auto sec = Section{from, to};
    auto sample = vec{
        {pt{1, 1}, tl{1, 1}}
      , {pt{rt(5)/4, 2}, tl{1, 1}}
      , {pt{rt(5)/4, 2}, tl{1, 2}}
      , {pt{rt(3)/2, 3}, tl{1, 2}}
      , {pt{rt(3)/2, 3}, tl{1, 3}}
      , {pt{rt(7)/4, 4}, tl{1, 3}}
      , {pt{rt(7)/4, 4}, tl{1, 4}}
      , {pt{2, 5}, tl{1, 4}}
    };
    //prnt_trajectory(sec.get_trajectory());
    EXPECT_EQ(sec.get_trajectory(), sample);
    //assert(false == sec.is_reachable());
}
