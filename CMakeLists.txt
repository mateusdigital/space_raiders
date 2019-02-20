
cmake_minimum_required(VERSION 3.5)

set(PROJECT SpaceRaiders)
project(${PROJECT})

##----------------------------------------------------------------------------##
## Compiler Definitions                                                       ##
##----------------------------------------------------------------------------##
set(CMAKE_CXX_STANDARD          14)
set(CMAKE_CXX_STANDARD_REQUIRED on)

##------------------------------------------------------------------------------
## Modules
##   Find packages scripts was taken from:
##     https://github.com/tcbrindle/sdl2-cmake-scripts
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake_find")



##----------------------------------------------------------------------------##
## SDL                                                                        ##
##----------------------------------------------------------------------------##
find_package(SDL2       REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf   REQUIRED)
find_package(SDL2_gfx   REQUIRED)


include_directories(
    ${SDL2_INCLUDE_DIR}
    ${SDL2_IMAGE_INCLUDE_DIR}
    ${SDL2_TTF_INCLUDE_DIR}
    ${SDL2_GFX_INCLUDE_DIR}
    ./game
)

##----------------------------------------------------------------------------##
## Source Files                                                               ##
##----------------------------------------------------------------------------##
set(SOURCE_FILES
    ./game/Game/Engine.cpp
    ./game/GameObjects/Alien/Alien.cpp
    ./game/GameObjects/Background/Background.cpp
    ./game/GameObjects/Explosion/Explosion.cpp
    ./game/GameObjects/Laser/AlienLaser.cpp
    ./game/GameObjects/Laser/PlayerLaser.cpp
    ./game/GameObjects/Player/Player.cpp
    ./game/main.cpp
    ./game/Maths/Random.cpp
    ./game/Scenes/GameScene/GameScene.cpp
    ./game/Scenes/MenuScene/MenuScene.cpp
    ./game/Scenes/SplashScene/SplashScene.cpp
    ./game/Utils/ScoreHelper.cpp
)


##----------------------------------------------------------------------------##
## Executable Definitions                                                     ##
##----------------------------------------------------------------------------##
add_executable(${PROJECT} ${SOURCE_FILES})


##----------------------------------------------------------------------------##
## Include Directories                                                        ##
##----------------------------------------------------------------------------##
target_include_directories(${PROJECT} PUBLIC ${SDL2_INCLUDE_DIR}        )
target_include_directories(${PROJECT} PUBLIC ${SDL2_IMAGE_INCLUDE_DIRS} )
target_include_directories(${PROJECT} PUBLIC ${SDL2_TTF_INCLUDE_DIRS}   )
target_include_directories(${PROJECT} PUBLIC ${SDL2_GFX_INCLUDE_DIRS}   )

##----------------------------------------------------------------------------##
## Link Libraries                                                             ##
##----------------------------------------------------------------------------##
target_link_libraries(${PROJECT} LINK_PUBLIC ${SDL2_LIBRARY}        )
target_link_libraries(${PROJECT} LINK_PUBLIC ${SDL2_IMAGE_LIBRARIES})
target_link_libraries(${PROJECT} LINK_PUBLIC ${SDL2_TTF_LIBRARIES}  )
target_link_libraries(${PROJECT} LINK_PUBLIC ${SDL2_GFX_LIBRARIES}  )
