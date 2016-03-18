#pragma once

#include "ModificatorCalc.h"
#include "IAbilities.h"

class Abilities : public IAbilities
{
public:
    using ability = unsigned short;

    Abilities(
        ability Str
      , ability Dex
      , ability Con
      , ability Int
      , ability Wis
      , ability Cha
    ) : m_str(Str), m_dex(Dex), m_con(Con), m_int(Int), m_wis(Wis), m_cha(Cha)
    {
    }

    ability get_str() const { return m_str; }
    ability get_dex() const { return m_dex; }
    ability get_con() const { return m_con; }
    ability get_int() const { return m_int; }
    ability get_wis() const { return m_wis; }
    ability get_cha() const { return m_cha; }

    void set_str(ability v) { m_str = v; }
    void set_dex(ability v) { m_dex = v; }
    void set_con(ability v) { m_con = v; }
    void set_int(ability v) { m_int = v; }
    void set_wis(ability v) { m_wis = v; }
    void set_cha(ability v) { m_cha = v; }

private:
    ability m_str = 0;
    ability m_dex = 0;
    ability m_con = 0;
    ability m_int = 0;
    ability m_wis = 0;
    ability m_cha = 0;
};

class AbilityModifiers : public IAbilityModifiers
{
public:
  AbilityModifiers(const Abilities& abil) noexcept : m_abil(abil) {}
  short get_str_mod() const override { return get_modificator(m_abil.get_str()); }
  short get_dex_mod() const override { return get_modificator(m_abil.get_dex()); }
  short get_con_mod() const override { return get_modificator(m_abil.get_con()); }
  short get_int_mod() const override { return get_modificator(m_abil.get_int()); }
  short get_wis_mod() const override { return get_modificator(m_abil.get_wis()); }
  short get_cha_mod() const override { return get_modificator(m_abil.get_cha()); }
private:
  const IAbilities& m_abil;
};

