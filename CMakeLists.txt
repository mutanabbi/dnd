cmake_minimum_required(VERSION 3.3)

project(dnd VERSION 0.0.1 LANGUAGES CXX)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++1y -Wall -Wextra")
# @todo Fix gcc abi problem: -DCMAKE_CXX_COMPILER=g++-5 -DCMAKE_CXX_FLAGS="-D_GLIBCXX_USE_CXX11_ABI=0"

# I suppose I'm gonna need some of them
find_package(
    Boost 1.57 REQUIRED COMPONENTS
#    asio
#    msm
#    optional
)
enable_testing()
#set(GTEST_ROOT "/usr/local/lib/")
find_package(GTest)
find_package(Threads)
find_package(Readline REQUIRED)

add_subdirectory(src)
