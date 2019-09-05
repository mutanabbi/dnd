add_executable(
    ModificatorCalcTest
    ModificatorCalcTest.cpp
)
target_link_libraries(
    ModificatorCalcTest
    PRIVATE
        core
        GTest::GTest
        GTest::Main
  )
gtest_discover_tests(ModificatorCalcTest)

add_executable(
    DeathStateMachineTest
    DeathStateMachineTest.cpp
  )
target_link_libraries(
    DeathStateMachineTest
    PRIVATE
        core
        GTest::GTest
        GTest::Main
  )
gtest_discover_tests(DeathStateMachineTest)

add_executable(
    geo-tests
# TODO: rename to coverage-test
    main-test.cpp
    crossroad-test.cpp
    intersect-iterator-test.cpp
    line-test.cpp
    section-test.cpp
    tile-test.cpp
    trajectory-test.cpp
  )

target_link_libraries(
    geo-tests
    PRIVATE
        geo
        GTest::GTest
        GTest::Main
  )

gtest_discover_tests(geo-tests)

