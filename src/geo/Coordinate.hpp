#pragma once

#include <boost/rational.hpp>
#include <ostream>

struct Coordinate
{
    Coordinate(
        boost::rational<int> xv
      , boost::rational<int> yv
    ) : x(xv), y(yv)
    {}
    boost::rational<int> x;
    boost::rational<int> y;
};

inline bool operator==(const Coordinate& lhv, const Coordinate& rhv)
{
    return lhv.x == rhv.x && lhv.y == rhv.y;
}

inline bool operator!=(const Coordinate& lhv, const Coordinate& rhv)
{
    return !(lhv == rhv);
}

inline std::ostream& operator<<(std::ostream& os, const Coordinate& v)
{
    return os << "(" << v.x << ", " << v.y << ")";
}

