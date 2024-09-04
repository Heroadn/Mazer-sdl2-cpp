# CMakeList.txt: projeto de CMake para Mazer-sdl, incluir origem e definir
# lógica específica a um projeto aqui.
#
cmake_minimum_required (VERSION 3.8)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/)


# Adicione a origem ao executável deste projeto.
add_executable (Mazer-sdl 
"src/Mazer-sdl.cpp" 
"src/Mazer-sdl.h" 
"src/Maze.h"  
"src/Tile.h"  
"src/Maze.cpp"  
"src/PixelBuffer.h" 
 
"src/Engine/SDLWindow.cpp" 
"src/Engine/SDLWindow.h" 
"src/Engine/SDLInput.h" 
"src/Engine/SDLInput.cpp" 
"src/Engine/IEngine.h" 
"src/PixelEngine.h" 
"src/Engine/GraphicsFactory.cpp"  
"src/PixelEngine.cpp" 
"src/Engine/IDrawing.h" 
"src/Engine/SDLDrawing.h" 
"src/Engine/SDLDrawing.cpp" 
"src/Engine/IInput.h" 
"src/Engine/IWindow.h")

# SDL2 Config
find_package(SDL2 CONFIG REQUIRED)

target_link_libraries(
	Mazer-sdl 
	SDL2::SDL2
	SDL2::SDL2main)

# SDL_ttf Config
#$set(SDL2_TTF_PATH "Dependencies/SDL_ttf")
#find_package(SDL2_ttf REQUIRED)
#include_directories(${SDL2_TTF_INCLUDE_DIR})
#target_link_libraries(Mazer-sdl ${SDL2_TTF_LIBRARY})


