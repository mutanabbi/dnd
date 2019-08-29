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
#include <iostream> /// @todo DEBUG ONLY

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

    using boost::rational_cast;
    // Get trajectory
    std::vector<Crossroad> crossroads = get_trajectory();
    assert(size(crossroads) > 1);
    for (
        auto it = make_intersect_iterator(begin(crossroads))
      , last = make_intersect_iterator(end(crossroads))
      ; it != last
      ; ++it
    )
    {
        // TODO: DEBUG ONLY
        auto prnt_trajectory = [&cout = std::cout](const auto& vec) {
            cout << "[";
            for (const auto& c : vec)
                cout << c << " | ";
            (cout << "]\n").flush();
        };
        prnt_trajectory(crossroads);

        auto& f = std::get<0>(*it);
        auto& t = std::get<1>(*it);
        assert(
            1 == f.point.x.denominator()
          || 1 == f.point.y.denominator()
        );

        // diagonal step
        if (f.tile.x != t.tile.x && f.tile.y != t.tile.y)
        {
            if (is_tile_occupied(t.tile))
                return false;
            else if (
                is_tile_occupied({f.tile.x, t.tile.y})
              && is_tile_occupied({f.tile.y, t.tile.x})
              ) return false;
        }

        // horizontal step
        if (f.tile.x != t.tile.x)
        {
            assert(1 == t.point.x.denominator());
            if (
                1 == t.point.y.denominator() // point lies on a vertical border btn tiles
              && is_tile_occupied(t.tile) // destinition tile is occupied
              && line().is_horizontal()
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

                // TODO: DEBUG ONLY
                std::cout << "alt:" << alt_t << std::endl;
                t.tile = alt_t;
            }
        }

        // vertical step
        if (f.tile.y != t.tile.y)
        {
            assert(1 == t.point.y.denominator());
            if (
                1 == t.point.x.denominator() // point lies on a horizontal border btn tiles
              && is_tile_occupied(t.tile) // destinition tile is occupied
              && line().is_vertical()
            )
            {
                // try to find alternative way
                assert(boost::rational_cast<unsigned>(t.point.x) >= t.tile.x);
                int delta = boost::rational_cast<unsigned>(t.point.x) - t.tile.x;
                assert((delta + static_cast<int>(t.tile.x)) >= 0);
                auto alt_t = Tile{
                    t.tile.x + delta
                  , t.tile.y
                };
                if (is_tile_occupied(alt_t))
                    return false;

                // TODO: DEBUG ONLY
                std::cout << "alt:" << alt_t << std::endl;
                t.tile = alt_t;
            }
        }
    } // for
    return true;

#if 0
    using boost::rational_cast;
    // Get trajectory
    std::vector<Coordinate> crosspoints = get_trajectory(
        rational_cast<unsigned>(m_from.point.x)
      , rational_cast<unsigned>(m_from.point.y)
      , rational_cast<unsigned>(m_to.point.x)
      , rational_cast<unsigned>(m_to.point.y)
      , m_line
    );

    // Check trajectory
    for (const auto pt : crosspoints)
    {
        auto x = rational_cast<unsigned>(pt.x);
        auto y = rational_cast<unsigned>(pt.y);
        if (1 == pt.x.denominator() && 1 == pt.y.denominator())
        {
            assert(x >= 0);
            assert(y >= 0);
            unsigned hits = 0;

            /// @todo It would be great to find a way how to bring an order to this mess
            hits += (is_tile_occupied({x, y}) ? 1 : 0);

            if (x > 0)
            {
                hits += (is_tile_occupied({x - 1, y}) ? 1 : 0);
                if (y > 0)
                    hits += (is_tile_occupied({x - 1, y - 1}) ? 1 : 0);
            }

            if (y > 0)
                hits += (is_tile_occupied({x, y - 1}) ? 1 : 0);

            if (hits > 1)
                return false;
        }
        else if (1 == pt.x.denominator())
        {
            unsigned hits = 0;
            hits += (is_tile_occupied({x, y}) ? 1 : 0);

            if (x > 0)
                hits += (is_tile_occupied({x - 1, y}) ? 1 : 0);

            if (hits > 0)
                return false;
        }
        else if (1 == pt.y.denominator())
        {
            unsigned hits = 0;
            hits += (is_tile_occupied({x, y}) ? 1 : 0);

            if (y > 0)
                hits += (is_tile_occupied({x, y - 1}) ? 1 : 0);

            if (hits > 0)
                return false;
        }
    }
    return true;
#endif
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

            // TODO: DEBUG ONLY
            // std::cout << "pt:" << pt << " f:" << f << " t:" << t << "ct: " << ct << std::endl;

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

#if 0
    /// @todo If size(v) == 0 it works incorrectly
    crossroads = std::accumulate(
        next(cbegin(v))
      , cend(v)
      , std::move(crossroads)
      , [](std::vector<Crossroad> c, const Coordinate& pt) {
            assert(pt.x >= 0);
            assert(pt.y >= 0);

            Tile prev_tile = c.back().tile;
            Tile cur_tile = prev_tile;
            Coordinate prev_pt = c.back().point;

            /*
            if (c.back().point != pt)
                c.emplace_back(pt, cur_tile);               // do not cross tile border at first time

            // do not cross tile boreder on last tile
            if (c.back().tile == last_tile)
            {
                assert(c.back().point == pt);
                return c;
            }
            */

            using boost::rational_cast;

            if (!is_belong(prev_tile, pt))
            {
            cur_tile.x = rational_cast<unsigned>(std::min(prev_pt.x, pt.x));
            cur_tile.y = rational_cast<unsigned>(std::min(prev_pt.y, pt.y));
                /*
                if (1 == prev_pt.x.denominator())           // choose left or right tile
                {
                    if (prev_pt.x < pt.x)                   // left to right trajectory direction
                    {
                        // choose right tile
                        //cur_tile.x += 1;
                        //next_tile.x = rational_cast<unsigned>(pt.x);
                        cur_tile.x += 1;
                        //assert(prev_tile.x == next_tile.x - 1);
                    }
                    else if (pt.x < prev_pt.x)              // right to left trajectory direction
                    {
                        // choose left tile
                        //assert(pt.x > 0);
                        //assert(cur_tile.x > 0);
                        //cur_tile.x -= 1;
                        assert(cur_tile.x > 0);
                        cur_tile.x -= 1;
                        //next_tile.x = rational_cast<unsigned>(pt.x) - 1;
                        //assert(prev_tile.x - 1 == next_tile.x);
                    }
                    // else
                        //assert(prev_tile.y != rational_cast<unsigned>(pt.y));
                        // vertical trajectory
                        // next_tile.x = prev_tile.x
                }

                if (1 == prev_pt.y.denominator())           // choose top or bottom tile
                {
                    if (prev_pt.y < pt.y)                   // bottom to top trajectory direction
                    {
                        // choose top tile
                        //cur_tile.y += 1;
                        cur_tile.y += 1;
                        //next_tile.y = rational_cast<unsigned>(pt.y);
                        //assert(prev_tile.y == next_tile.y - 1);
                    }
                    else if (pt.y < prev_pt.y)              // top to bottom trajectory direction
                    {
                        // choose bottom tile
                        //assert(pt.y > 0);
                        //assert(cur_tile.y > 0);
                        //cur_tile.y -= 1;
                        assert(cur_tile.y > 0);
                        cur_tile.y -= 1;
                        //next_tile.y = rational_cast<unsigned>(pt.y) - 1;
                        //assert(prev_tile.y - 1 == next_tile.y);
                    }
                    // else
                        //assert(prev_tile.x != rational_cast<unsigned>(pt.x));
                        // horisontal trajectory
                        // next_tile.y = prev_tile.y
                }
                */

                //assert(prev_tile != cur_tile);
                // assert(cur_tile != next_tile);
                // assert(is_belong(cur_tile, prev_pt));
                //assert(is_belong(cur_tile, pt));
                assert(is_belong(cur_tile, prev_pt));
                c.emplace_back(prev_pt, cur_tile);          //????
            }

            assert(is_belong(cur_tile, pt));
            c.emplace_back(pt, cur_tile);

            /*
            // but cross tile borders at second time
            c.emplace_back(pt, next_tile);                  // ?????
            */
            return c;
        }
    );
    /// @todo Do I need this condition? Check w/ assert
    if (crossroads.back() != to())
        crossroads.emplace_back(to());
    return crossroads;
#endif
}









































































































































