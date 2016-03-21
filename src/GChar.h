#pragma once

#include "BaseAbilities.h"
#include "IAbilities.h" /// @todo rename
#include "IDefence.h"
#include "GClass.h"

#include <experimental/optional>
#include <string>
#include <iosfwd>

#include <iostream>
class GChar : public IDefence
{
public:
    GChar(const std::string& name, const Abilities& abil, unsigned short lvl, short max_hp)
      : m_name(name), m_abil(abil), m_mod(m_abil), m_lvl(lvl), m_max_hp(max_hp)
    {
      assert(lvl > 0);
    }
    const IAbilities& get_abilities() const { return m_abil; }
    const IAbilityModifiers& get_ability_modifiers() const { return m_mod; }
    const std::string& name() const { return m_name; }
    int hp() const { return m_hp; }
    unsigned max_hp() const { return m_max_hp; }
    unsigned short lvl() const { return m_lvl; }
    void hit(unsigned short dmg) {
      std::cout << "HP before: " << m_hp << std::endl;
      m_hp -= dmg;
      std::cout << "HP after: " << m_hp << std::endl;
    }
    unsigned bloodied_hp() const { return max_hp() / 2; }
    bool bloodied() const { return m_hp <= static_cast<int>(bloodied_hp()); }

    /// @todo Use nonvirtual interface
    virtual unsigned short lvl_bonus() const { return 0; };

    friend std::ostream& operator<<(std::ostream&, const GChar&);

private:
    virtual void print_to_stream(std::ostream&) const = 0;

    std::string m_name;
    Abilities m_abil;
    AbilityModifiers m_mod;
    /// @todo BaseSkills m_skills;
    /// @todo Initiative
    /// @todo Speed
    unsigned short m_lvl = 1;
    const unsigned short m_max_hp = 0;
    int m_hp = m_max_hp;

    /// @todo Align
    /// @todo Equipment

    /// @todo weapons
    /// @todo vision
};

class GPersonage : public GChar
{
public:
    GPersonage(
      const std::string& name
    , const GClass& cls
    , const Abilities& abil
    , unsigned short lvl = 1
    , std::experimental::optional<short> max_hp = std::experimental::nullopt
    )
      : GChar(
          name
        , abil
        , lvl
        , max_hp ? *max_hp
             : cls.get_start_hp() + cls.get_per_lvl_hp() * (lvl - 1) + AbilityModifiers(abil).get_con_mod()
        )
      , m_cls(cls)
      , m_mod(get_ability_modifiers())
    {
    }

    unsigned short ac() const override
    {
      /// @todo armor bonuses
      return base_defence()
        + m_cls.ac_mod()
        + std::max<>(m_mod.get_int_mod(), m_mod.get_dex_mod());
    }
    unsigned short fort() const override
    {
      return base_defence()
        + m_cls.fort_mod()
        + std::max<>(m_mod.get_str_mod(), m_mod.get_con_mod());
    };
    unsigned short refl() const override
    {
      return base_defence()
        + m_cls.refl_mod()
        + std::max<>(m_mod.get_int_mod(), m_mod.get_dex_mod());;
    };
    unsigned short will() const override
    {
      return base_defence()
        + m_cls.will_mod()
        + std::max<>(m_mod.get_cha_mod(), m_mod.get_wis_mod());;
    };
  /// @todo attacks : basicMellee, basicRange
  /// @todo Race
  /// @todo Class
  /// @todo Level?
  /// @todo XP
private:
    unsigned short lvl_bonus() const override { return lvl() / 2; }
    unsigned short base_defence() const { return 10 + lvl_bonus(); }

    void print_to_stream(std::ostream&) const override;

    const GClass& m_cls;
    const IAbilityModifiers& m_mod;
};

/// @todo GNpc : GChar ?

