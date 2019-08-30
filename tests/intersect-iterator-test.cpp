#include "../intersect_iterator.hpp"
#include <tuple>
//#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <cassert>


template <typename Iter, std::size_t N>
auto run(
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

int main(int /*argc*/, char* /*argv*/[])
{
    // RA iterator test
    {
        std::vector<int> seq{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

        // empty sequence
        {
        std::vector<int> seq;
        auto it = make_intersect_iterator(cbegin(seq));
        auto last = make_intersect_iterator(cend(seq));
        assert(it == last);
        assert(last == it);
        }

        // less than frame length sequence
        {
        std::vector<int> seq{1};
        auto it = make_intersect_iterator(cbegin(seq));
        auto last = make_intersect_iterator(cend(seq));
        assert(it == last);
        assert(last == it);
        }

        {
        std::vector<int> seq{2/*count*/, 0/*value*/};
        auto it = make_intersect_iterator<3>(cbegin(seq));
        auto last = make_intersect_iterator<3>(cend(seq));
        assert(it == last);
        assert(last == it);
        }
        // default frame length is 2
        {
        auto it = make_intersect_iterator(cbegin(seq));
        auto last = make_intersect_iterator(cend(seq));
        auto rslt = "0,1,|1,2,|2,3,|3,4,|4,5,|"
                    "5,6,|6,7,|7,8,|8,9,|";
        assert(rslt == run(it, last));
        }

        // user defined frame length
        {
        auto it = make_intersect_iterator<3>(cbegin(seq));
        auto last = make_intersect_iterator<3>(cend(seq));
        auto rslt = "0,1,2,|1,2,3,|2,3,4,|3,4,5,|"
                    "4,5,6,|5,6,7,|6,7,8,|7,8,9,|";
        assert(rslt == run(it, last));
        }

        {
        auto it = make_intersect_iterator<3>(next(cbegin(seq), 3));
        auto last = make_intersect_iterator<3>(next(cbegin(seq), 7));
        auto rslt = "3,4,5,|4,5,6,|";
        assert(rslt == run(it, last));
        }

        {
        auto it = make_intersect_iterator<3>(next(cbegin(seq), 3));
        auto last = make_intersect_iterator<3>(next(cbegin(seq), 6));
        auto rslt = "3,4,5,|";
        assert(rslt == run(it, last));
        }

        {
        auto it = make_intersect_iterator<3>(next(cbegin(seq), 3));
        auto last = make_intersect_iterator<3>(next(cbegin(seq), 5));
        assert(it == last);
        assert(last == it);
        }

    }

    return 0;
}
