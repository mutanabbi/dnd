add_library(
  core
  # NOTE Keep the sources list sorted
  # TODO Rename `*.h` -> `*.hpp`
  # TODO Add *all* sources!
  Attack.cpp
  Attack.h
  GChar.cpp
  GChar.h
  GMonster.cpp
  GMonster.h
  IAbilities.cpp
  IAbilities.h
  IDefence.cpp
  IDefence.h
)
target_include_directories(
    core
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  )
add_executable(
    dnd
    main.cpp
    Console.cpp
    Console.h
  )

target_link_libraries(
    dnd
    PUBLIC
        core
        Readline::readline
  )

if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
