cmake_minimum_required(VERSION 2.8.4)
project(SortingVisualizer)

find_package(SDL2 REQUIRED)
include_directories(SortingVisualizer ${SDL2_INCLUDE_DIRS})

add_executable(SortingVisualizer sort.c)
target_link_libraries(SortingVisualizer ${SDL2_LIBRARIES})
