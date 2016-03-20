#include <gtest/gtest.h>
#include <DeathStateMachine.h>

TEST(DeathStateMachineTest, PerRoundTest)
{
  GPersonage minsk("Minsk", fighter, Abilities{ 10, 10, 10, 10, 10, 10});
  DeathStateMachine dsm(std::cref(minsk));
  EXPECT_TRUE(dsm.is_flag_active<is_alive>());
  minsk.hit(minsk.max_hp());
  dsm.process_event(damaged{});
  while (dsm.is_flag_active<is_dying>())
  {
    std::cout << std::endl;
    auto result = d20();
    std::cout << "Saving throw: " << result << std::endl;
    if (d20_dice::max() == result)
      dsm.process_event(saving_throw_critical_success());
    else if (result < 10)
      dsm.process_event(saving_throw_failure());
    else
      dsm.process_event(saving_throw_success());
  }
  EXPECT_TRUE(dsm.is_flag_active<is_dead>() || dsm.is_flag_active<is_alive>());
}

TEST(DeathStateMachineTest, TooBadDamageTest)
{
  GPersonage minsk("Minsk", fighter, Abilities{ 10, 10, 10, 10, 10, 10});
  DeathStateMachine dsm(std::cref(minsk));
  EXPECT_TRUE(dsm.is_flag_active<is_alive>());
  minsk.hit(minsk.bloodied_hp() + minsk.max_hp());
  EXPECT_TRUE(minsk.hp() <= 0);
  dsm.process_event(damaged{});
  EXPECT_TRUE(dsm.is_flag_active<is_dead>());
}
