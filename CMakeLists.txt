cmake_minimum_required(VERSION 3.3)

project(dnd VERSION 0.0.1 LANGUAGES CXX)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++1y")

# I suppose I'm gonna need some of them
#find_package(
#    Boost 1.57 REQUIRED COMPONENTS
#    asio
#    msm
#    optional
#  )
find_package(GTest)

ADD_SUBDIRECTORY( src )
