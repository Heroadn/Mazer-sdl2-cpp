#ifndef IINPUT_H
#define IINPUT_H
#include <string>

class IInput
{
public:
	virtual ~IInput() = 0;

	//return if the key'code' is pressed
	virtual bool getKey(int code) = 0;

	//remap key souce to target
	virtual void remap(
		int souceCode, 
		int targetCode) = 0;

	virtual void poll() = 0;

	virtual bool isCloseRequest() = 0;
};

inline IInput::~IInput() {}

#endif
