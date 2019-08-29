#include "../intersect_iterator.hpp"
#include <tuple>
#include <iostream>
#include <vector>
#include <cassert>


int main(int /*argc*/, char* /*argv*/[])
{
    // intersect_iterator test
    std::vector<int> vec{1, 2, 3, 4, 5, 6, 7, 8, 9};
    {
    auto it = make_intersect_iterator(cbegin(vec));
    auto last = make_intersect_iterator(cend(vec));
    for (; it != last; ++it)
        std::cout << "("
            << std::get<0>(*it) << ", "
            << std::get<1>(*it) << ")"
            << std::endl;
    }
    {
    auto it = make_intersect_iterator<3>(cbegin(vec));
    auto last = make_intersect_iterator<3>(cend(vec));
    for (; it != last; ++it)
        std::cout << "("
            << std::get<0>(*it) << ", "
            << std::get<1>(*it) << ", "
            << std::get<2>(*it) << ")"
            << std::endl;
    }
    // empty sequence
    {
    std::vector<int> vec;
    auto it = make_intersect_iterator(cbegin(vec));
    auto last = make_intersect_iterator(cend(vec));
    for (; it != last; ++it)
        assert(!"Can't be here");
    }
    /// @todo fix it
#if 0
        // less than frame width sequence
        {
        std::vector<int> vec{1};
        auto it = make_intersect_iterator(cbegin(vec));
        auto last = make_intersect_iterator(cend(vec));
        for (; it != last; ++it)
            assert(!"Can't be here");
        }
        {
        std::vector<int> vec{2/*count*/, 0/*value*/};
        auto it = make_intersect_iterator<3>(cbegin(vec));
        auto last = make_intersect_iterator<3>(cend(vec));
        for (; it != last; ++it)
            assert(!"Can't be here");
        }
#endif
    return 0;
}
