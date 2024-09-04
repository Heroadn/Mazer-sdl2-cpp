#include "GraphicsFactory.h"
#include <string>
#include <stdlib.h>

GraphicsFactory::CallbackMap GraphicsFactory::mGraphics;

void GraphicsFactory::registerGraphics(
	const std::string& type, 
	CreateCallback cb)
{
	mGraphics[type] = cb;
}

void GraphicsFactory::unregisterGraphics(const std::string& type)
{
	mGraphics.erase(type);
}

IEngine* GraphicsFactory::createGraphics(const std::string& type, void* arg)
{
	CallbackMap::iterator it = mGraphics.find(type);
	if (it != mGraphics.end())
	{
		// call the creation callback to construct this derived type
		return (it->second)(arg);
	}
	return nullptr;
}
