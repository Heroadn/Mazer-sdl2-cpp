#include "IEngine.h"
#include <functional>
#include <map>
#include <string>

class GraphicsFactory
{
public:
	//typedef IGraphics* (*CreateCallback)(void*);
	typedef std::function<IEngine* (void*)> CreateCallback;

	static void registerGraphics(const std::string& type, CreateCallback cb);
	static void unregisterGraphics(const std::string& type);
	static IEngine* createGraphics(const std::string& type, void* arg);

private:
	typedef std::map<std::string, CreateCallback> CallbackMap;
	static CallbackMap mGraphics;
};