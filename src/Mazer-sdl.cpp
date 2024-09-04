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
 
    SDLWindow window(SCREEN_WIDTH, SCREEN_HEIGHT, 16, "SDL");
    IEngine* engine= new PixelEngine();
    window.run(engine);

	return 0;
}
