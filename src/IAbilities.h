#pragma once

#include <iosfwd>

struct IAbilities
{
  virtual unsigned short get_str() const = 0;
  virtual unsigned short get_dex() const = 0;
  virtual unsigned short get_con() const = 0;
  virtual unsigned short get_int() const = 0;
  virtual unsigned short get_wis() const = 0;
  virtual unsigned short get_cha() const = 0;
  virtual ~IAbilities() = default;
};

struct IAbilityModifiers
{
  virtual short get_str_mod() const = 0;
  virtual short get_dex_mod() const = 0;
  virtual short get_con_mod() const = 0;
  virtual short get_int_mod() const = 0;
  virtual short get_wis_mod() const = 0;
  virtual short get_cha_mod() const = 0;
  virtual ~IAbilityModifiers() = default;
};

std::ostream& operator<<(std::ostream&, const IAbilities&);

