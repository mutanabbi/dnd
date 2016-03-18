#include "GChar.h"
#include <ostream>

std::ostream& operator<<(std::ostream& os, const GChar& v)
{
  v.print_to_stream(os);
  return os;
}

void GPersonage::print_to_stream(std::ostream& os) const
{
  os << m_cls.get_name() << " " << name() << " of " << lvl() << " level";
  os << " HP: " << hp();
  os << " " << static_cast<const IDefence&>(*this);
}
