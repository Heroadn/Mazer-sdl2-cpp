#include "PixelEngine.h"
#include <stdio.h>

#define MAZE_WIDTH  15
#define MAZE_HEIGHT 15

//rename to pixel engine or maze engine
PixelEngine::PixelEngine(PixelBuffer* buffer)
	:
	mMaze(Maze(MAZE_WIDTH, MAZE_HEIGHT, Tile(0, 1))),
	mMaze2(Maze(MAZE_WIDTH, MAZE_HEIGHT, Tile(0, 1))),
	mMaze3(Maze(MAZE_WIDTH, MAZE_HEIGHT, Tile(0, 1))),
	mMaze4(Maze(MAZE_WIDTH, MAZE_HEIGHT, Tile(0, 1))),
	mbBuffer(buffer)
{
}

PixelEngine::~PixelEngine()
{
}

void PixelEngine::render(IDrawing *draw)
{
	uint8_t r = 0xbb, g = 0xaa, b = 0xaa;
	int pixelWidth  = (int)ceil((double)draw->maxWidth()  / mbBuffer->getWidth());
	int pixelHeight = (int)ceil((double)draw->maxHeight() / mbBuffer->getHeight());

	//drawing all pixels in the buffer
	for (int y = 0; y < mbBuffer->getHeight(); y++)
	{
		for (int x = 0; x < mbBuffer->getWidth(); x++)
		{
			//getting pixel color
			mbBuffer->getPixelColor(
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
	mbBuffer->addPixels(
		0, 
		0, 
		mMaze.getWidth(), 
		mMaze.getHeight(), 
		mMaze.tile_to_pixel());

	mbBuffer->addPixels(
		mMaze2.getWidth(), 
		0, 
		mMaze2.getWidth(), 
		mMaze2.getHeight(), 
		mMaze2.tile_to_pixel());

	mbBuffer->addPixels(
		mMaze3.getWidth(), 
		mMaze3.getHeight(), 
		mMaze3.getWidth(), 
		mMaze3.getHeight(), 
		mMaze3.tile_to_pixel());

	mbBuffer->addPixels(
		0, 
		mMaze4.getHeight(), 
		mMaze4.getWidth(), 
		mMaze4.getHeight(), 
		mMaze4.tile_to_pixel());
}

void PixelEngine::clear() 
{
}