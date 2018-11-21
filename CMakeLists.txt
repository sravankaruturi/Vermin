cmake_minimum_required(VERSION 3.10)

project(Game)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory("Engine")

target_include_directories(Vermin
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/Engine/src/
        )

add_executable(
        Game
        Game/main.cpp
        Game/Game.h
        Game/Game.cpp
        Game/GameScene.h
        Game/GameScene.cpp
        Game/GamePlayManager.cpp
        Game/GamePlayManager.h
        Game/Unit.cpp
        Game/Unit.h Game/Villager.cpp Game/Villager.h Game/Warrior.cpp Game/Warrior.h Game/Catapult.cpp Game/Catapult.h Game/Building.cpp Game/Building.h Game/Barracks.cpp Game/Barracks.h Game/SiegeFactory.cpp Game/SiegeFactory.h
        Game/MenuScene.h
        Game/MenuScene.cpp
)

target_link_libraries(Game Vermin)