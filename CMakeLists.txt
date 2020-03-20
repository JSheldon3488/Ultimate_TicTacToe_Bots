cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(Ultimate_TicTacToe)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} src dependencies)

add_executable(Ultimate_TicTacToe src/main.cpp src/renderer.cpp src/gameObjects.cpp src/game.cpp dependencies/SDL2_gfxPrimitives.c dependencies/SDL2_rotozoom.c)
string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
target_link_libraries(Ultimate_TicTacToe ${SDL2_LIBRARIES})