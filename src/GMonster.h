#pragma once

#include "GChar.h"
#include "Defence.h"
#include <string>
#include <iosfwd>

class GMonster : public GChar
{
public:
  GMonster(
    const std::string& name
  , unsigned short lvl
  , short hp
  , const Defence& def
  , const Abilities& abil
  )
    : GChar(name, abil, lvl, hp), m_def(def)
  {}
  unsigned short get_ac() const override { return m_def.get_ac(); }
  unsigned short get_fort() const override { return m_def.get_fort(); }
  unsigned short get_refl() const override { return m_def.get_refl(); }
  unsigned short get_will() const override { return m_def.get_will(); }
  /// @todo Level
  /// @todo Role (Controller, Brude, Elete Controller/Brude)
  /// @todo XP Cost
  /// @todo size: small, gargantua
  /// @todo type: humanoid
private:
  void print_to_stream(std::ostream& os) const override;

  Defence m_def;
};


