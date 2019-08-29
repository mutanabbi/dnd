#pragma once

#include "Coordinate.hpp"

#include <boost/rational.hpp>
#include <boost/math/common_factor_rt.hpp>

#include <ostream>
#include <optional>
#include <cassert>


class Line
{
    void denominate()
    {
        /** @todo Solve the problem of zero a,b. In some cases gcd
         *  can just do division w/t any checks (in case if a or b are
         *  <code> numeric_limits<>::min() </code> but not equal to zero
         *  <code> boost::math::gcd<int>(std::numeric_limits<int>::min(), 0) </code>
         *  crushes w/ "SIGFPE, Arithmetic exception", for example
         *  Bug report?
         */
        // greatest common divisor
        /** @todo the form \c boost::math::gcd(m_a, m_b, m_c) could be possible
         *  but due a conflict gcd declarations between \c boost::integer and
         *  \c boost::rational it causes compile error (ambigious call)
         *  Bug report?
         */
        auto result = m_b == 0 ? m_a : m_a == 0 ? m_b : boost::math::gcd(m_a, m_b);
        result = boost::math::gcd(m_c, result);
        // normalize a,b,c
        m_a /= result;
        m_b /= result;
        m_c /= result;
    }

public:
    using rtnl = boost::rational<int>;

    Line(rtnl a, rtnl b, rtnl c) noexcept
      : m_a(a), m_b(b), m_c(c)
    {
        /// @todo throw an exception.  (two equal points)
        assert(m_a != 0 || m_b != 0);
        denominate();
    }

    Line(const Coordinate& p1, const Coordinate& p2) noexcept
      : Line(p1.y - p2.y, p2.x - p1.x, p1.x * p2.y - p2.x * p1.y)
    {
        assert((p1 != p2) && "It's not possible to build the line by one point. a == b == 0 in that case");
    }

    /// @note Result is undefined if b == 0
    std::optional<rtnl> x2y(rtnl x) const
    {
        if (m_b)
            return - (m_a * x + m_c) / m_b;
        return std::nullopt;
    }
    /// @note Result is undefined if a == 0
    std::optional<rtnl> y2x(rtnl y) const
    {
        if (m_a)
            return - (m_b * y + m_c) / m_a;
        return std::nullopt;
    }

    bool is_horizontal() const { return m_a == 0; }
    bool is_vertical() const { return m_b == 0; }

    rtnl a() const { return m_a; }
    rtnl b() const { return m_b; }
    rtnl c() const { return m_c; }

    bool contains(const Coordinate& pt) const
    {
        return m_b != 0
          ? x2y(pt.x) == pt.y
          : y2x(pt.y) == pt.x
        ;
    }

    friend bool operator==(const Line& lhv, const Line& rhv)
    {
#       if 0
        // note a,b,c could be different between two equal lines (if no
        // denomination been occured). In that case we could just chek two
        // arbitrary points belong to both lines. It means they are the same,
        // no matter a linear equation. But it must be done w/ respect to
        // the fact a or b coult be equal to 0. Also it's important to keep an
        // eye we check two actully different points.
        auto f = m_b != 0 ? &Line::x2y : & Line::y2x
        return (lhv.m_a * rhv.m_a) &&
            (lhv.*f)(0) == (rhv.*f)(0)
          && (lhv.*f)(42) == (rhv.*f)(42);
#       endif
        return lhv.m_a == rhv.m_a
          && lhv.m_b == rhv.m_b
          && lhv.m_c == rhv.m_c;
    }

    /// @todo Debug only
    friend std::ostream& operator<<(std::ostream& os, const Line& v)
    {
        return os << "{a: " << v.m_a << ", b:" << v.m_b << ", c: " << v.m_c << "}";
    }

private:
    rtnl m_a;
    rtnl m_b;
    rtnl m_c;
};                                                          // class Line

inline bool operator!=(const Line& lhv, const Line& rhv)
{
    return ! (lhv == rhv);
}

