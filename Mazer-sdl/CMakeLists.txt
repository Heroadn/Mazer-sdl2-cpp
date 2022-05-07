# CMakeList.txt: projeto de CMake para Mazer-sdl, incluir origem e definir
# lógica específica a um projeto aqui.
#
cmake_minimum_required (VERSION 3.8)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/)

# Adicione a origem ao executável deste projeto.
add_executable (Mazer-sdl WIN32 "Mazer-sdl.cpp" "Mazer-sdl.h" "Maze.h"  "Tile.h" "Graphics.h" "Graphics.cpp"  "Maze.cpp"  "PixelBuffer.h" "PixelBuffer.cpp")

# SDL2 Config
set(SDL2_PATH "Dependencies/SDL2")
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(Mazer-sdl ${SDL2_LIBRARY})
