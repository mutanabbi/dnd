#include <gtest/gtest.h>
#include <ModificatorCalc.h>

TEST(ModificatorCalcTest, BasicCases)
{
    EXPECT_EQ(10,  get_modificator(30));
    EXPECT_EQ(9,  get_modificator(29));
    EXPECT_EQ(9,  get_modificator(28));
    EXPECT_EQ(8,  get_modificator(27));
    EXPECT_EQ(8,  get_modificator(26));
    EXPECT_EQ(7,  get_modificator(25));
    EXPECT_EQ(7,  get_modificator(24));
    EXPECT_EQ(6,  get_modificator(23));
    EXPECT_EQ(6,  get_modificator(22));
    EXPECT_EQ(5,  get_modificator(21));
    EXPECT_EQ(5,  get_modificator(20));
    EXPECT_EQ(4,  get_modificator(19));
    EXPECT_EQ(4,  get_modificator(18));
    EXPECT_EQ(3,  get_modificator(17));
    EXPECT_EQ(3,  get_modificator(16));
    EXPECT_EQ(2,  get_modificator(15));
    EXPECT_EQ(2,  get_modificator(14));
    EXPECT_EQ(1,  get_modificator(13));
    EXPECT_EQ(1,  get_modificator(12));
    EXPECT_EQ(0,  get_modificator(11));
    EXPECT_EQ(0,  get_modificator(10));
    EXPECT_EQ(-1,  get_modificator(9));
    EXPECT_EQ(-1,  get_modificator(8));
    EXPECT_EQ(-2,  get_modificator(7));
    EXPECT_EQ(-2,  get_modificator(6));
    EXPECT_EQ(-3,  get_modificator(5));
    EXPECT_EQ(-3,  get_modificator(4));
    EXPECT_EQ(-4,  get_modificator(3));
    EXPECT_EQ(-4,  get_modificator(2));
    EXPECT_EQ(-5,  get_modificator(1));
    EXPECT_EQ(-5,  get_modificator(0));
}
