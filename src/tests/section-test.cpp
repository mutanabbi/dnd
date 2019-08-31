#include <geo/Section.hpp>
#include <geo/Coordinate.hpp>
#include <gtest/gtest.h>
//#include <iostream> // TODO: DEBUG ONLY


namespace {

auto reach(const Crossroad& from, const Crossroad& to)
{
    // TODO: DEBUG ONLY
    /*
    auto prnt_trajectory = [](const auto& vec) {
        std::cout << "[";
        for (const auto& c : vec)
            std::cout << c << " | ";
        (std::cout << "]\n").flush();
    };
    */
    auto sec = Section(from, to);
    //prnt_trajectory(get_trajectory(sec.from().point, sec.to().point, sec.line()));
    //prnt_trajectory(sec.get_trajectory());
    return sec.is_reachable();
};

}                                                           // anonymous namespace


class section_test : public ::testing::Test
{
protected:

    void SetUp() override
    {
        ASSERT_TRUE (is_tile_occupied({14, 2}));
        ASSERT_FALSE(is_tile_occupied({0, 1}));
        ASSERT_FALSE(is_tile_occupied({0, 2}));
        ASSERT_FALSE(is_tile_occupied({0, 3}));
        ASSERT_FALSE(is_tile_occupied({0, 4}));
        ASSERT_TRUE (is_tile_occupied({0, 5}));

        ASSERT_TRUE (is_tile_occupied({1, 2}));
        ASSERT_TRUE (is_tile_occupied({1, 3}));
        ASSERT_FALSE(is_tile_occupied({1, 4}));
        ASSERT_TRUE (is_tile_occupied({1, 5}));

        ASSERT_FALSE(is_tile_occupied({2, 1}));
        ASSERT_FALSE(is_tile_occupied({2, 2}));
        ASSERT_FALSE(is_tile_occupied({2, 3}));
        ASSERT_FALSE(is_tile_occupied({2, 4}));
        ASSERT_TRUE (is_tile_occupied({2, 5}));
    }

    // void TearDown() override {}
};


// across
//   1. bottom right to top left
TEST_F(section_test, across_bottom_right_to_top_left)
{
    EXPECT_TRUE (reach({{16, 1}, {15, 1}}, {{15, 2}, {15, 1}}));
    EXPECT_FALSE(reach({{16, 1}, {15, 1}}, {{14, 3}, {14, 2}}));
    EXPECT_FALSE(reach({{16, 1}, {15, 1}}, {{13, 4}, {13, 3}}));
}

//   2. bottom left to top right
TEST_F(section_test, across_bottom_left_to_top_right)
{
    EXPECT_TRUE (reach({{13, 1}, {13, 1}}, {{14, 2}, {13, 1}}));
    EXPECT_FALSE(reach({{13, 1}, {13, 1}}, {{15, 3}, {14, 2}}));
    EXPECT_FALSE(reach({{13, 1}, {13, 1}}, {{16, 4}, {15, 3}}));
}

//   3. top left to bottom right
TEST_F(section_test, across_top_left_to_bottom_right)
{
    EXPECT_TRUE (reach({{13, 4}, {13, 3}}, {{14, 3}, {13, 3}}));
    EXPECT_FALSE(reach({{13, 4}, {13, 3}}, {{15, 2}, {14, 2}}));
    EXPECT_FALSE(reach({{13, 4}, {13, 3}}, {{16, 1}, {15, 1}}));
}

//   4. top right to bottom left
TEST_F(section_test, across_top_right_to_bottom_left)
{
    EXPECT_TRUE (reach({{16, 4}, {16, 3}}, {{15, 3}, {15, 3}}));
    EXPECT_FALSE(reach({{16, 4}, {16, 3}}, {{14, 2}, {14, 2}}));
    EXPECT_FALSE(reach({{16, 4}, {16, 3}}, {{13, 1}, {13, 1}}));
}

// along
//   5. bottom right to top left
TEST_F(section_test, along_bottom_right_to_top_left)
{
    EXPECT_TRUE (reach({{16, 2}, {15, 2}}, {{15, 3}, {15, 2}}));
    EXPECT_TRUE (reach({{15, 3}, {15, 2}}, {{14, 4}, {14, 3}}));
    EXPECT_TRUE (reach({{16, 2}, {15, 2}}, {{14, 4}, {14, 3}}));
    EXPECT_TRUE (reach({{15, 1}, {14, 1}}, {{14, 2}, {14, 1}}));
    EXPECT_TRUE (reach({{14, 2}, {14, 1}}, {{13, 3}, {13, 2}}));
    EXPECT_TRUE (reach({{15, 1}, {14, 1}}, {{13, 3}, {13, 2}}));
}

//   6. bottom left to top right
TEST_F(section_test, along_bottom_left_to_top_right)
{
    EXPECT_TRUE (reach({{14, 1}, {14, 1}}, {{15, 2}, {15, 2}}));
    EXPECT_TRUE (reach({{15, 2}, {15, 2}}, {{16, 3}, {15, 2}}));
    EXPECT_TRUE (reach({{14, 1}, {14, 1}}, {{16, 3}, {15, 2}}));
    EXPECT_TRUE (reach({{13, 2}, {13, 2}}, {{14, 3}, {14, 3}}));
    EXPECT_TRUE (reach({{14, 3}, {14, 3}}, {{15, 4}, {14, 4}}));
    EXPECT_TRUE (reach({{13, 2}, {13, 2}}, {{15, 4}, {14, 4}}));
}

//   7. top left to bottom right (reversed 5)
TEST_F(section_test, along_top_left_to_bottom_right)
{
    EXPECT_TRUE (reach({{15, 3}, {15, 2}}, {{16, 2}, {15, 2}}));
    EXPECT_TRUE (reach({{14, 4}, {14, 3}}, {{15, 3}, {15, 2}}));
    EXPECT_TRUE (reach({{14, 4}, {14, 3}}, {{16, 2}, {15, 2}}));
    EXPECT_TRUE (reach({{14, 2}, {14, 1}}, {{15, 1}, {14, 1}}));
    EXPECT_TRUE (reach({{13, 3}, {13, 2}}, {{14, 2}, {14, 1}}));
    EXPECT_TRUE (reach({{13, 3}, {13, 2}}, {{15, 1}, {14, 1}}));
}

//   8. top right to bottom left (reversed 6)
TEST_F(section_test, along_top_right_to_bottom_left)
{
    EXPECT_TRUE (reach({{15, 2}, {15, 2}}, {{14, 1}, {14, 1}}));
    EXPECT_TRUE (reach({{16, 3}, {16, 3}}, {{15, 2}, {15, 2}}));
    EXPECT_TRUE (reach({{16, 3}, {16, 3}}, {{14, 1}, {14, 1}}));
    EXPECT_TRUE (reach({{14, 3}, {14, 3}}, {{13, 2}, {13, 2}}));
    EXPECT_TRUE (reach({{15, 4}, {15, 4}}, {{14, 3}, {14, 3}}));
    EXPECT_TRUE (reach({{15, 4}, {15, 4}}, {{13, 2}, {13, 2}}));
}

//   9a. left to right (below)
TEST_F(section_test, along_left_to_right_1_below)
{
    EXPECT_TRUE (reach({{13, 2}, {13, 1}}, {{14, 2}, {14, 1}}));
    EXPECT_TRUE (reach({{13, 2}, {13, 1}}, {{15, 2}, {15, 1}}));
    EXPECT_TRUE (reach({{13, 2}, {13, 1}}, {{16, 2}, {16, 1}}));
    EXPECT_TRUE (reach({{14, 2}, {14, 1}}, {{15, 2}, {15, 1}}));
    EXPECT_TRUE (reach({{14, 2}, {14, 1}}, {{16, 2}, {16, 1}}));
    EXPECT_TRUE (reach({{15, 2}, {15, 1}}, {{16, 2}, {16, 1}}));
}

//   9b. same as 9a but virtually above
TEST_F(section_test, along_left_to_right_1_above)
{
    EXPECT_FALSE(reach({{13, 2}, {13, 2}}, {{14, 2}, {14, 2}}));
    EXPECT_TRUE (reach({{13, 2}, {13, 2}}, {{15, 2}, {15, 2}}));
    EXPECT_TRUE (reach({{13, 2}, {13, 2}}, {{16, 2}, {16, 2}}));
    EXPECT_FALSE(reach({{14, 2}, {14, 2}}, {{15, 2}, {15, 2}}));
    EXPECT_FALSE(reach({{14, 2}, {14, 2}}, {{16, 2}, {16, 2}}));
    EXPECT_TRUE (reach({{15, 2}, {15, 2}}, {{16, 2}, {16, 2}}));
}

//   9c. left to right (above)
TEST_F(section_test, along_left_to_right_2_above)
{
    EXPECT_TRUE (reach({{13, 3}, {13, 3}}, {{14, 3}, {14, 3}}));
    EXPECT_TRUE (reach({{13, 3}, {13, 3}}, {{15, 3}, {15, 3}}));
    EXPECT_TRUE (reach({{13, 3}, {13, 3}}, {{16, 3}, {16, 3}}));
    EXPECT_TRUE (reach({{14, 3}, {14, 3}}, {{15, 3}, {15, 3}}));
    EXPECT_TRUE (reach({{14, 3}, {14, 3}}, {{16, 3}, {16, 3}}));
    EXPECT_TRUE (reach({{15, 3}, {15, 3}}, {{16, 3}, {16, 3}}));
}

//   9d. same as 9c but virtually below
TEST_F(section_test, along_left_to_right_2_below)
{
    EXPECT_FALSE(reach({{13, 3}, {13, 2}}, {{14, 3}, {14, 2}}));
    EXPECT_TRUE (reach({{13, 3}, {13, 2}}, {{15, 3}, {15, 2}}));
    EXPECT_TRUE (reach({{13, 3}, {13, 2}}, {{16, 3}, {16, 2}}));
    EXPECT_FALSE(reach({{14, 3}, {14, 2}}, {{15, 3}, {15, 2}}));
    EXPECT_FALSE(reach({{14, 3}, {14, 2}}, {{16, 3}, {16, 2}}));
    EXPECT_TRUE (reach({{15, 3}, {15, 2}}, {{16, 3}, {16, 2}}));
}

//   10a. right to left (below) (reversed 9.a)
TEST_F(section_test, along_right_to_left_1_below)
{
    EXPECT_TRUE (reach({{14, 2}, {14, 1}}, {{13, 2}, {13, 1}}));
    EXPECT_TRUE (reach({{15, 2}, {15, 1}}, {{13, 2}, {13, 1}}));
    EXPECT_TRUE (reach({{16, 2}, {16, 1}}, {{13, 2}, {13, 1}}));
    EXPECT_TRUE (reach({{15, 2}, {15, 1}}, {{14, 2}, {14, 1}}));
    EXPECT_TRUE (reach({{16, 2}, {16, 1}}, {{14, 2}, {14, 1}}));
    EXPECT_TRUE (reach({{16, 2}, {16, 1}}, {{15, 2}, {15, 1}}));
}

//   10b. same as 10a but virtully above (reversed 9.b)
TEST_F(section_test, along_right_to_left_1_above)
{
    EXPECT_FALSE(reach({{14, 2}, {14, 2}}, {{13, 2}, {13, 2}}));
    EXPECT_TRUE (reach({{15, 2}, {15, 2}}, {{13, 2}, {13, 2}}));
    EXPECT_TRUE (reach({{16, 2}, {16, 2}}, {{13, 2}, {13, 2}}));
    EXPECT_FALSE(reach({{15, 2}, {15, 2}}, {{14, 2}, {14, 2}}));
    EXPECT_FALSE(reach({{16, 2}, {16, 2}}, {{14, 2}, {14, 2}}));
    EXPECT_TRUE (reach({{16, 2}, {16, 2}}, {{15, 2}, {15, 2}}));
}

//   10c. right to left (above) (reversed 9.c)
TEST_F(section_test, along_right_to_left_2_above)
{
    EXPECT_TRUE (reach({{14, 3}, {14, 3}}, {{13, 3}, {13, 3}}));
    EXPECT_TRUE (reach({{15, 3}, {15, 3}}, {{13, 3}, {13, 3}}));
    EXPECT_TRUE (reach({{16, 3}, {16, 3}}, {{13, 3}, {13, 3}}));
    EXPECT_TRUE (reach({{15, 3}, {15, 3}}, {{14, 3}, {14, 3}}));
    EXPECT_TRUE (reach({{16, 3}, {16, 3}}, {{14, 3}, {14, 3}}));
    EXPECT_TRUE (reach({{16, 3}, {16, 3}}, {{15, 3}, {15, 3}}));
}

//   10c. same as 10c but virtually below (reversed 9.d)
TEST_F(section_test, along_right_to_left_2_below)
{
    EXPECT_FALSE(reach({{14, 3}, {14, 2}}, {{13, 3}, {13, 2}}));
    EXPECT_TRUE (reach({{15, 3}, {15, 2}}, {{13, 3}, {13, 2}}));
    EXPECT_TRUE (reach({{16, 3}, {16, 2}}, {{13, 3}, {13, 2}}));
    EXPECT_FALSE(reach({{15, 3}, {15, 2}}, {{14, 3}, {14, 2}}));
    EXPECT_FALSE(reach({{16, 3}, {16, 2}}, {{14, 3}, {14, 2}}));
    EXPECT_TRUE (reach({{16, 3}, {16, 2}}, {{15, 3}, {15, 2}}));
}

/// @todo Under construction
//   11a. bottom to top (left)
//   11b. bottom to top (right)
//   12a. top to bottom (left) (reversed 11.a)
//   12b. top to bottom (right) (reversed 11.b)


// from Tile{0,1} to Tile {1,4}
// clockwise, f1 - left bottom from tile corner
// [f1, f2, f3, f4] -> [t1, t2, t3, t4]
class near_vertical_wall : public section_test
{
protected:

    // void SetUp() override { section_test::SetUp(); }

    // void TearDown() override {}

    Tile ft {0, 1};
    Tile tt {1, 4};
};


TEST_F(near_vertical_wall, source_to_target_south_west)
{
    // * -> t1
    Crossroad t {{1, 4}, tt};
    EXPECT_TRUE (reach({{0, 1}, ft}, t));
    EXPECT_TRUE (reach({{0, 2}, ft}, t));
    EXPECT_TRUE (reach({{1, 2}, ft}, t));
    EXPECT_TRUE (reach({{1, 1}, ft}, t));
}

TEST_F(near_vertical_wall, source_to_target_north_west)
{
    // * -> t2
    Crossroad t {{1, 5}, tt};
    EXPECT_TRUE (reach({{0, 1}, ft}, t));
    EXPECT_TRUE (reach({{0, 2}, ft}, t));
    EXPECT_TRUE (reach({{1, 2}, ft}, t));
    EXPECT_TRUE (reach({{1, 1}, ft}, t));
}

TEST_F(near_vertical_wall, source_to_target_north_east)
{
    // * -> t3
    Crossroad t {{2, 5}, tt};
    EXPECT_FALSE(reach({{0, 1}, ft}, t));
    EXPECT_FALSE(reach({{0, 2}, ft}, t));
    EXPECT_FALSE(reach({{1, 2}, ft}, t));
    EXPECT_FALSE(reach({{1, 1}, ft}, t));
}

TEST_F(near_vertical_wall, source_to_target_south_east)
{
    Crossroad t {{2, 4}, tt};
    // * -> t4
    EXPECT_FALSE(reach({{0, 1}, ft}, t));
    EXPECT_FALSE(reach({{0, 2}, ft}, t));
    EXPECT_FALSE(reach({{1, 2}, ft}, t));
    EXPECT_FALSE(reach({{1, 1}, ft}, t));
}


// from Tile{1,1} to Tile {1,4}
// clockwise, f1 - left bottom from tile corner
// [f1, f2, f3, f4] -> [t1, t2, t3, t4]
class through_vertical_wall : public section_test
{
protected:

    // void SetUp() override { section_test::SetUp(); }

    // void TearDown() override {}

    Tile ft {1, 1};
    Tile tt {1, 4};
};


TEST_F(through_vertical_wall, source_to_target_south_west)
{
    // * -> t1
    Crossroad t {{1, 4}, tt};
    EXPECT_TRUE (reach({{1, 1}, ft}, t));
    EXPECT_TRUE (reach({{1, 2}, ft}, t));
    EXPECT_FALSE(reach({{2, 2}, ft}, t));
    EXPECT_FALSE(reach({{2, 1}, ft}, t));
}

TEST_F(through_vertical_wall, source_to_target_north_west)
{
    // * -> t2
    Crossroad t {{1, 5}, tt};
    EXPECT_TRUE (reach({{1, 1}, ft}, t));
    EXPECT_TRUE (reach({{1, 2}, ft}, t));
    EXPECT_FALSE(reach({{2, 2}, ft}, t));
    EXPECT_FALSE(reach({{2, 1}, ft}, t));
}

TEST_F(through_vertical_wall, source_to_target_north_east)
{
    // * -> t3
    Crossroad t {{2, 5}, tt};
    EXPECT_FALSE(reach({{1, 1}, ft}, t));
    EXPECT_FALSE(reach({{1, 2}, ft}, t));
    EXPECT_TRUE (reach({{2, 2}, ft}, t));
    EXPECT_TRUE (reach({{2, 1}, ft}, t));
}

TEST_F(through_vertical_wall, source_to_target_south_east)
{
    Crossroad t {{2, 4}, tt};
    // * -> t4
    EXPECT_FALSE(reach({{1, 1}, ft}, t));
    EXPECT_FALSE(reach({{1, 2}, ft}, t));
    EXPECT_TRUE (reach({{2, 2}, ft}, t));
    EXPECT_TRUE (reach({{2, 1}, ft}, t));
}
