include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_library(
  core STATIC
  GMonster.cpp GChar.cpp IAbilities.cpp IDefence.cpp Attack.cpp
)
add_executable(
  dnd
  main.cpp Console.cpp
)
target_link_libraries(dnd PUBLIC core "${Readline_LIBRARY}")
target_include_directories(dnd PUBLIC "${Readline_INCLUDE_DIRS}")

ADD_SUBDIRECTORY( tests )
