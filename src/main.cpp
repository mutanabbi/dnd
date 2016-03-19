#include <Dice.h>
#include <GChar.h> /// @todo replace to GPersonage.h
#include <GMonster.h>
#include <Attack.h>
#include <Console.h>
#include <iostream>
#include <memory>
#include <cassert>

std::unordered_map<std::string, std::unique_ptr<GChar>> g_chars;

void parse_cmd(std::vector<std::string> args)
{
  if (args.size() == 3 && args[1] == "hit")
  {
    auto attacker_it = g_chars.find(args[0]);
    auto defender_it = g_chars.find(args[2]);
    if (attacker_it == g_chars.end() || defender_it == g_chars.end())
      return;
    auto& attacker = attacker_it->second;
    auto& defender = defender_it->second;

    auto result = do_attack(*attacker, *defender, melee_basic_attack);
    /// @todo now here is an overflowing. Iplement dying mechanic
    if (HitType::MISS != result.first && HitType::AUTO_MISS != result.first)
      defender->hp(defender->hp() - result.second);

    std::cout << attacker->name() << " ";
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

    std::cout << " " << defender->name();
    if (HitType::MISS != result.first && HitType::AUTO_MISS != result.first)
      std::cout <<  " for " + std::to_string(result.second) + " hp";


    std::cout << '\n'
      << *attacker << '\n'
      << *defender << '\n'
      << std::endl;
  }
}

int main(int /*argc*/, char* /*argv*/[])
{
    auto minsk = std::make_unique<GPersonage>("Minsk", fighter, Abilities{ 10, 10, 10, 10, 10, 10});
    auto goblin = std::make_unique<GMonster>("Goblin Blackblade", 1, 25, Defence{16, 12, 14, 11}, Abilities{ 14, 17, 13, 8, 12, 8});

    std::cout
      << *minsk << '\n'
      << minsk->get_abilities() << '\n'
      << *goblin << '\n'
      << goblin->get_abilities() << '\n'
      << std::endl;

    g_chars.emplace("minsk", std::move(minsk));
    g_chars.emplace("goblin", std::move(goblin));

    Console console("> ");
    console.register_default_handler(parse_cmd);
    Console::cmd_status rc;
    do
    {
      rc = console();
    }
    while (rc != Console::cmd_status::QUIT);

    /*
    std::cout << "d4        : " << d4() << std::endl;
    std::cout << "2d4       : " << (2 * d4)() << std::endl;
    std::cout << "2d4 + d6  : " << (2 * d4 + d6)() << std::endl;
    std::cout << "d20       : " << d20() << std::endl;
    std::cout << "d100      : " << d100() << std::endl;
    std::cout << "3d6 + 2d4 : " << (3*d6 + 2*d4)() << std::endl;
    */
    return 0;
}
