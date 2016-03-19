#include "Attack.h"

#include <cassert>

short get_proper_defence(const IAttack& attack, const IDefence& def)
{
  switch (attack.get_defence_type())
  {
    case DefenceType::AC:
      return def.ac();
    case DefenceType::FORT:
      return def.fort();
    case DefenceType::REFL:
      return def.refl();
    case DefenceType::WILL:
      return def.will();
    default:
      assert(!"Can't be here");
  };
  assert(!"Can't be here");
  return 0;
}


short get_proper_ability(const IAttack& attack, const IAbilityModifiers& abil)
{
  switch (attack.get_ability_type())
  {
    case AbilityType::STR:
      return abil.get_str_mod();
    case AbilityType::DEX:
      return abil.get_dex_mod();
    case AbilityType::CON:
      return abil.get_con_mod();
    case AbilityType::INT:
      return abil.get_int_mod();
    case AbilityType::WIS:
      return abil.get_wis_mod();
    case AbilityType::CHA:
      return abil.get_cha_mod();
    case AbilityType::UNKNOWN:
      return 0;
    default:
      assert(!"Can't be here");
  };
  assert(!"Can't be here");
  return 0;
}


std::pair<HitType, unsigned>
do_attack(const GChar& attacker, const GChar& defencer, const IAttack& pwr)
{
  /// @todo half damage on miss if power says so
  auto roll = d20();
  unsigned dmg = 0;
  HitType hit = HitType::MISS;

  if (roll == 1)
    return {HitType::AUTO_MISS, 0};

  auto ability_mod = get_proper_ability(pwr, attacker.get_ability_modifiers());
  auto attack_result = roll + attacker.lvl_bonus() + ability_mod + pwr.get_bonus();
  auto defence_result = get_proper_defence(pwr, defencer);

  if (roll == 20 && attack_result >= defence_result)
    hit = HitType::CRITICAL_HIT;
  else if (roll == 20 && attack_result < defence_result)
    hit = HitType::AUTO_HIT;
  else if (attack_result >= defence_result)
    hit = HitType::HIT;

  if (hit != HitType::MISS && hit != HitType::AUTO_MISS)
    dmg = hit == HitType::CRITICAL_HIT ? pwr.damage().max() : pwr.damage().get();
  return {hit, dmg};
}
