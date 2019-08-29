#include "../Trajectory.hpp"
#include "../Coordinate.hpp"
#include <iostream>
#include <vector>
#include <cassert>


std::ostream& operator<<(std::ostream& os, const std::vector<Coordinate>& v)
{
    os << "[";
    for (const auto& pt : v)
        os << pt << ", ";
    return os << "]";
}

int main(int /*argc*/, char* /*argv*/[])
{
    // test trajectory value and ordering
    {
        using sample = std::vector<Coordinate>;
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

    {
        using sample = std::vector<Coordinate>;
        using rt = boost::rational<int>;
        auto f = [](const auto& tpl) {
            return std::apply(
                static_cast<std::vector<Coordinate>(*)(unsigned, unsigned, unsigned, unsigned)>(get_trajectory)
              , tpl
            );
        };
        auto r = [](const auto& tpl) {
            using namespace std;
            return apply(
                static_cast<vector<Coordinate>(*)(unsigned, unsigned, unsigned, unsigned)>(get_trajectory)
              , make_tuple(get<2>(tpl), get<3>(tpl), get<0>(tpl), get<1>(tpl))
            );
        };
        auto i = [](auto vec) {
            std::reverse(begin(vec), end(vec));
            return vec;
        };

        // point to itself
        {
        auto args = std::make_tuple(0u, 0u, 0u, 0u);
        auto rslt = f(args);
        auto expect = sample{{0, 0}};
        assert(expect == rslt);
        }
        {
        auto args = std::make_tuple(42, 42, 42, 42);
        auto rslt = f(args);
        auto expect = sample{{42, 42}};
        assert(expect == rslt);
        }

        // bottom left to top right
        {
        auto args = std::make_tuple(0u, 0u, 1u, 1u);
        auto expect = sample{{0, 0}, {1, 1}};
        auto rslt = f(args);
        assert(expect == rslt);
        assert(r(args) == i(rslt));
        }
        {
        auto args = std::make_tuple(0, 0, 2, 2);
        auto expect = sample{{0, 0}, {1, 1}, {2, 2}};
        auto rslt = f(args);
        assert(rslt == expect);
        assert(r(args) == i(rslt));
        }
        {
        auto args = std::make_tuple(0, 0, 3, 3);
        auto expect = sample{{0, 0}, {1, 1}, {2, 2}, {3, 3}};
        auto rslt = f(args);
        assert(rslt == expect);
        assert(r(args) == i(rslt));
        }
        {
        auto args = std::make_tuple(2, 0, 3, 2);
        auto expect = sample{{2, 0}, {rt(5)/2, 1}, {3, 2}};
        auto rslt = f(args);
        assert(rslt == expect);
        assert(r(args) == i(rslt));
        }
        {
        auto args = std::make_tuple(2, 0, 3, 3);
        auto rslt = f(args);
        auto expect = sample{{2, 0}, {rt(7)/3, 1}, {rt(8)/3, 2}, {3, 3}};
        assert(rslt == expect);
        assert(r(args) == i(rslt));
        }
        {
        auto args = std::make_tuple(2, 0, 4, 3);
        auto rslt = f(args);
        auto expect = sample{{2, 0}, {rt(8)/3, 1}, {3, rt(3)/2}, {rt(10)/3, 2}, {4, 3}};
        assert(rslt == expect);
        assert(r(args) == i(rslt));
        }

        // top left to bottom right
        {
        auto args = std::make_tuple(2, 3, 4, 0);
        auto rslt = f(args);
        auto expect = sample{{2, 3}, {rt(8)/3, 2}, {3, rt(3)/2}, {rt(10)/3, 1}, {4, 0}};
        assert(rslt == expect);
        assert(r(args) == i(rslt));
        }
        {
        auto args = std::make_tuple(2, 3, 4, 1);
        auto rslt = f(args);
        auto expect = sample{{2, 3}, {3, 2}, {4, 1}};
        assert(rslt == expect);
        assert(r(args) == i(rslt));
        }
        {
        auto args = std::make_tuple(2, 3, 4, 2);
        auto rslt = f(args);
        auto expect = sample{{2, 3}, {3, rt(5)/2}, {4, 2}};
        assert(rslt == expect);
        assert(r(args) == i(rslt));
        }
        {
        auto args = std::make_tuple(2, 3, 3, 0);
        auto rslt = f(args);
        auto expect = sample{{2, 3}, {rt(7)/3, 2}, {rt(8)/3, 1}, {3, 0}};
        assert(rslt == expect);
        assert(r(args) == i(rslt));
        }
        {
        auto args = std::make_tuple(2, 3, 3, 1);
        auto rslt = f(args);
        auto expect = sample{{2, 3}, {rt(5)/2, 2}, {3, 1}};
        assert(rslt == expect);
        assert(r(args) == i(rslt));
        }
        {
        auto args = std::make_tuple(2, 3, 3, 2);
        auto rslt = f(args);
        auto expect = sample{{2, 3}, {3, 2}};
        assert(rslt == expect);
        assert(r(args) == i(rslt));
        }

        // vertical line
        {
        auto args = std::make_tuple(2, 0, 2, 5);
        auto rslt = f(args);
        auto expect = sample{{2, 0}, {2, 1}, {2, 2}, {2, 3}, {2, 4}, {2, 5}};
        assert(rslt == expect);
        assert(r(args) == i(rslt));
        }

        // horisontal line
        {
        auto args = std::make_tuple(1, 4, 7, 4);
        auto rslt = f(args);
        auto expect = sample{{1, 4}, {2, 4}, {3, 4}, {4, 4}, {5, 4}, {6, 4}, {7, 4}};
        assert(rslt == expect);
        assert(r(args) == i(rslt));
        }
    }

    return 0;
}
