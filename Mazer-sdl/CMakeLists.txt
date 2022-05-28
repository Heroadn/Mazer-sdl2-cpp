# CMakeList.txt: projeto de CMake para Mazer-sdl, incluir origem e definir
# lógica específica a um projeto aqui.
#
cmake_minimum_required (VERSION 3.8)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/)


# Adicione a origem ao executável deste projeto.
add_executable (Mazer-sdl "Mazer-sdl.cpp" "Mazer-sdl.h" "Maze.h"  "Tile.h"  "Maze.cpp"  "PixelBuffer.h" "PixelBuffer.cpp" "Engine/SDLWindow.cpp" "Engine/SDLWindow.h" "Engine/SDLInput.h" "Engine/SDLInput.cpp" "Engine/IEngine.h" "PixelEngine.h" "Engine/GraphicsFactory.cpp"  "PixelEngine.cpp" "Engine/IDrawing.h" "Engine/SDLDrawing.h" "Engine/SDLDrawing.cpp" "Engine/IInput.h" "Engine/IWindow.h")

# SDL2 Config
set(SDL2_PATH "Dependencies/SDL2")
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(Mazer-sdl ${SDL2_LIBRARY})

# SDL_ttf Config
#$set(SDL2_TTF_PATH "Dependencies/SDL_ttf")
#find_package(SDL2_ttf REQUIRED)
#include_directories(${SDL2_TTF_INCLUDE_DIR})
#target_link_libraries(Mazer-sdl ${SDL2_TTF_LIBRARY})


