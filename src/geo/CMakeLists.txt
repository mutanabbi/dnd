add_library(
    geo INTERFACE
    #Coordinate.hpp
    #Coverage.hpp
    #Crossroad.hpp
    #intersect_iterator.hpp
    #Line.hpp
    #Section.hpp
    #Tile.hpp
    #Trajectory.hpp
)
get_filename_component(PARENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} DIRECTORY)
target_include_directories(
    geo
    INTERFACE
    $<BUILD_INTERFACE:${PARENT_DIR}>
  )
