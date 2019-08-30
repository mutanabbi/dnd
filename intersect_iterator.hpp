#pragma once

#include <array>
#include <tuple>
#include <algorithm>
#include <utility>
#include <cassert>


/** @note Due to the fact the iterator returns tuple of references
 *  on dereference it's category is @c LegacyInputIterator. It may
 *  cause luck of performance on using some standard algorithm w/
 *  this iterator like @c std::advance no matter will we support
 *  RA-operations or not. This is well known issue of std iterators'
 *  categories system. The only way I know how to fix it is to provide
 *  proper overloads for these algos (and/or and full specializations
 *  for related template classes) in namespace @c std. The biggest
 *  problem is the fact that due to the Standard it's forbidden to
 *  inject template overloads to @c std. Only full specializations
 *  are allowed.
 *
 *  @todo For now I can't see the way how to use FWD base iterators
 *  w/ @c intersect_iterator since it's forbidden to increment singular
 *  FWD iterator. It means we can't check intersec_iterator-s equality.
 *  It's necessary to get distance between lower and greater iterators,
 *  but since equality operator is symmetric and FWD iterator doesn't
 *  provide comparation operation, we can't determine who is who.
 *  It's still possible to make it range iterator (pass both iterators -
 *  on a sequence begin and end), but I need to think about it
 */
template <typename FwdIter, std::size_t N = 2>
class intersect_iterator
{
    template <typename... T>
    static auto get_refs_impl(std::tuple<T...>&& result, FwdIter&, std::integral_constant<std::size_t, 0>)
    {
        return result;
    }

    template <typename... T, std::size_t C>
    static auto get_refs_impl(std::tuple<T...>&& result, FwdIter& it, std::integral_constant<std::size_t, C>)
    {
        return get_refs_impl(
            std::tuple_cat(std::move(result), std::tie(*it++))
          , it
          , std::integral_constant<std::size_t, C - 1>{}
        );
    }

    auto get_refs() const
    {
        auto it = m_iter;
        return get_refs_impl(
            std::tuple<>{}
          , it
          , std::integral_constant<std::size_t, N>{}
        );
    }

    class fake_ptr_proxy;

    template <typename T, typename I, I dummy>
    struct id
    {
        using type = T;
    };

    template <typename T, typename Seq>
    struct mk_val_tpl;

    template <typename T, typename I, I... Args>
    struct mk_val_tpl<T, std::integer_sequence<I, Args...>>
    {
        using type = std::tuple<typename id<T, I, Args>::type...>;
    };

public:
    using difference_type = typename std::iterator_traits<FwdIter>::difference_type;
    using value_type = typename mk_val_tpl<
        typename std::iterator_traits<FwdIter>::value_type
      , std::make_index_sequence<N>
    >::type;
    using pointer = fake_ptr_proxy;
    using reference = typename mk_val_tpl<
        typename std::iterator_traits<FwdIter>::reference
      , std::make_index_sequence<N>
    >::type;
    using iterator_category = std::input_iterator_tag;

private:
    class fake_ptr_proxy
    {
        typename intersect_iterator::reference m_val;
    public:
        fake_ptr_proxy(intersect_iterator::reference val)
          : m_val(val)
        {}
        auto* operator->() && { return &m_val; }
    };

public:
    intersect_iterator(const intersect_iterator&) = default;
    intersect_iterator& operator=(const intersect_iterator&) = default;

    template <typename Iter>
    explicit intersect_iterator(Iter it)
      : m_iter(std::move(it))
    {
        static_assert(
            std::is_convertible<
                typename std::iterator_traits<FwdIter>::iterator_category
              , std::random_access_iterator_tag
            >::value
          , "intersect_iterator template argument must be a model of"
            " LegacyRandomAccessIterator at least"
        );
    }

    void swap(intersect_iterator& rhv) noexcept(noexcept(
        std::declval<intersect_iterator>().m_iter.swap(rhv.m_iters)
    ))
    {
        m_iter.swap(rhv.m_iter);
    }

    intersect_iterator& operator++()
    {
        std::advance(m_iter, 1);
        return *this;
    }

    intersect_iterator operator++(int)
    {
        intersect_iterator result{*this};
        ++(*this);
        return result;
    }

    reference operator*() { return get_refs(); }
    auto operator*() const { return get_refs(); }

    // It doesn't make many sence to support -> since
    // result type is pointer to tuple and tuple doesn't
    // provide many members. But this is LegacyInputIterator
    // requirement. So lets be so.
    pointer operator->() { return get_refs(); }
    auto operator->() const { return get_refs(); }

    friend bool operator==(
        const intersect_iterator& lhv
      , const intersect_iterator& rhv
    )
    {
        return is_equal(
            lhv.m_iter, rhv.m_iter, typename std::iterator_traits<FwdIter>::iterator_category{}
        );
    }

private:
    static bool is_equal(
        const FwdIter& lhv, const FwdIter& rhv, std::random_access_iterator_tag
    )
    {
        auto [it1, it2] = std::minmax(lhv, rhv);
        auto dist = std::distance(it1, it2);
        assert(dist >= 0);
        return static_cast<std::size_t>(dist) < N;
    }

    FwdIter m_iter;
};


template <typename FwdIter, std::size_t N>
inline bool operator!=(
    const intersect_iterator<FwdIter, N>& lhv
  , const intersect_iterator<FwdIter, N>& rhv
)
{
    return ! (lhv == rhv);
}

template <typename FwdIter>
class intersect_iterator<FwdIter, 0>;

template <typename FwdIter>
class intersect_iterator<FwdIter, 1>;

template <std::size_t N, typename FwdIter>
inline auto make_intersect_iterator(FwdIter&& iter)
{
    return intersect_iterator<FwdIter, N>(std::forward<FwdIter>(iter));
}

template <typename FwdIter>
inline auto make_intersect_iterator(FwdIter&& iter)
{
    return intersect_iterator<FwdIter>(std::forward<FwdIter>(iter));
}

