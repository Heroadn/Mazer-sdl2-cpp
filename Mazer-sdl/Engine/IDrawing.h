#ifndef IDRAWING_H
#define IDRAWING_H
#include <string>

class IDrawing
{
public:
	virtual ~IDrawing() = 0;

	virtual void clear(
		uint8_t r,
		uint8_t g,
		uint8_t b,
		uint8_t a) = 0;

	virtual void drawText(
		int x, 
		int y, 
		std::string &text) = 0;

	virtual void drawSquare(
		int x,
		int y,
		int width,
		int height,
		uint8_t r,
		uint8_t g,
		uint8_t b) = 0;

	virtual int show() = 0;

	virtual int maxWidth() = 0;

	virtual int maxHeight() = 0;

	//virtual int resize(
	//	int width, 
	//	int height) = 0;
};

inline IDrawing::~IDrawing() {}

#endif
