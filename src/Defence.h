#pragma once

#include "Idefence.h"

class Defence : public IDefence
{
public:
    Defence(
      unsigned short ac
    , unsigned short fort
    , unsigned short refl
    , unsigned short will
    ) noexcept
      : m_ac(ac), m_fort(fort), m_refl(refl), m_will(will)
    {
    }
    unsigned short ac() const override { return m_ac; }
    unsigned short fort() const override { return m_fort; }
    unsigned short refl() const override { return m_refl; }
    unsigned short will() const override { return m_will; }
private:
    unsigned short m_ac = 0;
    unsigned short m_fort = 0;
    unsigned short m_refl = 0;
    unsigned short m_will = 0;
};
