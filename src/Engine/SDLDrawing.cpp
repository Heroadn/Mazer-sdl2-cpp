#include "SDLDrawing.h"
#include <iostream>

SDLDrawing::SDLDrawing(
	SDL_Renderer* renderer,
	int width,
	int height)
	:
	renderer(renderer),
	mWidth(width),
	mHeight(height)
{
	clear(0xbb, 0xaa, 0xaa, 0x00);
}

SDLDrawing::~SDLDrawing()
{
}

void SDLDrawing::drawText(
	int x, 
	int y, 
	std::string& text)
{
}

void SDLDrawing::drawSquare(
	int x,
	int y,
	int width,
	int height,
	uint8_t r,
	uint8_t g,
	uint8_t b)
{
	SDL_Rect rect = { x * width, y * height, width, height};

	SDL_SetRenderDrawColor(renderer, r, g, b, 255);

	// Render rect
	SDL_RenderFillRect(renderer, &rect);
}

int SDLDrawing::show()
{
	SDL_RenderPresent(renderer);
	return 0;
}

void SDLDrawing::clear(
	uint8_t r,
	uint8_t g,
	uint8_t b,
	uint8_t a)
{

	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_RenderClear(renderer);
}

int SDLDrawing::maxWidth()
{
	return mWidth;
}

int SDLDrawing::maxHeight()
{
	return mHeight;
}
