#include <geo/intersect_iterator.hpp>
#include <gtest/gtest.h>
#include <tuple>
//#include <iostream> // TODO: DEBUG ONLY
#include <sstream>
#include <vector>
#include <list>


// RA iterator test
class intersect_iterator_ra_test : public ::testing::Test
{
protected:
    template <typename Iter, std::size_t N>
    static auto run(
        intersect_iterator<Iter, N> first
      , intersect_iterator<Iter, N> last
    )
    {
        std::stringstream ss;
        auto prnt = [&ss/*, &cout = std::cout*/] (auto... args) {
            { char a[] = {(ss << args << ',', '0')...}; (void)a; }
            //{ char a[] = {(cout << args << ',', '0')...}; (void)a; }
        };

        for (; first != last; ++first)
        {
            std::apply(prnt, *first);
            ss << '|';
            //std::cout << '\n';
        }
        //std::cout << std::endl;
        return ss.str();
    }

    // void SetUp() override {}

    // void TearDown() override {}

    std::vector<int> seq{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
};


// empty sequence RA iter test
TEST(simple_intersect_iterator_ra_test, empty_sequnce)
{
    std::vector<int> seq;
    auto it = make_intersect_iterator(cbegin(seq));
    auto last = make_intersect_iterator(cend(seq));
    EXPECT_EQ(it, last);
    EXPECT_EQ(last, it);
}

// less than frame length sequence
TEST(simple_intersect_iterator_ra_test, n_less_than_seq_size_1)
{
    std::vector<int> seq{1};
    auto it = make_intersect_iterator(cbegin(seq));
    auto last = make_intersect_iterator(cend(seq));
    EXPECT_EQ(it, last);
    EXPECT_EQ(last, it);
}

TEST(simple_intersect_iterator_ra_test, n_less_than_seq_size_2)
{
    std::vector<int> seq{2/*count*/, 0/*value*/};
    auto it = make_intersect_iterator<3>(cbegin(seq));
    auto last = make_intersect_iterator<3>(cend(seq));
    EXPECT_EQ(it, last);
    EXPECT_EQ(last, it);
}

TEST_F(intersect_iterator_ra_test, default_frame_length_is_2)
    // default frame length is 2
{
    auto it = make_intersect_iterator(cbegin(seq));
    auto last = make_intersect_iterator(cend(seq));
    auto rslt = "0,1,|1,2,|2,3,|3,4,|4,5,|"
                "5,6,|6,7,|7,8,|8,9,|";
    EXPECT_EQ(rslt, run(it, last));
}

// user defined frame length
TEST_F(intersect_iterator_ra_test, user_defined_frame_length_is_3)
{
    auto it = make_intersect_iterator<3>(cbegin(seq));
    auto last = make_intersect_iterator<3>(cend(seq));
    auto rslt = "0,1,2,|1,2,3,|2,3,4,|3,4,5,|"
                "4,5,6,|5,6,7,|6,7,8,|7,8,9,|";
    EXPECT_EQ(rslt, run(it, last));
}

TEST_F(intersect_iterator_ra_test, user_defined_frame_length_is_3_partial_1)
{
    auto it = make_intersect_iterator<3>(next(cbegin(seq), 3));
    auto last = make_intersect_iterator<3>(next(cbegin(seq), 7));
    auto rslt = "3,4,5,|4,5,6,|";
    EXPECT_EQ(rslt, run(it, last));
}

TEST_F(intersect_iterator_ra_test, user_defined_frame_length_is_3_partial_2)
{
    auto it = make_intersect_iterator<3>(next(cbegin(seq), 3));
    auto last = make_intersect_iterator<3>(next(cbegin(seq), 6));
    auto rslt = "3,4,5,|";
    EXPECT_EQ(rslt, run(it, last));
}

TEST_F(intersect_iterator_ra_test, user_defined_frame_length_is_3_partial_3_iter_eq)
{
    auto it = make_intersect_iterator<3>(next(cbegin(seq), 3));
    auto last = make_intersect_iterator<3>(next(cbegin(seq), 5));
    EXPECT_EQ(it, last);
    EXPECT_EQ(last, it);
}

