#ifndef SDLDRAWING_H
#define SDLDRAWING_H
#include "IDrawing.h"
#include <SDL.h>

class SDLDrawing : public IDrawing
{
public:
	SDLDrawing(
		SDL_Renderer* renderer,
		int width, 
		int height);

	~SDLDrawing();

	void drawText(
		int x,
		int y,
		std::string& text);

	void drawSquare(
		int x,
		int y,
		int width,
		int height,
		uint8_t r,
		uint8_t g,
		uint8_t b);

	void clear(
		uint8_t r,
		uint8_t g,
		uint8_t b,
		uint8_t a);

	int show();

	int maxWidth();

	int maxHeight();
private:
	SDL_Renderer* renderer;
	int mWidth, mHeight;
};

#endif
