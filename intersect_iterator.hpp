#pragma once

#include <array>
#include <tuple>
#include <utility>
#include <cassert>

/** @note WARN: NOT thread safe
 *  This class uses lazy initialization policy, so it isn't
 *  thread safe by default
 *
 *  @note Due to the fact the iterator returns tuple of references
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
 *  @todo It's easy to make it TS by using call_once in
 *  @c lazy_init
 */
template <typename FwdIter, std::size_t N = 2>
class intersect_iterator
{
    template <std::size_t... I>
    static auto gen_arr_impl(
        FwdIter it
      , std::index_sequence<I...>
      , bool do_increment = true
    )
    {
        return std::array<FwdIter, sizeof...(I)> {
            ((void)I, (do_increment ? it++ : it))...
        };
    }

    template <std::size_t... I>
    static auto gen_arr(
        FwdIter it
      , bool do_increment = true
    )
    {
        return gen_arr_impl(
            it
          , std::make_index_sequence<N>{}
          , do_increment
        );
    }

    template <std::size_t... I>
    auto get_refs_impl(std::index_sequence<I...>) const
    {
        return std::tie(*std::get<I>(m_iters)...);
    }

    auto get_refs() const
    {
        return get_refs_impl(std::make_index_sequence<N>{});
    }

    void lazy_init() const
    {
        if (!m_init)
        {
            gen_arr(m_iters.front()).swap(m_iters);
            m_init = true;
        }
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

    explicit intersect_iterator(FwdIter it)
      : m_iters(gen_arr(
            std::move(it)
          , /*do_increment=*/ false
        ))
    {
    }

    void swap(intersect_iterator& rhv) noexcept(noexcept(
        std::declval<intersect_iterator>().m_iters.swap(rhv.m_iters)
    ))
    {
        m_iters.swap(rhv.m_iters);
        std::swap(m_init, rhv.m_init);
    }

    intersect_iterator& operator++()
    {
        gen_arr(std::next(m_iters.front())).swap(m_iters);
        m_init = true;
        return *this;
    }

    intersect_iterator operator++(int)
    {
        intersect_iterator result{*this};
        ++(*this);
        return result;
    }

    reference operator*() { lazy_init(); return get_refs(); }
    auto operator*() const { lazy_init(); return get_refs(); }

    // It doesn't make many sence to support -> since
    // result type is pointer to tuple and tuple doesn't
    // provide many members. But this is LegacyInputIterator
    // requirement. So lets be so.
    pointer operator->() { lazy_init(); return get_refs(); }
    auto operator->() const { lazy_init(); return get_refs(); }

    friend bool operator==(
        const intersect_iterator& lhv
      , const intersect_iterator& rhv
    )
    {
        return lhv.m_iters.back() == rhv.m_iters.back();
    }

private:
    /** @todo It's possible to get rid of a array an leave one
     * iterator only. But it requires some tricks to generate
     * result tuples, so I left it for the future
     * Also it's important to make an attention to relative
     * iterator comparation if that refactoring will take place
     */
    mutable std::array<FwdIter, N> m_iters;
    mutable bool m_init = false;
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

