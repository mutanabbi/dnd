#pragma once

#include "Crossroad.hpp"
#include "Section.hpp"
#include "Tile.hpp"
#include "Coordinate.hpp"

#include <ostream>
#include <algorithm>
#include <cassert>

enum class cover : unsigned char
{
    no, partial, total, reachless
};

inline std::ostream& operator<<(std::ostream& os, const cover& v)
{
    switch (v)
    {
    case cover::no:
        return os << "no";
    case cover::partial:
        return os << "partial";
    case cover::total:
        return os << "total";
    case cover::reachless:
        return os << "reachless";
    };
    return os;
}

inline cover check_cover(const Crossroad& from, const Tile& to)
{
    std::array<Section, 4> sections = {
        Section{from, Crossroad{{to.x, to.y}, to}},
        Section{from, Crossroad{{to.x + 1, to.y}, to}},
        Section{from, Crossroad{{to.x, to.y + 1}, to}},
        Section{from, Crossroad{{to.x + 1, to.y + 1}, to}}
    };
    std::sort(
        begin(sections)
      , end(sections)
      , [](const Section& lhv, const Section& rhv) {
            // note this isn't real length. It's rather value that proportional
            // to length. Real formula to get lenght would be sqrt(pow(abs(dx),2) + (pow(abs(dy),2))
            // but sqrt operation isn't defined for rational numbers as well as
            // we don't need exact lenth here. So we can simplify calculations
            auto length = [] (const Coordinate& a, const Coordinate b) {
                return abs(a.x - b.x) + abs(a.y - b.y);
            };
            return length(lhv.from().point, lhv.to().point)
              < length(lhv.from().point, rhv.to().point);
      }
    );
    // Note unique is stable, so as soon as lines is softed in order
    // of sections' lengths we have shortest unique ones after this call
    auto uniq_end = std::unique(
        begin(sections)
      , end(sections)
      , [](const Section& lhv, const Section& rhv) {
            return lhv.line() == rhv.line();
      }
    );
    auto n = std::distance(begin(sections), uniq_end);
    assert(n > 2 && n < 5 && "It's possible to have 3 or 4 unique lines only");

    unsigned hits = std::accumulate(
        begin(sections)
      , uniq_end
      , 0
      , [](unsigned acum, const Section& sec) {
            return acum + (sec.is_reachable() ? 1 : 0);
      }
    );

    assert(hits < 5);
    switch (hits)
    {
    case 2:
        return cover::total;
    case 3:
        return 3 == n ? cover::no : cover::partial;
    case 4:
        assert(4 == n);
        return cover::no;

    case 0:
    case 1:
    default:
        ; // Suppress compiler warning
    };
    return cover::reachless;
}

inline cover check_cover(Tile from, Tile to)
{
    cover result = cover::reachless;

    if (from == to)
        return cover::no;

    for (auto fx = from.x; fx <= from.x + 1; ++fx)
        for (auto fy = from.y; fy <= from.y + 1; ++fy)
            if (cover::no == (result = std::min(
                check_cover(Crossroad{{fx, fy}, from}, to)
              , result
            ))) return result;

    return result;
}

