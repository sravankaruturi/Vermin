cmake_minimum_required(VERSION 3.10)
project(Vermin)

set(CMAKE_CXX_STANDARD 14)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/Libraries)

message(STATUS ${CMAKE_LIBRARY_PATH})

add_library(Vermin library.cpp library.h Window.cpp Window.h)

target_include_directories(Vermin PUBLIC Includes/)

target_link_libraries(Vermin C:/dev/Vermin/Engine/Libraries/glfw3.lib)