#pragma once

#include "Coordinate.hpp"
#include "Tile.hpp"
#include <ostream>
#include <cassert>


/// @todo rename
struct Crossroad
{
    Crossroad(const Coordinate& pt, const Tile& t)
      : point(pt), tile(t)
    {
        /// @todo throw
        // Validate the tile really has the point
        assert(tile.contains(point));
    }
    /// @todo getters
    Coordinate point;
    Tile tile;
};

inline bool operator==(const Crossroad& lhv, const Crossroad& rhv)
{
    return lhv.point == rhv.point && lhv.tile == rhv.tile;
}

inline bool operator!=(const Crossroad& lhv, const Crossroad& rhv)
{
    return ! (lhv == rhv);
}

inline std::ostream& operator<<(std::ostream& os, const Crossroad& v)
{
    return os << "{pt:" << v.point << " tl:" << v.tile << "}";
}

