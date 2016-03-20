cmake_minimum_required(VERSION 3.3)

project(dnd VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++1y")

# I suppose I'm gonna need some of them
find_package(
    Boost 1.57 REQUIRED COMPONENTS
#    asio
#    msm
#    optional
)
find_package(GTest)
find_package(readline REQUIRED)

ADD_SUBDIRECTORY( src )
