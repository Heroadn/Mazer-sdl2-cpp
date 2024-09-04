#ifndef IENGINE_H
#define IENGINE_H

#include "IInput.h"
#include "IDrawing.h"

class IEngine
{
public:
	virtual ~IEngine() = 0;

	virtual void update() = 0;

	virtual void clear() = 0;

	virtual void render(IDrawing* draw) = 0;

	virtual void input(IInput* input) = 0;
};

inline IEngine::~IEngine() {}

#endif
