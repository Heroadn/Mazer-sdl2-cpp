#include "Graphics.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//separar buffer e graphics SDL
Graphics::Graphics(const int screen_width,
				   const int screen_height,
				   const int bits_per_pixel,
				   const uint8_t colors[LAYERS][CHANNELS],
				   const char* title)
{
	m_screen_width     = screen_width;
	m_screen_height    = screen_height;
	m_bits_per_pixel   = bits_per_pixel;
	m_is_close_request = false;
	m_pixel_width      = (int)ceil((double)screen_width  / INTERNAL_WIDTH);
	m_pixel_height     = (int)ceil((double)screen_height / INTERNAL_HEIGHT);

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
	Graphics::render();
}

Graphics::~Graphics()
{
	//Quit SDL
	SDL_DestroyWindow(m_window);
	SDL_QuitSubSystem(SDL_INIT_EVERYTHING);
	SDL_Quit();
}

void Graphics::clear()
{
	//Fill the surface white
	fill_rect(m_screen, NULL, m_colors[0]);

	//m_screen_pixels -> should be clened
}

void Graphics::render()
{
	draw_buffer();
	SDL_UpdateWindowSurface(m_window);
}

void Graphics::input()
{
	//Event handler
	SDL_Event e;

	//Handle events on queue
	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_WINDOWEVENT
			&& SDL_GetWindowID(m_window) == e.window.windowID)
		{
			switch (e.window.event)
			{
			case SDL_WINDOWEVENT_CLOSE:
				m_is_close_request = true;
				break;
			default:
				break;
			}
		}
	}
}

//draw_pixel
void Graphics::draw_pixel(int x, 
						  int y, 
						  uint8_t color)
{
	m_screen_pixels[x][y] = color;
}


void Graphics::fill_rect(SDL_Surface* screen,
						  SDL_Rect* rect,
					      uint8_t colors[])
{
	uint32_t color = SDL_MapRGB(screen->format,
								colors[0],
								colors[1],
								colors[2]);

	SDL_FillRect(screen,
				 rect,
				 color);
}

//
void Graphics::draw_buffer()
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
			fill_rect(m_screen, &rect, colors);
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

bool Graphics::is_close_request() {
	return m_is_close_request;
};
