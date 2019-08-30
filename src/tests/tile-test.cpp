#include "../geo/Tile.hpp"
#include <boost/rational.hpp>
#include <cassert>


int main(int /*argc*/, char* /*argv*/[])
{
    using namespace boost;
    using rt = rational<int>;
    assert(0 == rational_cast<unsigned>(rt(1) / 2));
    assert(0 == rational_cast<unsigned>(rt(2) / 3));
    assert(0 == rational_cast<unsigned>(rt(3) / 4));

    assert(Tile({0, 0}).contains({0, 0}));
    assert(Tile({0, 0}).contains({1, 1}));
    assert(Tile({0, 0}).contains({0, 1}));
    assert(Tile({0, 0}).contains({1, 0}));

    assert(Tile({1, 0}).contains({1, 1}));
    assert(Tile({0, 1}).contains({1, 1}));
    assert(Tile({1, 1}).contains({1, 1}));

    assert(Tile({0, 1}).contains({0, 1}));

    assert(Tile({1, 0}).contains({1, 0}));

    // rational
    assert(Tile({0, 0}).contains({rt(1)/2, 1}));
    assert(Tile({0, 0}).contains({1, rt(1)/2}));
    assert(Tile({0, 0}).contains({rt(1)/2, 0}));
    assert(Tile({0, 0}).contains({0, rt(1)/2}));

    assert(Tile({0, 0}).contains({rt(1)/2, 1}));
    assert(Tile({0, 0}).contains({1, rt(1)/2}));
    assert(Tile({0, 0}).contains({rt(1)/2, 0}));
    assert(Tile({0, 0}).contains({0, rt(1)/2}));
    return 0;
}
