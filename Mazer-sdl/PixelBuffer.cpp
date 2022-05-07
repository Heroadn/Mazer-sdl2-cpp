#include "PixelBuffer.h"

struct Pixel
{
	uint8_t r : 4;
	uint8_t g : 4;
	uint8_t b : 4;
};

PixelBuffer::PixelBuffer(
	const int width,
	const int height)
	: m_width(width),
	  m_height(height)
{
	m_buffer = new uint8_t[m_width * m_height];
}

PixelBuffer::~PixelBuffer()
{
	delete[] m_buffer;
}

void PixelBuffer::clear()
{
}

void PixelBuffer::addPixels(
	uint8_t offset_x,
	uint8_t offset_y,
	uint8_t width,
	uint8_t height,
	uint8_t pallet_indexes[])
{
	uint8_t x = 0, y = 0, i = 0;

	for (int r = 0; r < height; r++)
	{
		for (int c = 0; c < width; c++)
		{
			x = (offset_x + c) % m_width;
			y = (offset_y + r) % m_height;

			i = c + (r * width);
			m_buffer[x + m_width * y] = pallet_indexes[i];
		}
	}
}

void PixelBuffer::addPallet(
	uint8_t r,
	uint8_t g,
	uint8_t b)
{
	m_pallet.push_back(Pixel{ r, g, b });
}

const Pixel& PixelBuffer::getPixel(
	int x, 
	int y)
{
	return m_pallet[m_buffer[x + m_width * y]];
}

uint8_t PixelBuffer::getRed(Pixel pixel) { return pixel.r; }
uint8_t PixelBuffer::getGreen(Pixel pixel) { return pixel.g; }
uint8_t PixelBuffer::getBlue(Pixel pixel) { return pixel.b; }

int PixelBuffer::getWidth()
{
	return m_width;
}
int PixelBuffer::getHeight()
{
	return m_height;
}



