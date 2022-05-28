// Mazer-sdl.cpp: define o ponto de entrada para o aplicativo.
//

#define MAZE_WIDTH  15
#define MAZE_HEIGHT 15
#define SCREEN_WIDTH 200
#define SCREEN_HEIGHT 200
//#define SCREEN_WIDTH 960
//#define SCREEN_HEIGHT 544
#define SDL_MAIN_HANDLED

#include "Mazer-sdl.h"
#include "Maze.h"
#include "Engine\SDLWindow.h"

#include <cstdio>
#include <cstdint>
#include <stdio.h>
#include <functional>
#include "PixelBuffer.h"
#include "PixelEngine.h"

int main(int argc, char* argv[])
{
	std::cout << "WHY SO SERIOUS;)";

    PixelBuffer buffer(32, 32);
    buffer.addPallet(0xaa, 0xaa, 0xaa);   //0 -> background ->Void
    buffer.addPallet(0x31, 0x35, 0x3f);   //1 -> Cell
    buffer.addPallet(0x31, 0x35, 0x3f);   //2 -> BlockFalse
    buffer.addPallet(0xf4, 0xf5, 0xf4);   //3 -> BlockTrue
    buffer.addPallet(0xc0, 0xb8, 0x9b);     //4 -> Cursor
 
    SDLWindow window(SCREEN_WIDTH, SCREEN_HEIGHT, 16, "SDL");
    IEngine* engine= new PixelEngine(&buffer);
    window.run(engine);

	return 0;
}
