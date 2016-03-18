#pragma once
#include <cassert>

constexpr short get_modificator(unsigned short ability)
{
    /// @todo static_assert(ability <= 30, "30 is a max ability score");
    assert(ability <= 30);
    return ability/2 - 5;
}
