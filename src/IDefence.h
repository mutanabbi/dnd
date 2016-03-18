#pragma once

#include <iosfwd>

struct IDefenceModifiers
{
  virtual short get_ac_mod() const = 0;
  virtual short get_fort_mod() const = 0;
  virtual short get_refl_mod() const = 0;
  virtual short get_will_mod() const = 0;
  virtual ~IDefenceModifiers() = default;

};

struct IDefence
{
  virtual unsigned short get_ac() const = 0;
  virtual unsigned short get_fort() const = 0;
  virtual unsigned short get_refl() const = 0;
  virtual unsigned short get_will() const = 0;
  virtual ~IDefence() = default;
};

std::ostream& operator<<(std::ostream&, const IDefence&);

