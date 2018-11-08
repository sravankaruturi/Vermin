cmake_minimum_required(VERSION 3.10)
project(Vermin)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# GLFW3 Includes

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_SOURCE_DIR}/Engine/Deps/glfw-3.2.1/)

#if(NOT MSVC)
# Assimp Stuff.
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Deps/assimp/)

message(STATUS ${CMAKE_LIBRARY_PATH})
#endif()

# Glad Stuff
add_library(GLAD ${CMAKE_CURRENT_SOURCE_DIR}/Deps/third_party/glad.c)
target_include_directories(GLAD PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Includes/)

# ImGUI Stuff
file(GLOB IMGUI_SRC
        ${CMAKE_CURRENT_SOURCE_DIR}/Deps/third_party/Imgui/*.cpp
        )

add_library(IMGUI
        ${IMGUI_SRC}
        )

target_include_directories(IMGUI
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Deps/third_party/Imgui/
        ${CMAKE_CURRENT_SOURCE_DIR}/Includes/
        )

file(GLOB VERMIN_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/*.h
        )

file(GLOB VERMIN_SOURCE
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
        )

add_library(Vermin
        ${VERMIN_HEADERS}
        ${VERMIN_SOURCE}
        )

set(Includes
        "${CMAKE_CURRENT_SOURCE_DIR}/"
        "${CMAKE_CURRENT_SOURCE_DIR}/Includes/"
        "${CMAKE_CURRENT_SOURCE_DIR}/Deps/third_party/Imgui/"
        "${OPENGL_INCLUDE_DIRS}"
        "${ASSIMP_INCLUDE_DIRS}"
        "${IMGUI_INCLUDE_DIRS}"
        )

message("${Includes}")

# Define the include DIRs
target_include_directories(Vermin PUBLIC ${Includes})

#if(MSVC)
#target_link_libraries(Vermin ${CMAKE_CURRENT_SOURCE_DIR}/Deps/binaries/assimp.lib)
#endif()

#find_package(ASSIMP REQUIRED)

set(LIBS glfw ${OPENGL_LIBRARIES} GLAD assimp IMGUI)

target_link_libraries(Vermin ${LIBS})

find_package(OpenGL REQUIRED)

if ( NOT MSVC )
add_compile_definitions(_GLIBCXX_USE_CXX11_ABI=0)
endif()
#add_compile_definitions(GLM_MESSAGES=1)