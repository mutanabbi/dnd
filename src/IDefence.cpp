#include "IDefence.h"
#include <ostream>

std::ostream& operator<<(std::ostream& os, const IDefence& v)
{
  os << "AC: " << v.ac()
     << " FORT: " << v.fort()
     << " REFL: " << v.refl()
     << " WILL: " << v.will();
  return os;
}
