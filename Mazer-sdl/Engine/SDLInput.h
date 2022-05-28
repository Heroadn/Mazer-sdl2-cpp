#ifndef INPUT_H
#define INPUT_H

#include "IInput.h"

class SDLInput : public IInput
{
public:
	SDLInput();

	~SDLInput();

	bool getKey(int code);

	bool isCloseRequest();

	void remap(int souceCode, int targetCode);

	void poll();
private:
	//not copyable
	SDLInput(SDLInput const&) = delete;

	struct Impl;
	Impl* mImpl;
};

#endif
