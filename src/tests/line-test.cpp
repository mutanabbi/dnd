#include "../geo/Line.hpp"
#include <iostream>
#include <cassert>


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

int main(int /*argc*/, char* /*argv*/[])
{
    Line m({2, 1}, {4, 4});
    for (int i = 0; i < 5; ++i)
        x2y(i, m);
    for (int i = 0; i < 5; ++i)
        y2x(i, m);

    {
    Line l1({0,0},{2,2});
    Line l2({3,3},{10,10});
    std::cout << l1 << std::endl;
    std::cout << l2 << std::endl;
    assert(l1.x2y(0) == l2.x2y(0));
    assert(l1.x2y(5) == l2.x2y(5));
    assert(l1.y2x(0) == l2.y2x(0));
    assert(l1.y2x(5) == l2.y2x(5));
    assert(l1 == l2);
    }

    {
    Line l1({1,0},{3,6});
    Line l2({1,-2},{3,-6});
    std::cout << l1 << std::endl;
    std::cout << l2 << std::endl;
    assert(l1 != l2);
    }

    {
    Line l1({0,0},{3,6});
    Line l2({0,0},{3,-6});
    std::cout << l1 << std::endl;
    std::cout << l2 << std::endl;
    assert(l1 != l2);
    assert(l1.contains({0,0}));
    assert(l2.contains({0,0}));
    }

    {
        // 2.3
    Line l1({1,2},{3,4});
    Line l2({2,0},{2,42});
    std::cout << l1 << std::endl;
    std::cout << l2 << std::endl;
    assert(l1 != l2);
    assert(l1.contains({2,3}));
    assert(l2.contains({2,3}));
    }
    return 0;
}
