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
            assert(lhv.from() == rhv.from());
            // note this isn't real length. It's rather value that proportional
            // to length. Real formula to get lenght would be sqrt(pow(abs(dx),2) + (pow(abs(dy),2))
            // but sqrt operation isn't defined for rational numbers as well as
            // we don't need exact lenth here. So we can simplify calculations
            auto length = [] (const Coordinate& a, const Coordinate b) {
                return abs(a.x - b.x) + abs(a.y - b.y);
            };
            return std::make_tuple(
                lhv.line().a()
              , lhv.line().b()
              , lhv.line().c()
              , length(lhv.from().point, lhv.to().point)
            ) < std::make_tuple(
                rhv.line().a()
              , rhv.line().b()
              , rhv.line().c()
              , length(rhv.from().point, rhv.to().point)
            );
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

    auto reachable_end = std::remove_if(
        begin(sections)
      , uniq_end
      , [](const Section& sec) {
            return !sec.is_reachable();
      }
    );

    unsigned hits = std::distance(begin(sections), reachable_end);

    assert(hits < 5);
    switch (hits)
    {
    case 2:
        return uniq_end != cend(sections)
            && uniq_end->line() == reachable_end->line()
            ? cover::partial
            : cover::total;
    case 3:
        return uniq_end != cend(sections) ? cover::no : cover::partial;
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

