#pragma once

#include <random>
#include <iostream>
#include <type_traits>
#include <cassert>

namespace detail {
template <typename T, typename ...>
struct is_one_of : std::false_type {};
template <typename T, typename Head, typename ... Tail>
struct is_one_of<T, Head, Tail...>
  : std::integral_constant<bool, std::is_same<T, Head>::value || is_one_of<T, Tail...>::value> {};
}                                                           // detail

/// @todo support "exploding" dice
template <unsigned Edges>
class Dice
{
public:
  unsigned operator()() const { return get_dist()(get_re()); }
  static constexpr unsigned max() { return Edges; }
  static constexpr unsigned min() { return 1; }
private:
    static auto& get_dist()
    {
      static std::uniform_int_distribution<unsigned> s_dist {1, Edges};
      return s_dist;
    }
    static auto& get_re()
    {
      static std::default_random_engine s_re(std::random_device{}());
      return s_re;
    }
};

using d2_dice = Dice<2>;
using d4_dice = Dice<4>;
using d6_dice = Dice<6>;
using d8_dice = Dice<8>;
using d10_dice = Dice<10>;
using d20_dice = Dice<20>;
using d100_dice = Dice<100>;

static d4_dice d2;
static d4_dice d4;
static d6_dice d6;
static d8_dice d8;
static d10_dice d10;
static d20_dice d20;
static d100_dice d100;

/// @todo Support of dropping N minumum and maximum values
/// @todo Do I really need type restrictions in @c DicePool class?
template <typename ... DiceTypes>
class DicePool
{
public:
  template <unsigned Edges>
  DicePool(Dice<Edges> dice, unsigned multiplier = 1)
    : m_min(Dice<Edges>::min() * multiplier), m_max(Dice<Edges>::max() * multiplier)
  {
    assert("It doesn't make sence to make zero throws" && multiplier > 0);
    /// @todo I suppose it's better to use @c boost::mpl
    static_assert(
      detail::is_one_of<Dice<Edges>
    , DiceTypes...>::value, "Wront Dice type for this Dice pool"
    );
    m_dice_pool.emplace_back(
      [dice, multiplier]{
        unsigned result = 0;
        for (unsigned i = 0; i < multiplier; ++i)
          result += dice();
        return result;
      });
  }

  unsigned long operator()() const
  {
    return std::accumulate(
      begin(m_dice_pool)
    , end(m_dice_pool)
    , 0u
    , [](unsigned cur, std::function<unsigned()> dice_pool) { return cur + dice_pool(); }
    );
  }

  unsigned min() const
  {
    return m_min;
  }

  unsigned max() const
  {
    return m_max;
  }

  friend DicePool operator+(const DicePool& lhv, const DicePool& rhv)
  {
    DicePool result(lhv);
    result.m_dice_pool.emplace_back(rhv);
    result.m_min += rhv.m_min;
    result.m_max += rhv.m_max;
    return result;
  }

private:
  /// @todo result type should be mighty than dice's one
  std::vector<std::function<unsigned()>> m_dice_pool;
  unsigned m_min = 0;
  unsigned m_max = 0;
};


/// @todo I should use @c boost::MPL to create a fully functional arythmetic operators. But this is just a fast approach
using D20DicePool = DicePool<d2_dice, d4_dice, d6_dice, d8_dice, d10_dice, d100_dice>;


template <unsigned Edges>
inline auto operator*(unsigned multiplier, Dice<Edges> dice)
{
  return D20DicePool(dice, multiplier);
}


template <unsigned DLeftEdges, unsigned DRightEdges>
inline auto operator+(Dice<DLeftEdges> lhv, Dice<DRightEdges> rhv)
{
  return D20DicePool(lhv) + D20DicePool(rhv);
}
