#include "PixelBuffer.h"
#include <stdlib.h>
#include <iostream>
#include <string.h>

PixelBuffer::PixelBuffer(
	const int width,
	const int height): m_width(width),
					   m_height(height)
{
	m_buffer = new uint8_t[m_width * m_height];
	memset(m_buffer, 0, m_width * m_height);
}

PixelBuffer::~PixelBuffer()
{
	delete[] m_buffer;
}

void PixelBuffer::clear()
{
}

void PixelBuffer::addPixels(
	const uint8_t offset_x,
	const uint8_t offset_y,
	const uint8_t width,
	const uint8_t height,
	const uint8_t pallet_indexes[])
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


void PixelBuffer::getPixelColor(
	const int x,
	const int y,
	uint8_t& r,
	uint8_t& g,
	uint8_t& b)
{
	uint8_t index = m_buffer[x + m_width * y];
	if (index > m_pallet.size())
	{
		std::cout << "Err Pallet index out of bounds" << index << " -- Check if the pallet has been added before" 
				  << std::endl;
		exit(EXIT_FAILURE);
	}

	Pixel pixel = m_pallet[index];
	r = pixel.r;
	g = pixel.g;
	b = pixel.b;
}

const int PixelBuffer::getWidth()
{
	return m_width;
}

const int PixelBuffer::getHeight()
{
	return m_height;
}



