#include "IDefence.h"
#include <ostream>

std::ostream& operator<<(std::ostream& os, const IDefence& v)
{
  os << "AC: " << v.get_ac()
     << " FORT: " << v.get_fort()
     << " REFL: " << v.get_refl()
     << " WILL: " << v.get_will();
  return os;
}
