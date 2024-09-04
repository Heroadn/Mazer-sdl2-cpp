#include "PixelEngine.h"
#include <stdio.h>

#define MAZE_WIDTH  15
#define MAZE_HEIGHT 15

//rename to pixel engine or maze engine
PixelEngine::PixelEngine()
	:
	mMaze(Maze(MAZE_WIDTH, MAZE_HEIGHT, Tile(0, 1))),
	mMaze2(Maze(MAZE_WIDTH, MAZE_HEIGHT, Tile(0, 1))),
	mMaze3(Maze(MAZE_WIDTH, MAZE_HEIGHT, Tile(0, 1))),
	mMaze4(Maze(MAZE_WIDTH, MAZE_HEIGHT, Tile(0, 1))),
	mbBuffer(PixelBuffer(32, 32))
{
	mbBuffer.addPallet({
		{ 0x0f, 0x11, 0x08}, //0 -> background ->Void 
		{ 0x24, 0x19, 0x09 }, //1 -> Cell
		{ 0x31, 0x35, 0x3f }, //2 -> BlockFalse
		{ 0xf4, 0xf5, 0xf4 }, //3 -> BlockTrue
		{ 0x64, 0x58, 0x53 }  //4 -> Cursor
		});

	mbBuffer.addPallet({
		{ 0xaa, 0xaa, 0xaa }, //0 -> background ->Void 
		{ 0x31, 0x35, 0x3f }, //1 -> Cell
		{ 0x31, 0x35, 0x3f }, //2 -> BlockFalse
		{ 0xf4, 0xf5, 0xf4 }, //3 -> BlockTrue
		{ 0xc0, 0xb8, 0x9b }  //4 -> Cursor
	});
}

PixelEngine::~PixelEngine()
{
}

void PixelEngine::render(IDrawing *draw)
{
	uint8_t r = 0xbb, g = 0xaa, b = 0xaa;
	int pixelWidth  = (int)ceil((double)draw->maxWidth()  / mbBuffer.getWidth());
	int pixelHeight = (int)ceil((double)draw->maxHeight() / mbBuffer.getHeight());
	//draw->clear(0xaa, 0xff, 0xbb,0xff);

	//drawing all pixels in the buffer
	for (int y = 0; y < mbBuffer.getHeight(); y++)
	{
		for (int x = 0; x < mbBuffer.getWidth(); x++)
		{
			//getting pixel color
			mbBuffer.getPixelColor(
				x, 
				y, 
				r, 
				g, 
				b);

			//drawing pixel at pos
			draw->drawSquare(
				x, 
				y,
				pixelWidth,
				pixelHeight,
				r, 
				g, 
				b);
		}

		draw->show();
	}
}

void PixelEngine::input(IInput *input)
{
	/*
	if (input->getKey(SDL_SCANCODE_A))
	{
		printf("HELLO ;)");
	}
	*/
}

void PixelEngine::update()
{
	mMaze.generate_step();
	mMaze2.generate_step();
	mMaze3.generate_step();
	mMaze4.generate_step();
	
	//add mazes to pixelbuffer
	mazeTobuffer(
		0, 
		0, 
		mMaze);

	mazeTobuffer(
		mMaze2.getWidth(),
		0,
		mMaze2);

	mazeTobuffer(
		mMaze3.getWidth(),
		mMaze3.getHeight(),
		mMaze3);

	mazeTobuffer(
		0,
		mMaze4.getHeight(),
		mMaze4);
}

void PixelEngine::clear() 
{
}

void PixelEngine::mazeTobuffer(int ox, int oy, Maze& maze)
{
	for (size_t x = 0; x < maze.getWidth(); x++)
	{
		for (size_t y = 0; y < maze.getHeight(); y++)
			mbBuffer.addPixel(
				ox + x,
				oy + y,
				maze.grid()[x + y * maze.getWidth()].getType());
	}

	int cx = maze.getCursor().getX();
	int cy = maze.getCursor().getY();

	mbBuffer.addPixel(
		ox + cx,
		oy + cy,
		Tile::Cursor);
	
}