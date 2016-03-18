#include "IAbilities.h"
#include <iostream>

std::ostream& operator<<(std::ostream& os, const IAbilities& v)
{
  os << "STR: " << v.get_str() << '\n'
     << "DEX: " << v.get_dex() << '\n'
     << "CON: " << v.get_con() << '\n'
     << "INT: " << v.get_int() << '\n'
     << "WIS: " << v.get_wis() << '\n'
     << "CHA: " << v.get_cha();
  return os;
}
