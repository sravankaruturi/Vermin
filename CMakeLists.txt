cmake_minimum_required(VERSION 3.10)

project(Game)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory("Engine")

add_executable(Game Game/main.cpp)

target_link_libraries(Game Vermin)