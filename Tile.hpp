#pragma once

#include "Coordinate.hpp"
#include <ostream>

struct Tile
{
    unsigned x;
    unsigned y;
    bool contains(const Coordinate& pt) const;
};

inline bool operator==(const Tile& lhv, const Tile& rhv)
{
    return lhv.x == rhv.x && lhv.y == rhv.y;
}

inline bool operator!=(const Tile& lhv, const Tile& rhv)
{
    return !(lhv == rhv);
}

inline std::ostream& operator<<(std::ostream& os, const Tile& v)
{
    return os << "(" << v.x << ", " << v.y << ")";
}

inline bool Tile::contains(const Coordinate& pt) const
{
    assert(pt.x >= 0);
    assert(pt.y >= 0);
    auto ptx = boost::rational_cast<unsigned>(pt.x);
    auto pty = boost::rational_cast<unsigned>(pt.y);
    return ptx >= this->x && ptx <= (this->x + 1)
      && pty >= this->y && pty <= (this->y + 1);
}

/// @todo Get rid of this. Use dependency injection or something
inline bool is_tile_occupied(Tile t)
{
    static Tile a[] = {
        {0, 5}
      , {1, 2}
      , {1, 3}
      , {1, 5}
      , {2, 5}
      , {4, 2}
      , {4, 3}
      , {6, 2}
      , {6, 3}
      , {9, 2}
      , {10, 3}
      , {14, 2}
    };
    using namespace std;
    return end(a) != find(begin(a), end(a), t);
}
