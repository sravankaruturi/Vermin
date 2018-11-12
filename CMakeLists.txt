cmake_minimum_required(VERSION 3.10)

project(Game)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory("Engine")

add_executable(Game Game/main.cpp Game/Game.h Game/Game.cpp Game/GameScene.h Game/GameScene.cpp Game/GamePlayManager.cpp Game/GamePlayManager.h Game/Player.cpp Game/Player.h Game/Unit.cpp Game/Unit.h Game/Villager.cpp Game/Villager.h Game/Warrior.cpp Game/Warrior.h Game/Catapult.cpp Game/Catapult.h Game/Building.cpp Game/Building.h Game/Barracks.cpp Game/Barracks.h Game/SiegeFactory.cpp Game/SiegeFactory.h)

target_link_libraries(Game Vermin)