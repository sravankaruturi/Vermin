cmake_minimum_required(VERSION 3.10)
project(Vermin)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# GLFW3 Includes

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(${CMAKE_SOURCE_DIR}/Engine/Deps/glfw-3.2.1/)

# Assimp Stuff.
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/Deps/assimp-4.0.1)

message(STATUS ${CMAKE_LIBRARY_PATH})

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

add_library(Vermin library.cpp library.h Window.cpp Window.h Scene.cpp Scene.h Camera.cpp Camera.h PEHelpers.cpp PEHelpers.h Entity.cpp Entity.h Object.cpp Object.h PE_GL.h Mesh.cpp Mesh.h AssetManager.cpp AssetManager.h BoundingBox.cpp BoundingBox.h Texture.cpp Texture.h GLShader.cpp GLShader.h LoggingManager.h LoggingMacros.h GUIHelpers.h AnimatedEntity.cpp AnimatedEntity.h)

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

set(LIBS glfw ${OPENGL_LIBRARIES} GLAD Assimp IMGUI)

target_link_libraries(Vermin ${LIBS})

find_package(OpenGL REQUIRED)

