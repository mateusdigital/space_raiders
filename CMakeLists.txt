cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME space-raiders)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD          14)
set(CMAKE_CXX_STANDARD_REQUIRED on)
message(${CMAKE_CURRENT_SOURCE_DIR})

## For Windows...
set(SDL2_PATH         ${CMAKE_CURRENT_SOURCE_DIR}/libs/third_party/win32/SDL2-2.0.12)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake_find")

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})
add_definitions(-D_CRT_SECURE_NO_WARNINGS)

include_directories(
    ${SDL2_INCLUDE_DIR}
)

set(SOURCE_FILES
    game/Alien.cpp
    game/Alien.h
    game/AlienLaser.cpp
    game/AlienLaser.h
    game/Background.cpp
    game/Background.h
    game/Engine.cpp
    game/Engine.h
    game/Explosion.cpp
    game/Explosion.h
    game/GameObject.h
    game/GameScene.cpp
    game/GameScene.h
    game/Input.h
    game/Macros.h
    game/MenuScene.cpp
    game/MenuScene.h
    game/Player.cpp
    game/Player.h
    game/PlayerLaser.cpp
    game/PlayerLaser.h
    game/Random.cpp
    game/Random.h
    game/Scene.h
    game/ScoreHelper.cpp
    game/ScoreHelper.h
    game/SplashScene.cpp
    game/SplashScene.h
    game/Sprite.h
    game/Vec2.h
    game/Version.h
    game/main.cpp
    game/olc.cpp
    game/olc_sdl.h
)


add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC ${SDL2_LIBRARY})
