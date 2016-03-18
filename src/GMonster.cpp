#include "GMonster.h"
#include <ostream>

void GMonster::print_to_stream(std::ostream& os) const
{
  os << name() << " of " << lvl() << " level";
  os << " HP: " << hp();
  os << " " << static_cast<const IDefence&>(*this);
}
