#include "Dice.h"
#include "GChar.h" /// @todo replace to GPersonage.h
#include "GMonster.h"
#include "Attack.h"
#include <iostream>
#include <cassert>

int main(int /*argc*/, char* /*argv*/[])
{
    GPersonage minsk("Minsk", fighter, Abilities{ 10, 10, 10, 10, 10, 10});
    GMonster goblin("Goblin Blackblade", 1, 25, Defence{16, 12, 14, 11}, Abilities{ 14, 17, 13, 8, 12, 8});
    std::cout << minsk << std::endl;
    std::cout << minsk.get_abilities() << std::endl;
    std::cout << std::endl;
    std::cout << goblin << std::endl;
    std::cout << goblin.get_abilities() << std::endl;
    std::cout << std::endl;
    auto result = do_attack(minsk, goblin, melee_basic_attack);

    std::cout << "Minsk ";

    if (HitType::MISS == result.first)
      std::cout << "missed";
    else if (HitType::AUTO_MISS == result.first)
      std::cout << "automatically missed";
    else if (HitType::HIT == result.first)
      std::cout << "hit";
    else if (HitType::AUTO_HIT == result.first)
      std::cout << "automatically hit";
    else if (HitType::CRITICAL_HIT == result.first)
      std::cout << "critically hit";

    std::cout << " " << goblin.name();
    if (HitType::MISS != result.first && HitType::AUTO_MISS != result.first)
      std::cout <<  " for " + std::to_string(result.second) + " hp";

    std::cout << std::endl;

    if (HitType::MISS != result.first && HitType::AUTO_MISS != result.first)
      goblin.hp(goblin.hp() - result.second);
    std::cout << std::endl;
    std::cout << goblin << std::endl;
    std::cout << std::endl;
    std::cout << "d4        : " << d4() << std::endl;
    std::cout << "2d4       : " << (2 * d4)() << std::endl;
    std::cout << "2d4 + d6  : " << (2 * d4 + d6)() << std::endl;
    std::cout << "d20       : " << d20() << std::endl;
    std::cout << "d100      : " << d100() << std::endl;
    std::cout << "3d6 + 2d4 : " << (3*d6 + 2*d4)() << std::endl;
    return 0;
}
