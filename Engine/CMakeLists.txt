cmake_minimum_required(VERSION 3.10)
project(Vermin)

set(CMAKE_CXX_STANDARD 14)

# GLFW3 Includes

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_SOURCE_DIR}/Engine/Deps/glfw-3.2.1/)

message(STATUS ${CMAKE_LIBRARY_PATH})

add_library(GLAD ${CMAKE_CURRENT_SOURCE_DIR}/Deps/third_party/glad.c)

target_include_directories(GLAD PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Includes/)

add_library(Vermin library.cpp library.h Window.cpp Window.h)

set(Includes
        "${CMAKE_CURRENT_SOURCE_DIR}/"
        "${CMAKE_CURRENT_SOURCE_DIR}/Includes/"
        "${OPENGL_INCLUDE_DIRS}"
        )

message("${Includes}")

# Define the include DIRs
target_include_directories(Vermin PUBLIC ${Includes})

if ( APPLE )
    set(LIBS glfw ${OPENGL_LIBRARIES} GLAD)
elseif(WIN32)
    set(LIBS glfw ${OPENGL_LIBRARIES} GLAD)
endif()

target_link_libraries(Vermin ${LIBS})

find_package(OpenGL REQUIRED)



