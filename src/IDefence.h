#pragma once

#include <iosfwd>

struct IDefenceModifiers
{
  virtual short ac_mod() const = 0;
  virtual short fort_mod() const = 0;
  virtual short refl_mod() const = 0;
  virtual short will_mod() const = 0;
  virtual ~IDefenceModifiers() = default;

};

struct IDefence
{
  virtual unsigned short ac() const = 0;
  virtual unsigned short fort() const = 0;
  virtual unsigned short refl() const = 0;
  virtual unsigned short will() const = 0;
  virtual ~IDefence() = default;
};

std::ostream& operator<<(std::ostream&, const IDefence&);

