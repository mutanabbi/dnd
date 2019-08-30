# ALERT Always use the latest available release!
cmake_minimum_required(VERSION 3.14)

project(
    dnd
    DESCRIPTION "The DND Game" # TODO Provide a better description
    HOMEPAGE_URL "https://github.com/mutanabbi/dnd"
    VERSION 0.0.1
    LANGUAGES CXX C
  )

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# I suppose I'm gonna need some of them
# TODO Use 1.70 w/ native CMake support!
find_package(
    Boost 1.57 REQUIRED COMPONENTS
    # NOTE Keep the list of components sorted
    thread
  )

find_package(Readline 7.0 REQUIRED COMPONENTS readline)
find_package(GTest)

include(CTest)
enable_testing()

add_subdirectory(src)
