cmake_minimum_required(VERSION 3.3)

project(dnd VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
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
find_package(GTest)
find_package(readline REQUIRED)

add_subdirectory(src)
