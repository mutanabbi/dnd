#include "../geo/Section.hpp"
#include "../geo/Coordinate.hpp"
//#include <iostream> // TODO: DEBUG ONLY
#include <cassert>


int main(int /*argc*/, char* /*argv*/[])
{
    {
        auto reach = [](const Crossroad& from, const Crossroad& to) {
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

        assert(true == is_tile_occupied({14, 2}));

        /// @todo These constraints below must be respected
        // across
        //   1. bottom right to top left
        assert(true  == reach({{16, 1}, {15, 1}}, {{15, 2}, {15, 1}}));
        assert(false == reach({{16, 1}, {15, 1}}, {{14, 3}, {14, 2}}));
        assert(false == reach({{16, 1}, {15, 1}}, {{13, 4}, {13, 3}}));
        //   2. bottom left to top right
        assert(true  == reach({{13, 1}, {13, 1}}, {{14, 2}, {13, 1}}));
        assert(false == reach({{13, 1}, {13, 1}}, {{15, 3}, {14, 2}}));
        assert(false == reach({{13, 1}, {13, 1}}, {{16, 4}, {15, 3}}));
        //   3. top left to bottom right
        assert(true  == reach({{13, 4}, {13, 3}}, {{14, 3}, {13, 3}}));
        assert(false == reach({{13, 4}, {13, 3}}, {{15, 2}, {14, 2}}));
        assert(false == reach({{13, 4}, {13, 3}}, {{16, 1}, {15, 1}}));
        //   4. top right to bottom left
        assert(true  == reach({{16, 4}, {16, 3}}, {{15, 3}, {15, 3}}));
        assert(false == reach({{16, 4}, {16, 3}}, {{14, 2}, {14, 2}}));
        assert(false == reach({{16, 4}, {16, 3}}, {{13, 1}, {13, 1}}));
        // along
        //   5. bottom right to top left
        assert(true == reach({{16, 2}, {15, 2}}, {{15, 3}, {15, 2}}));
        assert(true == reach({{15, 3}, {15, 2}}, {{14, 4}, {14, 3}}));
        assert(true == reach({{16, 2}, {15, 2}}, {{14, 4}, {14, 3}}));
        assert(true == reach({{15, 1}, {14, 1}}, {{14, 2}, {14, 1}}));
        assert(true == reach({{14, 2}, {14, 1}}, {{13, 3}, {13, 2}}));
        assert(true == reach({{15, 1}, {14, 1}}, {{13, 3}, {13, 2}}));
        //   6. bottom left to top right
        assert(true == reach({{14, 1}, {14, 1}}, {{15, 2}, {15, 2}}));
        assert(true == reach({{15, 2}, {15, 2}}, {{16, 3}, {15, 2}}));
        assert(true == reach({{14, 1}, {14, 1}}, {{16, 3}, {15, 2}}));
        assert(true == reach({{13, 2}, {13, 2}}, {{14, 3}, {14, 3}}));
        assert(true == reach({{14, 3}, {14, 3}}, {{15, 4}, {14, 4}}));
        assert(true == reach({{13, 2}, {13, 2}}, {{15, 4}, {14, 4}}));
        //   7. top left to bottom right (reversed 5)
        assert(true == reach({{15, 3}, {15, 2}}, {{16, 2}, {15, 2}}));
        assert(true == reach({{14, 4}, {14, 3}}, {{15, 3}, {15, 2}}));
        assert(true == reach({{14, 4}, {14, 3}}, {{16, 2}, {15, 2}}));
        assert(true == reach({{14, 2}, {14, 1}}, {{15, 1}, {14, 1}}));
        assert(true == reach({{13, 3}, {13, 2}}, {{14, 2}, {14, 1}}));
        assert(true == reach({{13, 3}, {13, 2}}, {{15, 1}, {14, 1}}));
        //   8. top right to bottom left (reversed 6)
        assert(true == reach({{15, 2}, {15, 2}}, {{14, 1}, {14, 1}}));
        assert(true == reach({{16, 3}, {16, 3}}, {{15, 2}, {15, 2}}));
        assert(true == reach({{16, 3}, {16, 3}}, {{14, 1}, {14, 1}}));
        assert(true == reach({{14, 3}, {14, 3}}, {{13, 2}, {13, 2}}));
        assert(true == reach({{15, 4}, {15, 4}}, {{14, 3}, {14, 3}}));
        assert(true == reach({{15, 4}, {15, 4}}, {{13, 2}, {13, 2}}));
        //   9a. left to right (below)
        assert(true == reach({{13, 2}, {13, 1}}, {{14, 2}, {14, 1}}));
        assert(true == reach({{13, 2}, {13, 1}}, {{15, 2}, {15, 1}}));
        assert(true == reach({{13, 2}, {13, 1}}, {{16, 2}, {16, 1}}));
        assert(true == reach({{14, 2}, {14, 1}}, {{15, 2}, {15, 1}}));
        assert(true == reach({{14, 2}, {14, 1}}, {{16, 2}, {16, 1}}));
        assert(true == reach({{15, 2}, {15, 1}}, {{16, 2}, {16, 1}}));
        //   9b. same but virtually above
        assert(false == reach({{13, 2}, {13, 2}}, {{14, 2}, {14, 2}}));
        assert(true  == reach({{13, 2}, {13, 2}}, {{15, 2}, {15, 2}}));
        assert(true  == reach({{13, 2}, {13, 2}}, {{16, 2}, {16, 2}}));
        assert(false == reach({{14, 2}, {14, 2}}, {{15, 2}, {15, 2}}));
        assert(false == reach({{14, 2}, {14, 2}}, {{16, 2}, {16, 2}}));
        assert(true  == reach({{15, 2}, {15, 2}}, {{16, 2}, {16, 2}}));
        //   9c. left to right (above)
        assert(true == reach({{13, 3}, {13, 3}}, {{14, 3}, {14, 3}}));
        assert(true == reach({{13, 3}, {13, 3}}, {{15, 3}, {15, 3}}));
        assert(true == reach({{13, 3}, {13, 3}}, {{16, 3}, {16, 3}}));
        assert(true == reach({{14, 3}, {14, 3}}, {{15, 3}, {15, 3}}));
        assert(true == reach({{14, 3}, {14, 3}}, {{16, 3}, {16, 3}}));
        assert(true == reach({{15, 3}, {15, 3}}, {{16, 3}, {16, 3}}));
        //   9d. same but virtually below
        assert(false == reach({{13, 3}, {13, 2}}, {{14, 3}, {14, 2}}));
        assert(true  == reach({{13, 3}, {13, 2}}, {{15, 3}, {15, 2}}));
        assert(true  == reach({{13, 3}, {13, 2}}, {{16, 3}, {16, 2}}));
        assert(false == reach({{14, 3}, {14, 2}}, {{15, 3}, {15, 2}}));
        assert(false == reach({{14, 3}, {14, 2}}, {{16, 3}, {16, 2}}));
        assert(true  == reach({{15, 3}, {15, 2}}, {{16, 3}, {16, 2}}));
        //   10a. right to left (below) (reversed 9.a)
        assert(true == reach({{14, 2}, {14, 1}}, {{13, 2}, {13, 1}}));
        assert(true == reach({{15, 2}, {15, 1}}, {{13, 2}, {13, 1}}));
        assert(true == reach({{16, 2}, {16, 1}}, {{13, 2}, {13, 1}}));
        assert(true == reach({{15, 2}, {15, 1}}, {{14, 2}, {14, 1}}));
        assert(true == reach({{16, 2}, {16, 1}}, {{14, 2}, {14, 1}}));
        assert(true == reach({{16, 2}, {16, 1}}, {{15, 2}, {15, 1}}));
        //   10b. same but virtully above (reversed 9.b)
        assert(false == reach({{14, 2}, {14, 2}}, {{13, 2}, {13, 2}}));
        assert(true  == reach({{15, 2}, {15, 2}}, {{13, 2}, {13, 2}}));
        assert(true  == reach({{16, 2}, {16, 2}}, {{13, 2}, {13, 2}}));
        assert(false == reach({{15, 2}, {15, 2}}, {{14, 2}, {14, 2}}));
        assert(false == reach({{16, 2}, {16, 2}}, {{14, 2}, {14, 2}}));
        assert(true  == reach({{16, 2}, {16, 2}}, {{15, 2}, {15, 2}}));
        //   10c. right to left (above) (reversed 9.c)
        assert(true == reach({{14, 3}, {14, 3}}, {{13, 3}, {13, 3}}));
        assert(true == reach({{15, 3}, {15, 3}}, {{13, 3}, {13, 3}}));
        assert(true == reach({{16, 3}, {16, 3}}, {{13, 3}, {13, 3}}));
        assert(true == reach({{15, 3}, {15, 3}}, {{14, 3}, {14, 3}}));
        assert(true == reach({{16, 3}, {16, 3}}, {{14, 3}, {14, 3}}));
        assert(true == reach({{16, 3}, {16, 3}}, {{15, 3}, {15, 3}}));
        //   10c. same but virtually below (reversed 9.d)
        assert(false == reach({{14, 3}, {14, 2}}, {{13, 3}, {13, 2}}));
        assert(true  == reach({{15, 3}, {15, 2}}, {{13, 3}, {13, 2}}));
        assert(true  == reach({{16, 3}, {16, 2}}, {{13, 3}, {13, 2}}));
        assert(false == reach({{15, 3}, {15, 2}}, {{14, 3}, {14, 2}}));
        assert(false == reach({{16, 3}, {16, 2}}, {{14, 3}, {14, 2}}));
        assert(true  == reach({{16, 3}, {16, 2}}, {{15, 3}, {15, 2}}));
        //   11a. bottom to top (left)
        //   11b. bottom to top (right)
        //   12a. top to bottom (left) (reversed 11.a)
        //   12b. top to bottom (right) (reversed 11.b)

        {
        assert(false == is_tile_occupied({0, 1}));
        assert(false == is_tile_occupied({0, 2}));
        assert(false == is_tile_occupied({0, 3}));
        assert(false == is_tile_occupied({0, 4}));
        assert(true  == is_tile_occupied({0, 5}));

        assert(true  == is_tile_occupied({1, 2}));
        assert(true  == is_tile_occupied({1, 3}));
        assert(false == is_tile_occupied({1, 4}));
        assert(true  == is_tile_occupied({1, 5}));

        assert(false == is_tile_occupied({2, 1}));
        assert(false == is_tile_occupied({2, 2}));
        assert(false == is_tile_occupied({2, 3}));
        assert(false == is_tile_occupied({2, 4}));
        assert(true  == is_tile_occupied({2, 5}));

        {
            // from Tile{0,1} to Tile {1,4}
            // clockwise, f1 - left bottom from tile corner
            // [f1, f2, f3, f4] -> [t1, t2, t3, t4]
            Tile ft {0, 1};
            Tile tt {1, 4};
            {
            // * -> t1
            Crossroad t {{1, 4}, tt};
            assert(true  == reach({{0, 1}, ft}, t));
            assert(true  == reach({{0, 2}, ft}, t));
            assert(true  == reach({{1, 2}, ft}, t));
            assert(true  == reach({{1, 1}, ft}, t));
            }

            {
            // * -> t2
            Crossroad t {{1, 5}, tt};
            assert(true  == reach({{0, 1}, ft}, t));
            assert(true  == reach({{0, 2}, ft}, t));
            assert(true  == reach({{1, 2}, ft}, t));
            assert(true  == reach({{1, 1}, ft}, t));
            }

            {
            // * -> t3
            Crossroad t {{2, 5}, tt};
            assert(false == reach({{0, 1}, ft}, t));
            assert(false == reach({{0, 2}, ft}, t));
            assert(false == reach({{1, 2}, ft}, t));
            assert(false == reach({{1, 1}, ft}, t));
            }

            {
            Crossroad t {{2, 4}, tt};
            // * -> t4
            assert(false == reach({{0, 1}, ft}, t));
            assert(false == reach({{0, 2}, ft}, t));
            assert(false == reach({{1, 2}, ft}, t));
            assert(false == reach({{1, 1}, ft}, t));
            }
        }

        {
            // from Tile{1,1} to Tile {1,4}
            // clockwise, f1 - left bottom from tile corner
            // [f1, f2, f3, f4] -> [t1, t2, t3, t4]
            Tile ft {1, 1};
            Tile tt {1, 4};
            {
            // * -> t1
            Crossroad t {{1, 4}, tt};
            assert(true  == reach({{1, 1}, ft}, t));
            assert(true  == reach({{1, 2}, ft}, t));
            assert(false  == reach({{2, 2}, ft}, t));
            assert(false  == reach({{2, 1}, ft}, t));
            }

            {
            // * -> t2
            Crossroad t {{1, 5}, tt};
            assert(true  == reach({{1, 1}, ft}, t));
            assert(true  == reach({{1, 2}, ft}, t));
            assert(false  == reach({{2, 2}, ft}, t));
            assert(false  == reach({{2, 1}, ft}, t));
            }

            {
            // * -> t3
            Crossroad t {{2, 5}, tt};
            assert(false == reach({{1, 1}, ft}, t));
            assert(false == reach({{1, 2}, ft}, t));
            assert(true == reach({{2, 2}, ft}, t));
            assert(true == reach({{2, 1}, ft}, t));
            }

            {
            Crossroad t {{2, 4}, tt};
            // * -> t4
            assert(false == reach({{1, 1}, ft}, t));
            assert(false == reach({{1, 2}, ft}, t));
            assert(true == reach({{2, 2}, ft}, t));
            assert(true == reach({{2, 1}, ft}, t));
            }
        }
        }

    }
    return 0;
}
