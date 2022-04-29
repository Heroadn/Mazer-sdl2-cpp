#include "Graphics.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

Graphics::Graphics(const int screen_width,
				   const int screen_height,
				   const int bits_per_pixel,
				   const uint8_t colors[LAYERS][CHANNELS],
				   const char* title)
{
	m_screen_width   = screen_width;
	m_screen_height  = screen_height;
	m_bits_per_pixel = bits_per_pixel;
	m_pixel_width    = (int)ceil((double)screen_width  / INTERNAL_WIDTH);
	m_pixel_height   = (int)ceil((double)screen_height / INTERNAL_HEIGHT);

	//moving colors to the struct
	memcpy(m_colors, colors,
		CHANNELS * LAYERS * sizeof(uint8_t));

	memset(m_screen_pixels, 0,
		INTERNAL_WIDTH * INTERNAL_HEIGHT);

	//Start SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
	{
		exit(EXIT_FAILURE);
	}

	m_window = Graphics::init_window(title);
	m_screen = Graphics::init_screen();

	Graphics::clear();
	Graphics::update();
}

Graphics::~Graphics()
{
	//Quit SDL
	SDL_DestroyWindow(m_window);
	SDL_QuitSubSystem(SDL_INIT_EVERYTHING);
	SDL_Quit();
}

void Graphics::draw_pixel(SDL_Rect rect,
					      uint8_t colors[])
{
	uint32_t color = SDL_MapRGB(m_screen->format,
								colors[0],
								colors[1],
								colors[2]);

	SDL_FillRect(m_screen,
				 &rect,
				 color);
}

//
void Graphics::draw_screen()
{
	SDL_Rect rect = { 0, 0, m_pixel_width, m_pixel_height };
	uint8_t* colors;

	for (int y = 0; y < INTERNAL_HEIGHT; y++)
	{
		for (int x = 0; x < INTERNAL_WIDTH; x++)
		{
			// can be precalculated
			rect.x = x * m_pixel_width;
			rect.y = y * m_pixel_height;
			colors = m_colors[m_screen_pixels[x][y]];
			draw_pixel(rect, colors);
		}
	}
}

//
void Graphics::draw_sprite(uint8_t offset_x,
						   uint8_t offset_y,
						   uint8_t width,
						   uint8_t height,
						   uint8_t sprite[])
{
	uint8_t x = 0, y = 0, i = 0;

	for (int r = 0; r < height; r++)//height
	{
		for (int c = 0; c < width; c++)//width
		{
			x = (offset_x + c) % INTERNAL_WIDTH;
			y = (offset_y + r) % INTERNAL_HEIGHT;

			i = (r * width) + c;
			m_screen_pixels[x][y] = sprite[i];
		}
	}
}

void Graphics::draw_sprite(uint8_t offset_x,
						   uint8_t offset_y,
						   uint8_t width,
						   uint8_t height,
						   std::vector<uint8_t> &sprite)
{
	uint8_t x = 0, y = 0, i = 0;

	for (int r = 0; r < height; r++)//height
	{
		for (int c = 0; c < width; c++)//width
		{
			x = (offset_x + c) % INTERNAL_WIDTH;
			y = (offset_y + r) % INTERNAL_HEIGHT;

			i = (r * width) + c;
			m_screen_pixels[x][y] = sprite[i];
		}
	}
}

//
void Graphics::clear()
{
	//Fill the surface white
	SDL_FillRect(m_screen, 
				 NULL, 
				 SDL_MapRGB(m_screen->format, m_colors[0][0], m_colors[0][1], m_colors[0][2]));
}

//
void Graphics::update()
{
	SDL_UpdateWindowSurface(m_window);
}

//
SDL_Window* Graphics::init_window(const char* title)
{
	SDL_Window* window = NULL;

	//Create window
	window = SDL_CreateWindow(title,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		m_screen_width,
		m_screen_height,
		SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	return window;
}

//
SDL_Surface* Graphics::init_screen()
{
	SDL_Surface* screen = NULL;

	//Set up screen
	screen = SDL_GetWindowSurface(m_window);

	//setsid
	if (screen == NULL)
	{
		fprintf(stderr, "Error when creating window\n");
		fprintf(stderr,  "Error: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	return screen;
}

