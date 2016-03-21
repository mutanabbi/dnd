#pragma once

#include "GChar.h"
#include "IDefence.h"
#include "IAbilities.h"
#include "Dice.h"

enum class DefenceType : unsigned short
{
  AC, FORT, REFL, WILL
};

/// @todo avoid dirty UNKNOWN workaround
enum class AbilityType : unsigned short
{
  STR, DEX, CON, INT, WIS, CHA, UNKNOWN
};

enum class HitType : unsigned short
{
  MISS, AUTO_MISS, HIT, AUTO_HIT, CRITICAL_HIT
};

class Damage
{
public:
  explicit Damage(unsigned value) noexcept
    : m_min([value]{ return value; })
    , m_max([value]{ return value; })
    , m_val([value]{ return value; })
  {}

  Damage(const D20DicePool& dp) noexcept
    : m_min([dp]{ return dp.min(); })
    , m_max([dp]{ return dp.max(); })
    , m_val(dp)
  {}

  unsigned min() const { return m_min(); }
  unsigned max() const { return m_max(); }
  unsigned get() const { return m_val(); }

private:
    std::function<unsigned()> m_min;
    std::function<unsigned()> m_max;
    std::function<unsigned()> m_val;
};


class IAttack
{
public:
  virtual unsigned short get_bonus() const = 0;
  virtual DefenceType get_defence_type() const = 0;
  virtual AbilityType get_ability_type() const = 0;
  virtual Damage damage() const = 0;
/// @todo target: person, object, area
/// @todo action: StandardAction
/// @todo attack: Wisdom vs Ref
/// @todo miss:
/// @todo special:
/// @todo keywords: conjuration, divine, implement, radiant,
/// @todo sustain minor:
  virtual ~IAttack() = default;
};


class MonsterAttack : public IAttack
{
public:
  MonsterAttack(short modifier, DefenceType defence, unsigned short dmg)
    : m_mod(modifier), m_df(defence), m_dmg(dmg)
  {}
  MonsterAttack(short modifier, DefenceType defence, D20DicePool dmg)
    : m_mod(modifier), m_df(defence), m_dmg(dmg)
  {}
  unsigned short get_bonus() const override { return m_mod; }
  DefenceType get_defence_type() const override { return m_df; }
  AbilityType get_ability_type() const override { return AbilityType::UNKNOWN; }
  Damage damage() const override { return m_dmg; }

private:
  short m_mod = 0;
  DefenceType m_df;
  Damage m_dmg;
};


class CharAttack : public IAttack
{
public:
  CharAttack(short modifier, AbilityType ability, DefenceType defence, unsigned short dmg)
    : m_abil(ability), m_df(defence), m_mod(modifier), m_dmg(dmg)
  {}
  CharAttack(short modifier, AbilityType ability, DefenceType defence, D20DicePool dmg)
    : m_abil(ability), m_df(defence), m_mod(modifier), m_dmg(dmg)
  {}
  unsigned short get_bonus() const override { return m_mod; }
  DefenceType get_defence_type() const override { return m_df; }
  AbilityType get_ability_type() const override { return m_abil; }
  Damage damage() const override { return m_dmg; }

private:
  AbilityType m_abil;
  DefenceType m_df;
  unsigned m_mod;
  Damage m_dmg;
};


short get_proper_defence(const IAttack& attack, const IDefence& def);

short get_proper_ability(const IAttack& attack, const IAbilityModifiers& abil);

std::pair<HitType, unsigned>
do_attack(const GChar& attacker, const GChar& defencer, const IAttack& pwr);

/// @todo Avoid hardcoded damage dice
static CharAttack melee_basic_attack{0, AbilityType::STR, DefenceType::AC, d4};

/// @todo
/*
class MelleeAttack : public IAttack
{
};

class BasicMelleeAttack : public MeleeAttack
{};

class RangeAttack : public Attack
{
range: 5
};

class BasicRangeAttack : public RangeAttack
{}

class CloseAttack : public RangeAttack
{};

class AreaAttack : public RangeAttack
{};
*/
