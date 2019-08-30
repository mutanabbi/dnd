#pragma once

#include "Crossroad.hpp"
#include "Trajectory.hpp"
#include "Tile.hpp"
#include "Line.hpp"
#include "intersect_iterator.hpp"

#include <boost/rational.hpp>

#include <vector>
#include <numeric>
#include <algorithm>
#include <utility>
#include <cassert>
//#include <iostream> /// @todo DEBUG ONLY

class Section
{
    static Line get_line(const Crossroad& f, const Crossroad& t)
    {
        /** @todo throw or get rid of line() getter
         * to make every Crossroad riachable from itself
         * (you can't buid the line in that case
         */
        assert(f != t);

        if (f.point != t.point)
          return Line(f.point, t.point);

        using std::max, std::min;
        unsigned dx = max(f.tile.x, t.tile.x) - min(f.tile.x, t.tile.x);
        unsigned dy = max(f.tile.y, t.tile.y) - min(f.tile.y, t.tile.y);
        assert(dx == 0 || dx == 1);
        assert(dy == 0 || dy == 1);
        using rt = boost::rational<int>;
        return Line(f.point, {f.point.x + rt(dx), f.point.y + rt(dy)});
    }

public:
    Section(const Crossroad& f, const Crossroad& t) noexcept
      : m_from(f), m_to(t), m_line(get_line(m_from, m_to))
    {
    }

    bool is_reachable() const;                              //!< @todo proper name
    std::vector<Crossroad> get_trajectory() const;          //!< @todo private?

    const Crossroad& from() const { return m_from; }
    const Crossroad& to() const { return m_to; }
    const Line& line() const { return m_line; }

private:
    Crossroad m_from;
    Crossroad m_to;
    Line m_line;
};                                                          // class Section


inline bool Section::is_reachable() const
{
    /** @todo Too strong assertments. Current programm use these constraints, but
     *  they aren't true in general case. Get rid of this
     */
    assert(1 == m_from.point.x.denominator());
    assert(1 == m_from.point.y.denominator());
    assert(1 == m_to.point.x.denominator());
    assert(1 == m_to.point.y.denominator());
    assert(m_from.point.x >= 0);
    assert(m_from.point.y >= 0);
    assert(m_to.point.x >= 0);
    assert(m_to.point.y >= 0);

    if (is_tile_occupied(m_to.tile) || is_tile_occupied(m_from.tile))
        return false;

    // Get trajectory
    std::vector<Crossroad> crossroads = get_trajectory();

    assert(size(crossroads) > 1);
    assert(!is_tile_occupied(crossroads.back().tile));

    using boost::rational_cast;

    for (
        auto it = make_intersect_iterator(begin(crossroads))
      , last = make_intersect_iterator(end(crossroads))
      ; it != last
      ; ++it
    )
    {
        // TODO: DEBUG ONLY
        /*
        auto prnt_trajectory = [&cout = std::cout](const auto& vec) {
            cout << "[";
            for (const auto& c : vec)
                cout << c << " | ";
            (cout << "]\n").flush();
        };
        prnt_trajectory(crossroads);
        */

        auto [f, t] = *it;
        assert(
            1 == f.point.x.denominator()
          || 1 == f.point.y.denominator()
        );
        assert(
            1 == t.point.x.denominator()
          || 1 == t.point.y.denominator()
        );

        if (f.point != t.point) // same points == different tiles
        {
            // here we sure f and t share a tile
            assert(f.tile == t.tile);

            if (is_tile_occupied(f.tile))
            {
                /// @todo Get rid of copypaste
                if (
                    line().is_horizontal()
                  && 1 == f.point.y.denominator()
                )
                {
                    // try to find alternative way
                    assert(boost::rational_cast<unsigned>(t.point.y) >= t.tile.y);
                    int delta = (boost::rational_cast<unsigned>(t.point.y) - t.tile.y) ? 1 : -1;
                    assert((delta + static_cast<int>(t.tile.y)) >= 0);
                    auto alt_t = Tile{
                        t.tile.x
                      , t.tile.y + delta
                    };
                    if (is_tile_occupied(alt_t))
                        return false;
                }
                else if (
                    line().is_vertical()
                  && 1 == f.point.x.denominator()
                )
                {
                    // try to find alternative way
                    assert(boost::rational_cast<unsigned>(t.point.x) >= t.tile.x);
                    int delta = (boost::rational_cast<unsigned>(t.point.x) - t.tile.x ? 1 : -1);
                    assert((delta + static_cast<int>(t.tile.x)) >= 0);
                    auto alt_t = Tile{
                        t.tile.x + delta
                      , t.tile.y
                    };
                    if (is_tile_occupied(alt_t))
                        return false;
                }
                else
                    return false;
            } // end if current tile occupied
        } // end if f and t share a current tile
        else if (
            1 == f.point.x.denominator()
          && 1 == f.point.y.denominator()
        ) // diagonal throught a node
        {
            assert(f.tile != t.tile);
            if (
                is_tile_occupied({f.tile.x, t.tile.y})
              && is_tile_occupied({f.tile.y, t.tile.x})
            )
                return false;
        }
    } // for
    return true;
}

inline std::vector<Crossroad> Section::get_trajectory() const
{
    auto v = ::get_trajectory(from().point, to().point, line());
    assert(size(v) > 0);
    assert(v.front() == from().point);
    assert(from() != to());

    if (1 == size(v))
    {
        assert(from().tile.contains(v.back()));
        assert(to().tile.contains(v.back()));
        return {from(), to()};
    }

    std::vector<Crossroad> crossroads;
    crossroads.reserve(size(v) * 2);
    crossroads.emplace_back(from());

    /// @todo Test intersect_iterator for this case (size < N). There is a bug
    crossroads = std::accumulate(
        make_intersect_iterator(cbegin(v))
      , make_intersect_iterator(cend(v))
      , std::move(crossroads)
      , [](std::vector<Crossroad> c, const auto& tpl) {
            auto& [f, t] = tpl; // from, to coordinates

            assert(f.x >= 0);
            assert(f.y >= 0);
            assert(t.x >= 0);
            assert(t.y >= 0);

            assert(f != t);
            assert(1 >= (std::max(f.x, t.x) - std::min(f.x, t.x)));
            assert(1 >= (std::max(f.y, t.y) - std::min(f.y, t.y)));

            auto detect_tile = [](
                const Tile pt
              , const Coordinate& t
            ) {
                using boost::rational_cast;
                Tile ct = pt;
                ct.x =
                    t.x > pt.x + 1 ? pt.x + 1
                  : t.x < pt.x ? pt.x - 1
                  : pt.x;
                ct.y =
                    t.y > pt.y + 1 ? pt.y + 1
                  : t.y < pt.y ? pt.y - 1
                  : pt.y;
                return ct;
            };

            auto ct = detect_tile(c.back().tile, t);
            auto& pt = c.back().tile;                       // prev tile;

            assert(pt.contains(f));
            assert(ct.contains(f));

            //if (pt.contains(f) && pt != ct)
            if (pt != ct)
                c.emplace_back(f, ct);

            c.emplace_back(t, ct);

            return c;
    });

    if (crossroads.back() != to())
        crossroads.emplace_back(to());
    return crossroads;
}
