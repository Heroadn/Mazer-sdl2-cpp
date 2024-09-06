#include "PixelEngine.h"
#include <stdio.h>

#define MAZE_WIDTH  10
#define MAZE_HEIGHT 10

#define DEBUG_SIZE_W 200
#define DEBUG_SIZE_H 200

//rename to pixel engine or maze engine
PixelEngine::PixelEngine() 
{
	//
	this->nMazesWidth  = DEBUG_SIZE_W / MAZE_WIDTH; 
	this->nMazesHeight = DEBUG_SIZE_H / MAZE_HEIGHT;
	this->nMazes = this->nMazesWidth * this->nMazesHeight;
	this->mbBuffer = new PixelBuffer(DEBUG_SIZE_W, DEBUG_SIZE_H);

	//initializing mazes
	for (size_t y = 0; y < this->nMazesHeight; y++)
	{
		for (size_t x = 0; x < this->nMazesWidth; x++)
		{
			this->mazes.push_back(Maze(MAZE_WIDTH, MAZE_HEIGHT, Tile(0, 1)));
			this->positions.push_back({ x, y });
		}
	}
 
	//
	mbBuffer->addPallet({
		{ 0x0f, 0x11, 0x08}, //0 -> background ->Void 
		{ 0x24, 0x19, 0x09 }, //1 -> Cell
		{ 0x31, 0x35, 0x3f }, //2 -> BlockFalse
		{ 0xf4, 0xf5, 0xf4 }, //3 -> BlockTrue
		{ 0x64, 0x58, 0x53 }  //4 -> Cursor
		});

	mbBuffer->addPallet({
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
	int pixelWidth  = (int)ceil((double)draw->maxWidth()  / mbBuffer->getWidth());
	int pixelHeight = (int)ceil((double)draw->maxHeight() / mbBuffer->getHeight());
	//draw->clear(0xaa, 0xff, 0xbb,0xff);

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
	//adds mazes to pixelbuffer
	for(int ip = 0; ip < this->nMazes; ip++)
	{
		this->mazes[ip].generate_step();
		mazeTobuffer(
			std::get<0>(this->positions[ip]) * MAZE_WIDTH,
			std::get<1>(this->positions[ip]) * MAZE_HEIGHT,
			this->mazes[ip]);
	}
}

void PixelEngine::clear() 
{
}

void PixelEngine::mazeTobuffer(int ox, int oy, Maze& maze)
{
	for (size_t x = 0; x < maze.getWidth(); x++)
	{
		for (size_t y = 0; y < maze.getHeight(); y++)
			mbBuffer->addPixel(
				ox + x,
				oy + y,
				maze.grid()[x + y * maze.getWidth()].getType());
	}

	int cx = maze.getCursor().getX();
	int cy = maze.getCursor().getY();

	mbBuffer->addPixel(
		ox + cx,
		oy + cy,
		Tile::Cursor);
	
}