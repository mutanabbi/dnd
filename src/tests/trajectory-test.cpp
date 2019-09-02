#include <geo/Trajectory.hpp>
#include <geo/Coordinate.hpp>
#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <cassert>


using sample = std::vector<Coordinate>;
using rt = boost::rational<int>;

// test trajectory value and ordering
TEST(trajectory_test, ordering)
{
    // to itself - no direction
    assert((sample{{0, 0}} == get_trajectory(0, 0, 0, 0)));
    // left -> right
    assert((sample{{0, 0}, {1, 0}} == get_trajectory(0, 0, 1, 0)));
    assert((sample{{0, 0}, {1, 0}, {2, 0}} == get_trajectory(0, 0, 2, 0)));
    // right -> left
    assert((sample{{1, 0}, {0, 0}} == get_trajectory(1, 0, 0, 0)));
    assert((sample{{2, 0}, {1, 0}, {0, 0}} == get_trajectory(2, 0, 0, 0)));
    // bottom -> top
    assert((sample{{0, 0}, {0, 1}} == get_trajectory(0, 0, 0, 1)));
    assert((sample{{0, 0}, {0, 1}, {0, 2}} == get_trajectory(0, 0, 0, 2)));
    // top -> bottom
    assert((sample{{0, 1}, {0, 0}} == get_trajectory(0, 1, 0, 0)));
    assert((sample{{0, 2}, {0, 1}, {0, 0}} == get_trajectory(0, 2, 0, 0)));
    // left bottom -> right top
    assert((sample{{0, 0}, {1, 1}} == get_trajectory(0, 0, 1, 1)));
    assert((sample{{0, 0}, {1, 1}, {2, 2}} == get_trajectory(0, 0, 2, 2)));
    // right top -> left bottom
    assert((sample{{1, 1}, {0, 0}} == get_trajectory(1, 1, 0, 0)));
    assert((sample{{2, 2}, {1, 1}, {0, 0}} == get_trajectory(2, 2, 0, 0)));
    // left top -> right bottom
    assert((sample{{0, 1}, {1, 0}} == get_trajectory(0, 1, 1, 0)));
    assert((sample{{0, 2}, {1, 1}, {2, 0}} == get_trajectory(0, 2, 2, 0)));
    // right bottom -> left top
    assert((sample{{1, 0}, {0, 1}} == get_trajectory(1, 0, 0, 1)));
    assert((sample{{2, 0}, {1, 1}, {0, 2}} == get_trajectory(2, 0, 0, 2)));
}

namespace {

// apply get_trajectory w/ tuple of arguments in direct order 0, 1, 2, 3
template <typename... T>
auto f(const std::tuple<T...>& tpl) {
    return std::apply(
        static_cast<std::vector<Coordinate>(*)(unsigned, unsigned, unsigned, unsigned)>(get_trajectory)
      , tpl
    );
};

// apply get_trajectory w/ tuple of arguments in partially reversed order 2, 3, 0, 1
template <typename... T>
auto r(const std::tuple<T...>& tpl) {
    using namespace std;
    return apply(
        static_cast<vector<Coordinate>(*)(unsigned, unsigned, unsigned, unsigned)>(get_trajectory)
      , tie(get<2>(tpl), get<3>(tpl), get<0>(tpl), get<1>(tpl))
    );
};

// invert vector
template <typename T, typename A>
auto i(std::vector<T, A> vec)
{
    std::reverse(begin(vec), end(vec));
    return vec;
};

/*
std::ostream& operator<<(std::ostream& os, const std::vector<Coordinate>& v)
{
    os << "[";
    for (const auto& pt : v)
        os << pt << ", ";
    return os << "]";
}
*/
} // anonymous namespace

TEST(trajectory_test, point_to_itself_1)
{
    auto args = std::make_tuple(0u, 0u, 0u, 0u);
    auto rslt = f(args);
    auto expect = sample{{0, 0}};
    EXPECT_EQ(expect, rslt);
}

TEST(trajectory_test, point_to_itself_2)
{
    auto args = std::make_tuple(42, 42, 42, 42);
    auto rslt = f(args);
    auto expect = sample{{42, 42}};
    EXPECT_EQ(expect, rslt);
}

// bottom left to top right
TEST(trajectory_test, bottom_left_to_top_right)
{
    {
    auto args = std::make_tuple(0u, 0u, 1u, 1u);
    auto expect = sample{{0, 0}, {1, 1}};
    auto rslt = f(args);
    EXPECT_EQ(expect, rslt);
    EXPECT_EQ(r(args), i(rslt));
    }
    {
    auto args = std::make_tuple(0, 0, 2, 2);
    auto expect = sample{{0, 0}, {1, 1}, {2, 2}};
    auto rslt = f(args);
    EXPECT_EQ(rslt, expect);
    EXPECT_EQ(r(args), i(rslt));
    }
    {
    auto args = std::make_tuple(0, 0, 3, 3);
    auto expect = sample{{0, 0}, {1, 1}, {2, 2}, {3, 3}};
    auto rslt = f(args);
    EXPECT_EQ(rslt, expect);
    EXPECT_EQ(r(args), i(rslt));
    }
    {
    auto args = std::make_tuple(2, 0, 3, 2);
    auto expect = sample{{2, 0}, {rt(5)/2, 1}, {3, 2}};
    auto rslt = f(args);
    EXPECT_EQ(rslt, expect);
    EXPECT_EQ(r(args), i(rslt));
    }
    {
    auto args = std::make_tuple(2, 0, 3, 3);
    auto rslt = f(args);
    auto expect = sample{{2, 0}, {rt(7)/3, 1}, {rt(8)/3, 2}, {3, 3}};
    EXPECT_EQ(rslt, expect);
    EXPECT_EQ(r(args), i(rslt));
    }
    {
    auto args = std::make_tuple(2, 0, 4, 3);
    auto rslt = f(args);
    auto expect = sample{{2, 0}, {rt(8)/3, 1}, {3, rt(3)/2}, {rt(10)/3, 2}, {4, 3}};
    EXPECT_EQ(rslt, expect);
    EXPECT_EQ(r(args), i(rslt));
    }
}

TEST(trajectory_test, top_left_to_bottom_right)
{
    // top left to bottom right
    {
    auto args = std::make_tuple(2, 3, 4, 0);
    auto rslt = f(args);
    auto expect = sample{{2, 3}, {rt(8)/3, 2}, {3, rt(3)/2}, {rt(10)/3, 1}, {4, 0}};
    EXPECT_EQ(rslt, expect);
    EXPECT_EQ(r(args), i(rslt));
    }
    {
    auto args = std::make_tuple(2, 3, 4, 1);
    auto rslt = f(args);
    auto expect = sample{{2, 3}, {3, 2}, {4, 1}};
    EXPECT_EQ(rslt, expect);
    EXPECT_EQ(r(args), i(rslt));
    }
    {
    auto args = std::make_tuple(2, 3, 4, 2);
    auto rslt = f(args);
    auto expect = sample{{2, 3}, {3, rt(5)/2}, {4, 2}};
    EXPECT_EQ(rslt, expect);
    EXPECT_EQ(r(args), i(rslt));
    }
    {
    auto args = std::make_tuple(2, 3, 3, 0);
    auto rslt = f(args);
    auto expect = sample{{2, 3}, {rt(7)/3, 2}, {rt(8)/3, 1}, {3, 0}};
    EXPECT_EQ(rslt, expect);
    EXPECT_EQ(r(args), i(rslt));
    }
    {
    auto args = std::make_tuple(2, 3, 3, 1);
    auto rslt = f(args);
    auto expect = sample{{2, 3}, {rt(5)/2, 2}, {3, 1}};
    EXPECT_EQ(rslt, expect);
    EXPECT_EQ(r(args), i(rslt));
    }
    {
    auto args = std::make_tuple(2, 3, 3, 2);
    auto rslt = f(args);
    auto expect = sample{{2, 3}, {3, 2}};
    EXPECT_EQ(rslt, expect);
    EXPECT_EQ(r(args), i(rslt));
    }
}

TEST(trajectory_test, vertical_line)
{
    auto args = std::make_tuple(2, 0, 2, 5);
    auto rslt = f(args);
    auto expect = sample{{2, 0}, {2, 1}, {2, 2}, {2, 3}, {2, 4}, {2, 5}};
    EXPECT_EQ(rslt, expect);
    EXPECT_EQ(r(args), i(rslt));
}

TEST(trajectory_test, horizontal_line)
{
    auto args = std::make_tuple(1, 4, 7, 4);
    auto rslt = f(args);
    auto expect = sample{{1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 4}, {7, 4}};
    EXPECT_EQ(rslt, expect);
    EXPECT_EQ(r(args), i(rslt));
}
