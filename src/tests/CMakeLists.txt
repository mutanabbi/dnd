add_executable(ModificatorCalcTest ModificatorCalcTest.cpp)
target_link_libraries(ModificatorCalcTest PUBLIC "${GTEST_BOTH_LIBRARIES}")
target_include_directories(ModificatorCalcTest PUBLIC "${GTEST_INCLUDE_DIRS}")
#GTEST_ADD_TESTS(ModificatorCalc "--foo 1" FooUnitTest.cc)
