#include <geo/Crossroad.hpp>
#include <geo/Section.hpp>
#include <geo/Coverage.hpp>
#include <gtest/gtest.h>

//#include <iostream>

/// @todo Useful but not utilized tool
/*
template <typename T, std::size_t... I>
auto reverse_tuple_impl(T&& t, std::index_sequence<I...>)
{
    return std::make_tuple(
        std::get<sizeof...(I) - I -1>(std::forward<T>(t))...
    );
}

template <typename T>
auto reverse_tuple(T&& t)
{
    return reverse_tuple_impl(
        std::forward<T>(t)
      , std::make_index_sequence<
            std::tuple_size<
                typename std::remove_reference<T>::type
            >::value
        >{}
    );
}
*/

class section1_test : public ::testing::Test
{
protected:
    void SetUp() override
    {
        /*    +___+
         *   5|###|
         *   4|   |
         *   3| # |
         *   2| # |
         *   1|   |
         *   0|   |
         *    +---+
         *     012
         */
        ASSERT_TRUE (is_tile_occupied({1, 2}));
        ASSERT_TRUE (is_tile_occupied({1, 3}));

        ASSERT_FALSE(is_tile_occupied({0, 0}));
        ASSERT_FALSE(is_tile_occupied({0, 1}));
        ASSERT_FALSE(is_tile_occupied({0, 2}));
        ASSERT_FALSE(is_tile_occupied({0, 3}));
        ASSERT_FALSE(is_tile_occupied({0, 4}));
        ASSERT_TRUE (is_tile_occupied({0, 5}));

        ASSERT_FALSE(is_tile_occupied({1, 0}));
        ASSERT_FALSE(is_tile_occupied({1, 1}));
        ASSERT_TRUE (is_tile_occupied({1, 2}));
        ASSERT_TRUE (is_tile_occupied({1, 3}));
        ASSERT_FALSE(is_tile_occupied({1, 4}));
        ASSERT_TRUE (is_tile_occupied({1, 5}));

        ASSERT_FALSE(is_tile_occupied({2, 0}));
        ASSERT_FALSE(is_tile_occupied({2, 1}));
        ASSERT_FALSE(is_tile_occupied({2, 2}));
        ASSERT_FALSE(is_tile_occupied({2, 3}));
        ASSERT_FALSE(is_tile_occupied({2, 4}));
        ASSERT_TRUE (is_tile_occupied({2, 5}));
    }
};

class section3_test : public ::testing::Test
{
protected:
    void SetUp() override
    {
        /*    +____+
         *   5|    |
         *   4|    |
         *   3|  # |
         *   2| #  |
         *   1|    |
         *   0|    |
         *    +----+
         *     8901
         */
        ASSERT_FALSE(is_tile_occupied({8, 0}));
        ASSERT_FALSE(is_tile_occupied({8, 1}));
        ASSERT_FALSE(is_tile_occupied({8, 2}));
        ASSERT_FALSE(is_tile_occupied({8, 3}));
        ASSERT_FALSE(is_tile_occupied({8, 4}));
        ASSERT_FALSE(is_tile_occupied({8, 5}));

        ASSERT_FALSE(is_tile_occupied({9, 0}));
        ASSERT_FALSE(is_tile_occupied({9, 1}));
        ASSERT_TRUE (is_tile_occupied({9, 2}));
        ASSERT_FALSE(is_tile_occupied({9, 3}));
        ASSERT_FALSE(is_tile_occupied({9, 4}));
        ASSERT_FALSE(is_tile_occupied({9, 5}));

        ASSERT_FALSE(is_tile_occupied({10, 0}));
        ASSERT_FALSE(is_tile_occupied({10, 1}));
        ASSERT_FALSE(is_tile_occupied({10, 2}));
        ASSERT_TRUE (is_tile_occupied({10, 3}));
        ASSERT_FALSE(is_tile_occupied({10, 4}));
        ASSERT_FALSE(is_tile_occupied({10, 5}));

        ASSERT_FALSE(is_tile_occupied({11, 0}));
        ASSERT_FALSE(is_tile_occupied({11, 1}));
        ASSERT_FALSE(is_tile_occupied({11, 2}));
        ASSERT_FALSE(is_tile_occupied({11, 3}));
        ASSERT_FALSE(is_tile_occupied({11, 4}));
        ASSERT_FALSE(is_tile_occupied({11, 5}));
    }
};

class section4_test : public ::testing::Test
{
protected:
    void SetUp() override
    {
        /*    +___+
         *   5|   |
         *   4|   |
         *   3|   |
         *   2| # |
         *   1|   |
         *   0|   |
         *    +---+
         *  10+345
         */
        ASSERT_FALSE(is_tile_occupied({13, 0}));
        ASSERT_FALSE(is_tile_occupied({13, 1}));
        ASSERT_FALSE(is_tile_occupied({13, 2}));
        ASSERT_FALSE(is_tile_occupied({13, 3}));
        ASSERT_FALSE(is_tile_occupied({13, 4}));

        ASSERT_FALSE(is_tile_occupied({14, 0}));
        ASSERT_FALSE(is_tile_occupied({14, 1}));

        ASSERT_TRUE (is_tile_occupied({14, 2}));

        ASSERT_FALSE(is_tile_occupied({14, 3}));
        ASSERT_FALSE(is_tile_occupied({14, 4}));

        ASSERT_FALSE(is_tile_occupied({15, 0}));
        ASSERT_FALSE(is_tile_occupied({15, 1}));
        ASSERT_FALSE(is_tile_occupied({15, 2}));
        ASSERT_FALSE(is_tile_occupied({15, 3}));
        ASSERT_FALSE(is_tile_occupied({15, 4}));
    }
};


TEST_F(section3_test, diagonal1)
{
    Tile from{10, 2};
    EXPECT_EQ(cover::no, check_cover(from, {8, 0}));
    EXPECT_EQ(cover::no, check_cover(from, {8, 1}));
    EXPECT_EQ(cover::reachless, check_cover(from, {8, 2}));
    //
    /// @todo Wrong cover::no result
    //EXPECT_EQ(cover::reachless, check_cover(from, {8, 3}));
    //EXPECT_EQ(cover::reachless, check_cover(from, {8, 4}));
    //

    EXPECT_EQ(cover::no, check_cover(from, {9, 0}));
    EXPECT_EQ(cover::no, check_cover(from, {9, 1}));
    EXPECT_EQ(cover::reachless, check_cover(from, {9, 2}));
    //
    /// @todo Wrong cover::no result
    //EXPECT_EQ(cover::reachless, check_cover(from, {9, 3}));
    //EXPECT_EQ(cover::reachless, check_cover(from, {9, 4}));
    //

    EXPECT_EQ(cover::no, check_cover(from, {10, 0}));
    EXPECT_EQ(cover::no, check_cover(from, {10, 1}));
    EXPECT_EQ(cover::no, check_cover(from, from));
    EXPECT_EQ(cover::reachless, check_cover(from, {10, 3}));
    EXPECT_EQ(cover::reachless, check_cover(from, {10, 4}));

    EXPECT_EQ(cover::no, check_cover(from, {11, 0}));
    EXPECT_EQ(cover::no, check_cover(from, {11, 1}));
    EXPECT_EQ(cover::no, check_cover(from, {11, 2}));
    EXPECT_EQ(cover::no, check_cover(from, {11, 3}));
    EXPECT_EQ(cover::no, check_cover(from, {11, 4}));
}

TEST_F(section3_test, diagonal2)
{
    Tile from{11, 1};
    EXPECT_EQ(cover::no, check_cover(from, {8, 0}));
    EXPECT_EQ(cover::no, check_cover(from, {8, 1}));
    /// @todo Wront cover::total result
    //EXPECT_EQ(cover::partial, check_cover(from, {8, 2}));
    //
    /// @todo Wrong cover::no result
    //EXPECT_EQ(cover::reachless, check_cover(from, {8, 3}));
    //EXPECT_EQ(cover::reachless, check_cover(from, {8, 4}));
    //

    EXPECT_EQ(cover::no, check_cover(from, {9, 0}));
    EXPECT_EQ(cover::no, check_cover(from, {9, 1}));
    EXPECT_EQ(cover::reachless, check_cover(from, {9, 2}));
    //
    /// @todo Wrong cover::no result
    //EXPECT_EQ(cover::reachless, check_cover(from, {9, 3}));
    //EXPECT_EQ(cover::reachless, check_cover(from, {9, 4}));
    //

    EXPECT_EQ(cover::no, check_cover(from, {10, 0}));
    EXPECT_EQ(cover::no, check_cover(from, {10, 1}));
    EXPECT_EQ(cover::no, check_cover(from, {10, 2}));
    EXPECT_EQ(cover::reachless, check_cover(from, {10, 3}));
    /// @todo Wront cover::total result
    //EXPECT_EQ(cover::partial, check_cover(from, {10, 4}));

    EXPECT_EQ(cover::no, check_cover(from, {11, 0}));
    EXPECT_EQ(cover::no, check_cover(from, from));
    EXPECT_EQ(cover::no, check_cover(from, {11, 2}));
    EXPECT_EQ(cover::no, check_cover(from, {11, 3}));
    EXPECT_EQ(cover::no, check_cover(from, {11, 4}));
}

TEST_F(section3_test, ocuppied_to_itself)
{
    /// @todo Wrong cover::no result
    //EXPECT_EQ(cover::reachless, check_cover({9 , 2}, {9 , 2}));
    //EXPECT_EQ(cover::reachless, check_cover({10, 3}, {10, 3}));
    //
    EXPECT_EQ(cover::reachless, check_cover({9 , 2}, {10, 3}));
    EXPECT_EQ(cover::reachless, check_cover({10, 3}, {9 , 2}));
}

TEST_F(section4_test, simple1)
{
    Tile from{13, 1};
    EXPECT_EQ(cover::no, check_cover(from, from));
    EXPECT_EQ(cover::no, check_cover(from, {14, 1}));
    EXPECT_EQ(cover::no, check_cover(from, {15, 1}));
    EXPECT_EQ(cover::no, check_cover(from, {13, 2}));
    EXPECT_EQ(cover::no, check_cover(from, {13, 3}));

    EXPECT_EQ(cover::partial, check_cover(from, {14, 3}));
    EXPECT_EQ(cover::partial, check_cover(from, {15, 2}));

    EXPECT_EQ(cover::reachless, check_cover(from, {15, 3}));
}

TEST_F(section4_test, simple2)
{
    Tile from{14, 1};
    EXPECT_EQ(cover::no, check_cover(from, from));
    EXPECT_EQ(cover::no, check_cover(from, {13, 1}));
    EXPECT_EQ(cover::no, check_cover(from, {15, 1}));
    EXPECT_EQ(cover::no, check_cover(from, {13, 2}));
    EXPECT_EQ(cover::no, check_cover(from, {15, 2}));
    EXPECT_EQ(cover::no, check_cover(from, {13, 3}));
    EXPECT_EQ(cover::no, check_cover(from, {15, 3}));

    EXPECT_EQ(cover::reachless, check_cover(from, {14, 3}));
}

TEST_F(section4_test, simple3)
{
    Tile from{15, 1};
    EXPECT_EQ(cover::no, check_cover(from, from));
    EXPECT_EQ(cover::no, check_cover(from, {13, 1}));
    EXPECT_EQ(cover::no, check_cover(from, {14, 1}));
    EXPECT_EQ(cover::no, check_cover(from, {15, 2}));
    EXPECT_EQ(cover::no, check_cover(from, {15, 3}));

    EXPECT_EQ(cover::partial, check_cover(from, {13, 2}));
    EXPECT_EQ(cover::partial, check_cover(from, {14, 3}));

    EXPECT_EQ(cover::reachless, check_cover(from, {13, 3}));
}

TEST_F(section4_test, simple4)
{
    Tile from{13, 2};
    EXPECT_EQ(cover::no, check_cover(from, from));
    EXPECT_EQ(cover::no, check_cover(from, {13, 1}));
    EXPECT_EQ(cover::no, check_cover(from, {13, 3}));
    EXPECT_EQ(cover::no, check_cover(from, {14, 1}));
    EXPECT_EQ(cover::no, check_cover(from, {14, 3}));
    EXPECT_EQ(cover::no, check_cover(from, {15, 1}));
    EXPECT_EQ(cover::no, check_cover(from, {15, 3}));

    EXPECT_EQ(cover::reachless, check_cover(from, {15, 2}));
}

TEST_F(section4_test, simple5)
{
    Tile from{15, 2};
    EXPECT_EQ(cover::no, check_cover(from, from));

    EXPECT_EQ(cover::no, check_cover(from, {13, 1}));
    EXPECT_EQ(cover::no, check_cover(from, {14, 1}));
    EXPECT_EQ(cover::no, check_cover(from, {15, 1}));
    EXPECT_EQ(cover::no, check_cover(from, {13, 3}));
    EXPECT_EQ(cover::no, check_cover(from, {14, 3}));
    EXPECT_EQ(cover::no, check_cover(from, {15, 3}));

    EXPECT_EQ(cover::reachless, check_cover(from, {13, 2}));
}

TEST_F(section4_test, simple6)
{
    Tile from{13, 3};
    EXPECT_EQ(cover::no, check_cover(from, from));
    EXPECT_EQ(cover::no, check_cover(from, {13, 1}));
    EXPECT_EQ(cover::no, check_cover(from, {13, 2}));
    EXPECT_EQ(cover::no, check_cover(from, {14, 3}));
    EXPECT_EQ(cover::no, check_cover(from, {15, 3}));

    EXPECT_EQ(cover::partial, check_cover(from, {14, 1}));
    EXPECT_EQ(cover::partial, check_cover(from, {15, 2}));

    EXPECT_EQ(cover::reachless, check_cover(from, {15, 1}));
}

TEST_F(section4_test, simple7)
{
    Tile from{14, 3};
    EXPECT_EQ(cover::no, check_cover(from, from));

    EXPECT_EQ(cover::no, check_cover(from, {13, 1}));
    EXPECT_EQ(cover::no, check_cover(from, {13, 2}));
    EXPECT_EQ(cover::no, check_cover(from, {13, 3}));
    EXPECT_EQ(cover::no, check_cover(from, {15, 1}));
    EXPECT_EQ(cover::no, check_cover(from, {15, 2}));
    EXPECT_EQ(cover::no, check_cover(from, {15, 3}));

    EXPECT_EQ(cover::reachless, check_cover(from, {14, 1}));
}

TEST_F(section4_test, simple8)
{
    Tile from{15, 3};
    EXPECT_EQ(cover::no, check_cover(from, from));
    EXPECT_EQ(cover::no, check_cover(from, {13, 3}));
    EXPECT_EQ(cover::no, check_cover(from, {14, 3}));
    EXPECT_EQ(cover::no, check_cover(from, {15, 1}));
    EXPECT_EQ(cover::no, check_cover(from, {15, 2}));

    EXPECT_EQ(cover::partial, check_cover(from, {13, 2}));
    EXPECT_EQ(cover::partial, check_cover(from, {14, 1}));

    EXPECT_EQ(cover::reachless, check_cover(from, {13, 1}));
}

TEST_F(section1_test, no_cover_1)
{
    Tile from{0, 0};
    EXPECT_EQ(cover::no, check_cover(from, from));
    EXPECT_EQ(cover::no, check_cover(from, {0, 1}));
    EXPECT_EQ(cover::no, check_cover(from, {1, 0}));
    EXPECT_EQ(cover::no, check_cover(from, {1, 1}));
    EXPECT_EQ(cover::no, check_cover(from, {2, 0}));
    EXPECT_EQ(cover::no, check_cover(from, {2, 1}));
}

TEST_F(section1_test, no_cover_2)
{
    Tile from{1, 0};
    EXPECT_EQ(cover::no, check_cover(from, from));
    EXPECT_EQ(cover::no, check_cover(from, {0, 0}));
    EXPECT_EQ(cover::no, check_cover(from, {0, 1}));
    EXPECT_EQ(cover::no, check_cover(from, {1, 1}));
    EXPECT_EQ(cover::no, check_cover(from, {2, 0}));
    EXPECT_EQ(cover::no, check_cover(from, {2, 1}));
}

TEST_F(section1_test, no_cover_3)
{
    Tile from{2, 0};
    EXPECT_EQ(cover::no, check_cover(from, from));
    EXPECT_EQ(cover::no, check_cover(from, {0, 0}));
    EXPECT_EQ(cover::no, check_cover(from, {0, 1}));
    EXPECT_EQ(cover::no, check_cover(from, {1, 0}));
    EXPECT_EQ(cover::no, check_cover(from, {1, 1}));
    EXPECT_EQ(cover::no, check_cover(from, {2, 1}));
}

TEST_F(section1_test, no_cover_4)
{
    Tile from{0, 1};
    EXPECT_EQ(cover::no, check_cover(from, from));
    EXPECT_EQ(cover::no, check_cover(from, {0, 0}));
    EXPECT_EQ(cover::no, check_cover(from, {1, 0}));
    EXPECT_EQ(cover::no, check_cover(from, {1, 1}));
    EXPECT_EQ(cover::no, check_cover(from, {2, 0}));
    EXPECT_EQ(cover::no, check_cover(from, {2, 1}));
}

TEST_F(section1_test, no_cover_5)
{
    Tile from{1, 1};
    EXPECT_EQ(cover::no, check_cover(from, from));
    EXPECT_EQ(cover::no, check_cover(from, {0, 0}));
    EXPECT_EQ(cover::no, check_cover(from, {0, 1}));
    EXPECT_EQ(cover::no, check_cover(from, {1, 0}));
    EXPECT_EQ(cover::no, check_cover(from, {2, 1}));
    EXPECT_EQ(cover::no, check_cover(from, {2, 0}));
}

TEST_F(section1_test, no_cover_6)
{
    Tile from{2, 1};
    EXPECT_EQ(cover::no, check_cover(from, from));
    EXPECT_EQ(cover::no, check_cover(from, {0, 0}));
    EXPECT_EQ(cover::no, check_cover(from, {0, 1}));
    EXPECT_EQ(cover::no, check_cover(from, {1, 0}));
    EXPECT_EQ(cover::no, check_cover(from, {1, 1}));
    EXPECT_EQ(cover::no, check_cover(from, {2, 0}));
}

TEST_F(section1_test, reachless)
{
    ASSERT_TRUE(is_tile_occupied({0, 5}));
    ASSERT_TRUE(is_tile_occupied({1, 5}));
    ASSERT_TRUE(is_tile_occupied({2, 5}));
    ASSERT_TRUE(is_tile_occupied({1, 2}));
    ASSERT_TRUE(is_tile_occupied({1, 3}));

    EXPECT_EQ(cover::reachless, check_cover({1, 0}, {1, 4}));
    EXPECT_EQ(cover::reachless, check_cover({1, 1}, {1, 4}));

    EXPECT_EQ(cover::reachless, check_cover({1, 4}, {1, 0}));
    EXPECT_EQ(cover::reachless, check_cover({1, 4}, {1, 1}));

    EXPECT_EQ(cover::reachless, check_cover({0, 2}, {2, 2}));
    EXPECT_EQ(cover::reachless, check_cover({0, 2}, {2, 3}));
    EXPECT_EQ(cover::reachless, check_cover({0, 2}, {2, 4}));
    EXPECT_EQ(cover::reachless, check_cover({0, 2}, {3, 2}));
    EXPECT_EQ(cover::reachless, check_cover({0, 2}, {3, 3}));
    EXPECT_EQ(cover::reachless, check_cover({0, 2}, {3, 4}));

    EXPECT_EQ(cover::reachless, check_cover({0, 3}, {2, 1}));
    EXPECT_EQ(cover::reachless, check_cover({0, 3}, {2, 2}));
    EXPECT_EQ(cover::reachless, check_cover({0, 3}, {2, 3}));
    EXPECT_EQ(cover::reachless, check_cover({0, 3}, {3, 0}));
    EXPECT_EQ(cover::reachless, check_cover({0, 3}, {3, 1}));
    EXPECT_EQ(cover::reachless, check_cover({0, 3}, {3, 2}));
    EXPECT_EQ(cover::reachless, check_cover({0, 3}, {3, 3}));

    EXPECT_EQ(cover::reachless, check_cover({2, 2}, {0, 2}));
    EXPECT_EQ(cover::reachless, check_cover({2, 2}, {0, 3}));
    EXPECT_EQ(cover::reachless, check_cover({2, 2}, {0, 4}));

    EXPECT_EQ(cover::reachless, check_cover({2, 3}, {0, 1}));
    EXPECT_EQ(cover::reachless, check_cover({2, 3}, {0, 2}));
    EXPECT_EQ(cover::reachless, check_cover({2, 3}, {0, 3}));

    EXPECT_EQ(cover::reachless, check_cover({3, 2}, {0, 2}));
    EXPECT_EQ(cover::reachless, check_cover({3, 2}, {0, 3}));

    /** @todo (wrong?) Total coverage here. There is line of effect from
     *  just one corner to an other. I don't know what is a proper behaviour
     */
    //EXPECT_EQ(cover::reachless, check_cover({3, 2}, {0, 4}));
    //EXPECT_EQ(cover::reachless, check_cover({3, 3}, {0, 1}));

    EXPECT_EQ(cover::reachless, check_cover({3, 3}, {0, 2}));
    EXPECT_EQ(cover::reachless, check_cover({3, 3}, {0, 3}));

    EXPECT_EQ(cover::reachless, check_cover({0, 4}, {2, 1}));
    EXPECT_EQ(cover::reachless, check_cover({0, 4}, {2, 2}));
    EXPECT_EQ(cover::reachless, check_cover({0, 4}, {2, 3}));

    EXPECT_EQ(cover::reachless, check_cover({2, 1}, {0, 4}));
    EXPECT_EQ(cover::reachless, check_cover({2, 2}, {0, 4}));

    /// @todo Same error. Total coverage. There is line of effect
    //EXPECT_EQ(cover::reachless, check_cover({2, 3}, {0, 4}));
}

#if 0
    {
        // from Tile (2,2)
        std::cout << check_cover(Coordinate{3, 3}, Tile{1, 4}) << std::endl;
        assert(cover::partial == check_cover(Coordinate{3, 3}, Tile{1, 4}));
    }

    {
        /// @todo I'm here
    std::cout << "======================================" << std::endl;
        std::cout << check_cover(Tile{10, 1}, Tile{9, 3}) << std::endl;
        std::cout << is_reachable(Coordinate{10, 1}, Section{{10, 1}, {9, 3}}) << std::endl;
        std::cout << is_reachable(Coordinate{10, 1}, Section{{10, 1}, {9, 4}}) << std::endl;
        std::cout << is_reachable(Coordinate{10, 1}, Section{{10, 1}, {10, 3}}) << std::endl;
        std::cout << is_reachable(Coordinate{10, 1}, Section{{10, 1}, {10, 4}}) << std::endl;
    std::cout << "======================================" << std::endl;
        std::cout << is_reachable(Coordinate{11, 1}, Section{{11, 1}, {9, 3}}) << std::endl;
        std::cout << is_reachable(Coordinate{11, 1}, Section{{11, 1}, {9, 4}}) << std::endl;
        std::cout << is_reachable(Coordinate{11, 1}, Section{{11, 1}, {10, 3}}) << std::endl;
        std::cout << is_reachable(Coordinate{11, 1}, Section{{11, 1}, {10, 4}}) << std::endl;
/*
        std::cout << is_reachable(Coordinate{3, 3}, Section{{3, 3}, {2, 4}}) << std::endl;
        std::cout << is_reachable(Coordinate{3, 3}, Section{{3, 3}, {1, 4}}) << std::endl;
        std::cout << is_reachable(Coordinate{3, 3}, Section{{3, 3}, {1, 5}}) << std::endl;
*/
    }

    auto prnt_trajectory = [&cout = std::cout](const auto& vec) {
        cout << "[";
        for (const auto& c : vec)
            cout << c << " | ";
        (cout << "]\n").flush();
    };

    {
        assert(cover::no == check_cover(Tile{0, 0}, Tile{0, 0}));
        std::cout << check_cover(Tile{0, 0}, Tile{1, 1}) << std::endl;
        auto f = [](const auto& from, const auto& to)
        {
            for (auto fx = from.x; fx <= from.x + 1; ++fx)
                for (auto fy = from.y; fy <= from.y + 1; ++fy)
                {
                    auto cr = Crossroad{{fx, fy}, from};
                    std::cout << cr << "->" << to << " = " << check_cover(cr, to) << std::endl;
                }
        };
        f(Tile{0, 0}, Tile{1, 1});

        assert(cover::no == check_cover(Tile{0, 0}, Tile{1, 1}));
        assert(cover::no == check_cover(Tile{0, 0}, Tile{1, 0}));
        assert(cover::no == check_cover(Tile{0, 0}, Tile{2, 0}));

        std::cout << check_cover(Tile{0, 1}, Tile{1, 4}) << std::endl;
        assert(cover::total == check_cover(Tile{0, 1}, Tile{1, 4}));

        assert(!is_tile_occupied({1, 1}));
        assert(is_tile_occupied({1, 2}));
        assert(is_tile_occupied({1, 3}));
        assert(!is_tile_occupied({1, 4}));

        std::cout << check_cover(Tile{1, 1}, Tile{1, 4}) << std::endl;
        std::cout << "==============" << std::endl;
        f(Tile{1, 1}, Tile{1, 4});
        {
          {
            // vertical line along border
            Crossroad f{{2, 1}, {1, 1}};
            {
                Crossroad t{{2, 4}, {1, 4}};
                Section sec(f, t);
                /*
                {pt:(2/1, 1/1) tl:(1, 1)}
                {pt:(2/1, 1/1) tl:(2, 1)}
                {pt:(2/1, 2/1) tl:(2, 1)}
                {pt:(2/1, 2/1) tl:(2, 2)}
                {pt:(2/1, 3/1) tl:(2, 2)}
                {pt:(2/1, 3/1) tl:(2, 3)}
                {pt:(2/1, 4/1) tl:(2, 3)}
                {pt:(2/1, 4/1) tl:(1, 4)}
                */

        prnt_trajectory(sec.get_trajectory());
                assert(sec.is_reachable());
            }
            {
                Crossroad t{{2, 5}, {1, 4}};
                Section sec(f, t);
                assert(sec.is_reachable());
            }
            {
                Crossroad t{{1, 4}, {1, 4}};
                Section sec(f, t);
                assert(!sec.is_reachable());
            }
            {
                Crossroad t{{1, 5}, {1, 4}};
                Section sec(f, t);
                assert(!sec.is_reachable());
            }
          }

          {
            // same vertical line along border, different point
            Crossroad f{{2, 2}, {1, 1}};
            {
                Crossroad t{{2, 4}, {1, 4}};
                Section sec(f, t);
                //{pt:(2/1, 2/1) tl:(1, 1)}
                //{pt:(2/1, 2/1) tl:(2, 2)}
                //{pt:(2/1, 3/1) tl:(2, 2)}
                //{pt:(2/1, 3/1) tl:(2, 3)}
                //{pt:(2/1, 4/1) tl:(2, 3)}
                //{pt:(2/1, 4/1) tl:(1, 4)}

                assert(sec.is_reachable());
            }
            {
                Crossroad t{{2, 5}, {1, 4}};
                Section sec(f, t);
                assert(sec.is_reachable());
            }
            {
                Crossroad t{{1, 4}, {1, 4}};
                Section sec(f, t);
                assert(!sec.is_reachable());
            }
            {
                Crossroad t{{1, 5}, {1, 4}};
                Section sec(f, t);
                assert(!sec.is_reachable());
            }
          }
        }

        //prnt_trajectory(sec.get_trajectory());

        std::cout << "--------------" << std::endl;
        assert(cover::reachless == check_cover(Tile{1, 1}, Tile{1, 4}));

        std::cout << check_cover(Tile{2, 2}, Tile{1, 4}) << std::endl;
        assert(cover::partial == check_cover(Tile{2, 2}, Tile{1, 4}));

//        assert(cover::no == check_cover(Tile{5, 1}, Tile{5, 4}));
        std::cout << check_cover(Tile{10, 1}, Tile{9, 3}) << std::endl;
        //assert(cover::reachless == check_cover(Tile{10, 1}, Tile{9, 3}));

        std::cout << check_cover(Tile{11, 1}, Tile{9, 3}) << std::endl;
        //assert(cover::reachless == check_cover(Tile{11, 1}, Tile{9, 3}));
    }
#endif

