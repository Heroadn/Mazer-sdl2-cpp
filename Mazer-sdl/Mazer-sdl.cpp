// Mazer-sdl.cpp: define o ponto de entrada para o aplicativo.
//
//#define SDL_MAIN_HANDLED
#include "Mazer-sdl.h"
#include "Maze.h"
#include "Graphics.h"
#include <SDL.h>
#include <cstdio>

#define WIDTH 10
#define HEIGHT 10

//Main loop flag
bool quit = false;

void input()
{
    //Event handler
    static SDL_Event e;

    //Handle events on queue
    while (SDL_PollEvent(&e) != 0)
    {
        //User requests quit
        if (e.type == SDL_QUIT)
        {
            quit = true;
        }

    }
}

int WinMain(int argc, char* argv[])
{
    using namespace std;
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);

	std::cout << "PORQUE ESTA TAO SERIO;)";
    const uint8_t color[5][3] = {{0xaa, 0xaa, 0xaa},    //0 -> background ->Void
                                 {0xff, 0xff, 0xff},    //1 -> Cell
                                 {0xff, 0xff, 0xff},    //2 -> BlockFalse
                                 {0x00, 0x00, 0x00},    //3 -> BlockTrue
                                 {0x00, 0x00, 0xff}};   //4 -> Cursor

    /*
    const uint8_t color[5][3] = {{0xff, 0xff, 0xff},    //0 -> background ->Void
                                 {0xff, 0x00, 0x00},    //1 -> Cell
                                 {0xff, 0x00, 0x00},    //2 -> BlockFalse
                                 {0xff, 0xff, 0xff} ,   //3 -> BlockTrue
                                 {0x00, 0x00, 0x00} };  //4
    */
    //paleta -> amarelo, vermelho, preto e branco
    
	Maze maze(10, 10, Tile(0, 1));
    Maze maze2(10, 10, Tile(0, 1));
    Graphics graph(960, 544, 16, color, "SDL");

    uint32_t last = 0;
    uint32_t now = 0;
    uint32_t delay = 0;
    uint32_t ticks_per_sec = 1000 / 15;

    //While application is running
    while (!quit)
    {
        input();

        last = SDL_GetTicks();
        {
            graph.clear();
            maze.generate();
            maze2.generate();
            graph.draw_sprite(4 + maze.getWidth(), 4, maze2.getWidth(), maze2.getHeight(), maze2.tile_to_pixel());
            graph.draw_sprite(4, 4, maze.getWidth(), maze.getHeight(), maze.tile_to_pixel());
            graph.draw_screen();
            graph.update(); 
        }
        now = SDL_GetTicks();
        delay = ticks_per_sec - (now - last);
        SDL_Delay(delay);
    }
    graph.~Graphics();
    

	return 0;
}
