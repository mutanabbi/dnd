#include "../Crossroad.hpp"
#include "../Section.hpp"
#include <vector>
#include <iostream>
#include <cassert>


int main(int /*argc*/, char* /*argv*/[])
{
    auto prnt_trajectory = [&cout = std::cout](const auto& vec) {
        cout << "[";
        for (const auto& c : vec)
            cout << c << " | ";
        (cout << "]\n").flush();
    };
    {
        using pt = Coordinate;
        using tl = Tile;
        using vec = std::vector<Crossroad>;
        using rt = boost::rational<int>;

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
        assert(!is_tile_occupied({1, 1}));
        assert(is_tile_occupied({1, 2}));
        assert(is_tile_occupied({1, 3}));
        assert(!is_tile_occupied({1, 4}));

        {
        auto from = Crossroad{Coordinate{1, 1}, Tile{1, 1}};
        auto to = Crossroad{Coordinate{1, 4}, Tile{1, 4}};
        auto sec = Section{from, to};
        assert((sec.get_trajectory() == vec{
            {pt{1, 1}, tl{1, 1}}
          , {pt{1, 2}, tl{1, 1}}
          , {pt{1, 2}, tl{1, 2}}
          , {pt{1, 3}, tl{1, 2}}
          , {pt{1, 3}, tl{1, 3}}
          , {pt{1, 4}, tl{1, 3}}
          , {pt{1, 4}, tl{1, 4}}
        }));
        /*
        assert(true == sec.is_reachable());
        */
        }
        {
        auto from = Crossroad{Coordinate{1, 1}, Tile{1, 1}};
        auto to = Crossroad{Coordinate{2, 4}, Tile{1, 4}};
        auto sec = Section{from, to};
        assert((sec.get_trajectory() == vec{
            {pt{1, 1}, tl{1, 1}}
          , {pt{rt(4)/3, 2}, tl{1, 1}}
          , {pt{rt(4)/3, 2}, tl{1, 2}}
          , {pt{rt(5)/3, 3}, tl{1, 2}}
          , {pt{rt(5)/3, 3}, tl{1, 3}}
          , {pt{2, 4}, tl{1, 3}}
          , {pt{2, 4}, tl{1, 4}}
        }));
        //assert(false == sec.is_reachable());
        }
        {
        auto from = Crossroad{Coordinate{1, 1}, Tile{1, 1}};
        auto to = Crossroad{Coordinate{2, 5}, Tile{1, 4}};
        auto sec = Section{from, to};
        prnt_trajectory(sec.get_trajectory());
        assert((sec.get_trajectory() == vec{
            {pt{1, 1}, tl{1, 1}}
          , {pt{rt(5)/4, 2}, tl{1, 1}}
          , {pt{rt(5)/4, 2}, tl{1, 2}}
          , {pt{rt(3)/2, 3}, tl{1, 2}}
          , {pt{rt(3)/2, 3}, tl{1, 3}}
          , {pt{rt(7)/4, 4}, tl{1, 3}}
          , {pt{rt(7)/4, 4}, tl{1, 4}}
          , {pt{2, 5}, tl{1, 4}}
        }));
        //assert(false == sec.is_reachable());
        }
    }
    return 0;
}
