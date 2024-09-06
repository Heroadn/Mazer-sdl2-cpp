#include <vector>
#include <iostream>
#include <cstdint>

#ifndef IPIXELBUFFER_H
#define IPIXELBUFFER_H

/*
Class is responsible for
storing the representation of pixels
that can be called using indexes from an already registered pallet
(abstraction for indirect color indexing basicaly)
*/
class PixelBuffer
{
public:
	//
	struct Pixel
	{
		uint8_t r;
		uint8_t g;
		uint8_t b;
	};

	/**
	 * Constructor.
	 *
	 * @param width.					width of the buffer
	 * @param height.					height of the buffer
	 */
	PixelBuffer(
		const int width,
		const int height) 
		: mWidth(width),
		mHeight(height),
		mIndex(0)
	{
		mBuffer = new uint8_t[mWidth * mHeight];
		memset(mBuffer, 0, mWidth * mHeight);
	}

	~PixelBuffer()
	{
		delete[] mBuffer;
	}

	/**
	 * Clears buffer
	 */
	void clear()
	{
		for (size_t i = 0; i < mHeight * mWidth; i++)
			mBuffer[i] = 0;
	}

	/**
	 * Adds a pixel to (x, y) with a color from pallet[index].
	 *
	 * @param x.					x position to put pixel
	 * @param y.					y position to put pixel
	 * @param index.			    index of the pallet
	 */
	void addPixel(
		const uint8_t x,
		const uint8_t y,
		const uint8_t index)
	{
		mBuffer[y * mWidth + x] = index;
	}

	/**
	 * adds a pallet.
	 *
	 * @param r.					x position to put pixel
	 * @param g.					y position to put pixel
	 * @param b.					color of the pixel
	 */
	void addPallet(
		std::vector<Pixel> colors)
	{
		mPallet.push_back(colors);
	}

	/**
	 * adds a pallet in the format 0xRRGGBB.
	 *
	 * @param color.				color to be added. ex. 0xRRGGBB
	 */
	void addPallet(
		std::vector<uint32_t> colors)
	{
		std::vector<Pixel> result;

		for (auto color : colors)
		{
			//0x5e, 0xc5, 0x7e
			//0xc5;
			uint8_t r = (color & 0x00FF0000) >> 16;
			uint8_t g = (color & 0x0000FF00) >> 8;
			uint8_t b = (color & 0x000000FF);
			result.push_back(Pixel{ r, g, b });
		}

		//
		addPallet(result);
	}

	void changePallet(int index)
	{
		if (index > mPallet.size())
		{
			std::cout
				<< "Err Pallet index out of bounds"
				<< index
				<< " -- Check if the pallet has been added before"
				<< std::endl;
			//exit(EXIT_FAILURE);
			return;
		}

		mIndex = index;
	}

	size_t sizePallets()
	{
		return mPallet.size();
	}

	/**
	 * adds a pallet.
	 *
	 * @param x.					x position of pixel in buffer
	 * @param y.					y position of pixel in buffer
	 * @param r.					r red component to be returned
	 * @param g.					g green component to be returned
	 * @param b.					b blue component to be returned
	 */
	void getPixelColor(
		const int x,
		const int y,
		uint8_t& r,
		uint8_t& g,
		uint8_t& b)
	{
		uint8_t index = mBuffer[x + mWidth * y];
		Pixel pixel = mPallet[mIndex][index];
		r = pixel.r;
		g = pixel.g;
		b = pixel.b;
	}

	const int getWidth()
	{
		return mWidth;
	}

	const int getHeight()
	{
		return mHeight;
	}

private:
	int mWidth;
	int mHeight;
	int mIndex = 0;

	uint8_t* mBuffer;
	std::vector<std::vector<Pixel>> mPallet;
};

#endif