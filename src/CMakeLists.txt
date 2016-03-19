include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_executable(
  dnd
  main.cpp Attack.cpp GChar.cpp GMonster.cpp IAbilities.cpp IDefence.cpp Console.cpp
)
target_link_libraries(dnd PUBLIC "${Readline_LIBRARY}")
target_include_directories(dnd PUBLIC "${Readline_INCLUDE_DIRS}")

ADD_SUBDIRECTORY( tests )
