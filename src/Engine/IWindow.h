#ifndef IWINDOW_H
#define IWINDOW_H
#include <string>
#include "IEngine.h"

class IWindow
{
public:
	virtual ~IWindow() = 0;

	virtual void run(IEngine* graphics) = 0;

	virtual int sizeWidth() = 0;

	virtual int sizeHeight() = 0;
};

inline IWindow::~IWindow() {}

#endif
