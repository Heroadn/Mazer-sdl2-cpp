#include <SDL.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "SDLWindow.h"
#include "SDLInput.h"
#include "SDLDrawing.h"
#include <iostream>

#define FPS 30

struct SDLWindow::Impl
{
public:
	SDL_Window*   m_window;
	SDL_Renderer* m_renderer;


	int m_screen_width;
	int m_screen_height;
	int m_pixel_width;
	int m_pixel_height;
	int m_bits_per_pixel;
	int m_is_close_request;
	
	Impl(
		int bufferWidth, 
		int bufferHeight,
		int screenWidth,
		int screenHeight,
		int bpp,
		const char* title)
	{
		m_bits_per_pixel = bpp;
		m_screen_width   = screenWidth;
		m_screen_height  = screenHeight;

		//Start SDL
		if (SDL_Init(SDL_INIT_EVERYTHING) == -1)
		{
			exit(EXIT_FAILURE);
		}
		
		//create screen and window
		m_window = create_window(
			m_screen_width,
			m_screen_height,
			title);

		m_renderer = create_renderer(m_window);

	}

	SDL_Renderer* create_renderer(SDL_Window *window)
	{
		SDL_Renderer* renderer = SDL_CreateRenderer(
			window,
			-1,
			SDL_RENDERER_SOFTWARE);

		if (renderer == NULL)
		{
			std::cout << "ERROR: " << SDL_GetError() << std::endl;
			exit(EXIT_FAILURE);
		}

		return renderer;
	}

	~Impl()
	{
		SDL_DestroyWindow(m_window);
		SDL_QuitSubSystem(SDL_INIT_EVERYTHING);
		SDL_Quit();
	}

	//
	SDL_Surface* create_screen()
	{
		SDL_Surface* screen = NULL;

		//Set up screen
		screen = SDL_GetWindowSurface(m_window);

		//setsid
		if (screen == NULL)
		{
			fprintf(stderr, "Error when creating window\n");
			fprintf(stderr, "Error: %s\n", SDL_GetError());
			exit(EXIT_FAILURE);
		}

		return screen;
	}

	//
	SDL_Window* create_window(
		int width,
		int height,
		const char* title)
	{
		SDL_Window* window = NULL;

		//Create window
		window = SDL_CreateWindow(title,
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			width,
			height,
			SDL_WINDOW_SHOWN);

		if (window == NULL)
		{
			fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());
			exit(EXIT_FAILURE);
		}

		return window;
	}

	inline uint32_t get_tick()
	{
		return SDL_GetTicks();
	}

	inline void sleep(uint32_t ms)
	{
		SDL_Delay(ms);
	}

	/**
	 * Draw a pixel pixel into the screen
	 */
	void draw_pixel(
		SDL_Surface* screen,
		SDL_Rect* rect,
		const uint8_t& r,
		const uint8_t& g,
		const uint8_t& b)
	{
		uint32_t color = SDL_MapRGB(
			screen->format,
			r,
			g,
			b);

		SDL_FillRect(
			screen,
			rect,
			color);
	}

	void updateSurface()
	{
		SDL_UpdateWindowSurface(m_window);
	}
};

//separar buffer e graphics SDL
SDLWindow::SDLWindow(
	const int screen_width,
	const int screen_height,
	const int bits_per_pixel,
	const char* title)
{
	mImpl = new SDLWindow::Impl(
		33, 
		33, 
		screen_width, 
		screen_height, 
		bits_per_pixel, 
		title);
}

SDLWindow::~SDLWindow()
{
	delete mImpl;
}

void SDLWindow::run(IEngine *engine)
{
	uint32_t last = 0;
	uint32_t now = 0;
	uint32_t delay = 0;
	uint32_t ticks_per_sec = 1000 / FPS;
	uint32_t id = SDL_GetWindowID(mImpl->m_window);

	SDLInput sdlInput;
	SDLDrawing sdlDrawing(
		mImpl->m_renderer,
		mImpl->m_screen_width,
		mImpl->m_screen_height);
	
	
	while (sdlInput.isCloseRequest() == false)
	{
		sdlInput.poll();
		engine->input(&sdlInput);

		last = mImpl->get_tick();
		{
			engine->clear();
			engine->update();
			engine->render(&sdlDrawing);
		}

		now = mImpl->get_tick();
		delay = ticks_per_sec - (now - last);
		mImpl->sleep(delay);
	}
}

int SDLWindow::sizeWidth()
{
	return this->mImpl->m_screen_width;
}

int SDLWindow::sizeHeight()
{
	return this->mImpl->m_screen_height;
}
