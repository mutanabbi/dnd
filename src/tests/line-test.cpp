#include <geo/Line.hpp>
#include <gtest/gtest.h>
//#include <iostream> // TODO: DEBUG ONLY

#if 0
namespace {

void x2y(int x, Line ln)
{
    /** @todo It's impossible to write <code> operator<<(ostream. const optional<rational>&) </code>
     *  since boost::rational use some strange sfinae approach which isn't really sfinae. An attempt
     *  just to otput any string leads to substitution failue during std::optional parametr type deduction
     *  and to compiler error
     */
    auto y = ln.x2y(x);
    std::cout << "x:" << x << " -> y:";
    if (y)
        std::cout << (*y);
    else
        std::cout << "nullopt";
    std::cout << std::endl;
}

void y2x(int y, Line ln)
{
    auto x = ln.y2x(y);
    std::cout << "x:";
    if (x)
        std::cout << (*x);
    else
        std::cout << "nullopt";
    std::cout << " <- y:" << y << std::endl;
}

}                                                           // anonymous namespace
#endif

TEST(line_test, different_coordinates_equality)
{
    /*
    Line m({2, 1}, {4, 4});
    for (int i = 0; i < 5; ++i)
        x2y(i, m);
    for (int i = 0; i < 5; ++i)
        y2x(i, m);
    */

    Line l1({0,0},{2,2});
    Line l2({3,3},{10,10});
    //std::cout << l1 << std::endl;
    //std::cout << l2 << std::endl;
    EXPECT_EQ(l1.x2y(0), l2.x2y(0));
    EXPECT_EQ(l1.x2y(5), l2.x2y(5));
    EXPECT_EQ(l1.y2x(0), l2.y2x(0));
    EXPECT_EQ(l1.y2x(5), l2.y2x(5));
    EXPECT_EQ(l1, l2);
}

TEST(line_test, non_equality)
{
    Line l1({1,0},{3,6});
    Line l2({1,-2},{3,-6});
    //std::cout << l1 << std::endl;
    //std::cout << l2 << std::endl;
    EXPECT_NE(l1, l2);
}

TEST(line_test, crosed_lines_built_by_shared_coordinate_non_equality)
{
    Line l1({0,0},{3,6});
    Line l2({0,0},{3,-6});
    //std::cout << l1 << std::endl;
    //std::cout << l2 << std::endl;
    EXPECT_NE(l1, l2);
    EXPECT_TRUE(l1.contains({0,0}));
    EXPECT_TRUE(l2.contains({0,0}));
}

TEST(line_test, crossed_lines_non_equality)
{
    // 2.3
    Line l1({1,2},{3,4});
    Line l2({2,0},{2,42});
    //std::cout << l1 << std::endl;
    //std::cout << l2 << std::endl;
    EXPECT_NE(l1, l2);
    EXPECT_TRUE(l1.contains({2,3}));
    EXPECT_TRUE(l2.contains({2,3}));
}
