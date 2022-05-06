// Mazer-sdl.cpp: define o ponto de entrada para o aplicativo.
//
//#define SDL_MAIN_HANDLED
#include "Mazer-sdl.h"
#include "Maze.h"
#include "Graphics.h"
#include <SDL.h>
#include <cstdio>

#define MAZE_WIDTH  15
#define MAZE_HEIGHT 15
#define SCREEN_WIDTH 200
#define SCREEN_HEIGHT 200
//#define SCREEN_WIDTH 960
//#define SCREEN_HEIGHT 544

inline uint32_t get_tick()
{
    return SDL_GetTicks();
}

inline void sleep(uint32_t ms)
{
    SDL_Delay(ms);
}

int WinMain(int argc, char* argv[])
{
    freopen("output.txt", "w", stdout);
    freopen("error.txt", "w", stderr);

	std::cout << "WHY SO SERIOUS;)";
    const uint8_t color[5][3] = {{0xaa, 0xaa, 0xaa},    //0 -> background ->Void
                                 {0x31, 0x35, 0x3f},    //1 -> Cell
                                 {0x31, 0x35, 0x3f},    //2 -> BlockFalse
                                 {0xf4, 0xf5, 0xf4},    //3 -> BlockTrue
                                 {0xc0, 0xb8, 0x9b}};   //4 -> Cursor

	Maze maze(MAZE_WIDTH,  MAZE_HEIGHT, Tile(0, 1));
    Maze maze2(MAZE_WIDTH, MAZE_HEIGHT, Tile(0, 1));
    Maze maze3(MAZE_WIDTH, MAZE_HEIGHT, Tile(0, 1));
    Maze maze4(MAZE_WIDTH, MAZE_HEIGHT, Tile(0, 1));
    Graphics graph(SCREEN_WIDTH, SCREEN_HEIGHT, 16, color, "SDL");


    uint32_t last = 0;
    uint32_t now = 0;
    uint32_t delay = 0;
    uint32_t ticks_per_sec = 1000 / 30;

    //While application is running
    while (!graph.is_close_request())
    {
        graph.input();

        last = get_tick();
        {
            graph.clear();

            //generate maze
            maze.generate_step();
            maze2.generate_step();
            maze3.generate_step();
            maze4.generate_step();

            //drawing
            graph.draw_sprite(maze.getWidth(), 0, maze2.getWidth(), maze2.getHeight(), maze2.tile_to_pixel());
            graph.draw_sprite(0, 0, maze.getWidth(), maze.getHeight(), maze.tile_to_pixel());

            graph.draw_sprite(maze.getWidth(), maze.getHeight(), maze2.getWidth(), maze2.getHeight(), maze3.tile_to_pixel());
            graph.draw_sprite(0, maze.getHeight(), maze.getWidth(), maze.getHeight(), maze4.tile_to_pixel());

            //screen
            graph.render(); 
        }
        now = get_tick();
        delay = ticks_per_sec - (now - last);
        sleep(delay);
    }

    graph.~Graphics();
    maze.~Maze();
    maze2.~Maze();
    maze3.~Maze();
    maze4.~Maze();
	return 0;
}
