#pragma once

#include "Line.hpp"
#include "Coordinate.hpp"

#include <boost/rational.hpp>

#include <vector>
#include <tuple>
#include <algorithm>
#include <cmath>
#include <cassert>


inline std::vector<Coordinate> get_trajectory(
    unsigned fxv
  , unsigned fyv
  , unsigned txv
  , unsigned tyv
  , Line ln
)
{
    unsigned fx, fy, tx, ty;
    std::tie(fx, tx) = std::minmax(fxv, txv);
    std::tie(fy, ty) = std::minmax(fyv, tyv);

    std::vector<Coordinate> crosspoints;
    crosspoints.reserve(std::fdim(tx, fx) + std::fdim(ty, fy));
    using boost::rational_cast;
    // Get trajectory
    for (auto x = fx; x <= tx; ++x)
    {
        auto y = ln.x2y(x);
        if (!y)
            break;
        assert(*y >= 0);
        //std::cout << "x:" << x << " -> y:" << *y << std::endl;
        crosspoints.emplace_back(Coordinate{x, *y});
    }
    for (auto y = fy; y <= ty; ++y)
    {
        auto x = ln.y2x(y);
        if (!x)
            break;
        assert(*x >= 0);
        //std::cout << "x:" << *x << " <- y:" << y << std::endl;
        crosspoints.emplace_back(Coordinate{*x, y});
    }

    std::sort(
        begin(crosspoints)
      , end(crosspoints)
      , [fxv, fyv, txv, tyv](const auto& l, const auto& r) {
            /// @todo Move proper comparator choice out of lambda
            using std::tie;
            return
                fxv <  txv && fyv <  tyv ? tie(l.x, l.y) < tie(r.x, r.y) : // l bot -> r top;
                fxv <  txv && fyv >= tyv ? tie(l.x, r.y) < tie(r.x, l.y) : // l top -> r bot; l -> r
                fxv >= txv && fyv <  tyv ? tie(r.x, l.y) < tie(l.x, r.y) : // r bot -> l top;
              /*fxv >= txv && fyv >= tyv*/ tie(r.x, r.y) < tie(l.x, l.y) ; // r top -> l bot; top -> bot; r -> l
      }
    );
    crosspoints.erase(
        std::unique(begin(crosspoints), end(crosspoints))
      , cend(crosspoints)
    );

    return crosspoints;
}

inline std::vector<Coordinate> get_trajectory(
    const Coordinate& from
  , const Coordinate& to
  , const Line& line
)
{
    /// @todo Get rid of this
    assert(1 == from.x.denominator());
    assert(1 == from.y.denominator());
    assert(1 == to.y.denominator());
    assert(1 == to.x.denominator());
    assert(from.x >= 0);
    assert(from.y >= 0);
    assert(to.x >= 0);
    assert(to.y >= 0);
    auto rt = [] (const auto& v) { return boost::rational_cast<unsigned>(v); };
    return get_trajectory(rt(from.x), rt(from.y), rt(to.x), rt(to.y), line);
}

inline std::vector<Coordinate> get_trajectory(
    unsigned fxv
  , unsigned fyv
  , unsigned txv
  , unsigned tyv
)
{
    return std::tie(fxv, fyv) == std::tie(txv, tyv)
      ? std::vector<Coordinate>{{fxv, fyv}}
      : get_trajectory(fxv, fyv, txv, tyv, Line({fxv, fyv}, {txv, tyv}));
}
