include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_executable(dnd main.cpp Attack.cpp GChar.cpp GMonster.cpp IAbilities.cpp IDefence.cpp)

ADD_SUBDIRECTORY( tests )
