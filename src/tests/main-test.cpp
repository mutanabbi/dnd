#include "../geo/Crossroad.hpp"
#include "../geo/Section.hpp"
#include "../geo/Coverage.hpp"

#include <iostream>
#include <cassert>

/// @todo Useful but not utilized tool
/*
template <typename T, std::size_t... I>
auto reverse_tuple_impl(T&& t, std::index_sequence<I...>)
{
    return std::make_tuple(
        std::get<sizeof...(I) - I -1>(std::forward<T>(t))...
    );
}

template <typename T>
auto reverse_tuple(T&& t)
{
    return reverse_tuple_impl(
        std::forward<T>(t)
      , std::make_index_sequence<
            std::tuple_size<
                typename std::remove_reference<T>::type
            >::value
        >{}
    );
}
*/

int main(int /*argc*/, char* /*argv*/[])
{
#if 0
    {
        std::cout << get_trajectory(3, 3, 2, 4) << std::endl;
        // from Tile (2,2)
        std::cout << is_reachable(Coordinate{3, 3}, Section{{3, 3}, {2, 4}}) << std::endl;
        std::cout << is_reachable(Coordinate{3, 3}, Section{{3, 3}, {1, 4}}) << std::endl;
        std::cout << is_reachable(Coordinate{3, 3}, Section{{3, 3}, {1, 5}}) << std::endl;
        std::cout << get_trajectory(3, 3, 2, 5) << std::endl;
        std::cout << is_reachable(Coordinate{3, 3}, Section{{3, 3}, {2, 5}}) << std::endl;
    }
#endif

#if 0
    {
        // from Tile (2,2)
        std::cout << check_cover(Coordinate{3, 3}, Tile{1, 4}) << std::endl;
        assert(cover::partial == check_cover(Coordinate{3, 3}, Tile{1, 4}));
    }

    {
        /// @todo I'm here
    std::cout << "======================================" << std::endl;
        std::cout << check_cover(Tile{10, 1}, Tile{9, 3}) << std::endl;
        std::cout << is_reachable(Coordinate{10, 1}, Section{{10, 1}, {9, 3}}) << std::endl;
        std::cout << is_reachable(Coordinate{10, 1}, Section{{10, 1}, {9, 4}}) << std::endl;
        std::cout << is_reachable(Coordinate{10, 1}, Section{{10, 1}, {10, 3}}) << std::endl;
        std::cout << is_reachable(Coordinate{10, 1}, Section{{10, 1}, {10, 4}}) << std::endl;
    std::cout << "======================================" << std::endl;
        std::cout << is_reachable(Coordinate{11, 1}, Section{{11, 1}, {9, 3}}) << std::endl;
        std::cout << is_reachable(Coordinate{11, 1}, Section{{11, 1}, {9, 4}}) << std::endl;
        std::cout << is_reachable(Coordinate{11, 1}, Section{{11, 1}, {10, 3}}) << std::endl;
        std::cout << is_reachable(Coordinate{11, 1}, Section{{11, 1}, {10, 4}}) << std::endl;
/*
        std::cout << is_reachable(Coordinate{3, 3}, Section{{3, 3}, {2, 4}}) << std::endl;
        std::cout << is_reachable(Coordinate{3, 3}, Section{{3, 3}, {1, 4}}) << std::endl;
        std::cout << is_reachable(Coordinate{3, 3}, Section{{3, 3}, {1, 5}}) << std::endl;
*/
    }
#endif

    auto prnt_trajectory = [&cout = std::cout](const auto& vec) {
        cout << "[";
        for (const auto& c : vec)
            cout << c << " | ";
        (cout << "]\n").flush();
    };

    {
        assert(cover::no == check_cover(Tile{0, 0}, Tile{0, 0}));
        std::cout << check_cover(Tile{0, 0}, Tile{1, 1}) << std::endl;
        auto f = [](const auto& from, const auto& to)
        {
            for (auto fx = from.x; fx <= from.x + 1; ++fx)
                for (auto fy = from.y; fy <= from.y + 1; ++fy)
                {
                    auto cr = Crossroad{{fx, fy}, from};
                    std::cout << cr << "->" << to << " = " << check_cover(cr, to) << std::endl;
                }
        };
        f(Tile{0, 0}, Tile{1, 1});

        assert(cover::no == check_cover(Tile{0, 0}, Tile{1, 1}));
        assert(cover::no == check_cover(Tile{0, 0}, Tile{1, 0}));
        assert(cover::no == check_cover(Tile{0, 0}, Tile{2, 0}));

        std::cout << check_cover(Tile{0, 1}, Tile{1, 4}) << std::endl;
        assert(cover::total == check_cover(Tile{0, 1}, Tile{1, 4}));

        assert(!is_tile_occupied({1, 1}));
        assert(is_tile_occupied({1, 2}));
        assert(is_tile_occupied({1, 3}));
        assert(!is_tile_occupied({1, 4}));

        std::cout << check_cover(Tile{1, 1}, Tile{1, 4}) << std::endl;
        std::cout << "==============" << std::endl;
        f(Tile{1, 1}, Tile{1, 4});
        {
          {
            // vertical line along border
            Crossroad f{{2, 1}, {1, 1}};
            {
                Crossroad t{{2, 4}, {1, 4}};
                Section sec(f, t);
                /*
                {pt:(2/1, 1/1) tl:(1, 1)}
                {pt:(2/1, 1/1) tl:(2, 1)}
                {pt:(2/1, 2/1) tl:(2, 1)}
                {pt:(2/1, 2/1) tl:(2, 2)}
                {pt:(2/1, 3/1) tl:(2, 2)}
                {pt:(2/1, 3/1) tl:(2, 3)}
                {pt:(2/1, 4/1) tl:(2, 3)}
                {pt:(2/1, 4/1) tl:(1, 4)}
                */

        prnt_trajectory(sec.get_trajectory());
                assert(sec.is_reachable());
            }
            {
                Crossroad t{{2, 5}, {1, 4}};
                Section sec(f, t);
                assert(sec.is_reachable());
            }
            {
                Crossroad t{{1, 4}, {1, 4}};
                Section sec(f, t);
                assert(!sec.is_reachable());
            }
            {
                Crossroad t{{1, 5}, {1, 4}};
                Section sec(f, t);
                assert(!sec.is_reachable());
            }
          }

          {
            // same vertical line along border, different point
            Crossroad f{{2, 2}, {1, 1}};
            {
                Crossroad t{{2, 4}, {1, 4}};
                Section sec(f, t);
                //{pt:(2/1, 2/1) tl:(1, 1)}
                //{pt:(2/1, 2/1) tl:(2, 2)}
                //{pt:(2/1, 3/1) tl:(2, 2)}
                //{pt:(2/1, 3/1) tl:(2, 3)}
                //{pt:(2/1, 4/1) tl:(2, 3)}
                //{pt:(2/1, 4/1) tl:(1, 4)}

                assert(sec.is_reachable());
            }
            {
                Crossroad t{{2, 5}, {1, 4}};
                Section sec(f, t);
                assert(sec.is_reachable());
            }
            {
                Crossroad t{{1, 4}, {1, 4}};
                Section sec(f, t);
                assert(!sec.is_reachable());
            }
            {
                Crossroad t{{1, 5}, {1, 4}};
                Section sec(f, t);
                assert(!sec.is_reachable());
            }
          }
        }

        //prnt_trajectory(sec.get_trajectory());

        std::cout << "--------------" << std::endl;
        assert(cover::reachless == check_cover(Tile{1, 1}, Tile{1, 4}));

        std::cout << check_cover(Tile{2, 2}, Tile{1, 4}) << std::endl;
        assert(cover::partial == check_cover(Tile{2, 2}, Tile{1, 4}));

//        assert(cover::no == check_cover(Tile{5, 1}, Tile{5, 4}));
        std::cout << check_cover(Tile{10, 1}, Tile{9, 3}) << std::endl;
        //assert(cover::reachless == check_cover(Tile{10, 1}, Tile{9, 3}));

        std::cout << check_cover(Tile{11, 1}, Tile{9, 3}) << std::endl;
        //assert(cover::reachless == check_cover(Tile{11, 1}, Tile{9, 3}));
    }
    return 0;
}

