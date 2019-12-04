cmake_minimum_required(VERSION 3.14)
project(assignment)


set(CMAKE_CXX_STANDARD 14)

add_executable(assignment main.cpp Astar.cpp Astar.hpp Grid.cpp Grid.hpp InputListener.cpp InputListener.hpp PathFinder.hpp Dfs.cpp Dfs.hpp PathFinder.cpp)
target_link_libraries(assignment -lsfml-graphics -lsfml-window -lsfml-system)