#include "SDLInput.h"
#include <cstdint>
#include <stdio.h>
#include <SDL.h>

struct SDLInput::Impl
{
public:
	bool mKeys[256] = { 0 };
	bool mSystemCloseRequest;

	enum Event
	{
		Event_Keyboard,
		Event_Mouse,
		Event_System
	};

	Impl()
	{
		mSystemCloseRequest = false;
	}

	~Impl()
	{
	}

	Event getEventType(int type)
	{
		switch (type)
		{
		case SDL_KEYDOWN: 
		case SDL_KEYUP:
			return Event::Event_Keyboard;
			break;
		case SDL_MOUSEMOTION: 
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
			return Event::Event_Mouse;
		default:
			return Event::Event_System;
		}
	}

	void handle() {
		SDL_Event e;

		while (SDL_PollEvent(&e) != 0)
		{
			//if (id != e.window.windowID)
			//	return;

			//keyboard
			switch (getEventType(e.type)) {
			case Event_Keyboard:
				handleKeyboard(e);
				break;
			case Event_Mouse:
				handleMouse(e);
				break;
			case Event_System:
				handleSystem(e);
				break;
			default:
				break;
			}
		}
	}

	void handleMouse(SDL_Event& e)
	{
		/*
		fprintf(
			stderr, 
			"MOUSE HANDLER NOT IMPLEMENTED");*/
	}

	void handleSystem(SDL_Event& e)
	{
		switch (e.window.event)
		{
		case SDL_WINDOWEVENT_CLOSE:
			mSystemCloseRequest = true;
			break;
		default:
			break;
		}
	}

	void handleKeyboard(SDL_Event &e)	 
	{
		switch (e.type)
		{
		case SDL_KEYDOWN:
			mKeys[e.key.keysym.scancode] = true;
			break;
		case SDL_KEYUP:
			mKeys[e.key.keysym.scancode] = false;
			break;
		default:
			break;
		}
	}
};

SDLInput::SDLInput()
{
	mImpl = new SDLInput::Impl();
}

SDLInput::~SDLInput()
{
	delete mImpl;
}

void SDLInput::remap(
	int souceCode, 
	int targetCode)
{
}

bool SDLInput::getKey(int code)
{
	//Add bounds checking
	return mImpl->mKeys[code];
}

void SDLInput::poll()
{
	mImpl->handle();
}

bool SDLInput::isCloseRequest()
{
	return mImpl->mSystemCloseRequest;
}
