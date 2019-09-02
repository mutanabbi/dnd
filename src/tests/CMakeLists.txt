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

function (mk_geo_test NAME)
    add_executable(
        ${NAME}
        ${NAME}.cpp
    )
    target_link_libraries(
        ${NAME}
        PRIVATE
            geo
            GTest::GTest
            GTest::Main
      )
    gtest_discover_tests(${NAME})
endfunction()

# TODO: rename to coverage-test
mk_geo_test(main-test)
mk_geo_test(crossroad-test)
mk_geo_test(intersect-iterator-test)
mk_geo_test(line-test)
mk_geo_test(section-test)
mk_geo_test(tile-test)
mk_geo_test(trajectory-test)
