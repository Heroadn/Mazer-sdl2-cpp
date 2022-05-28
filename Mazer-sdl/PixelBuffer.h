#include <vector>
#include <cstdint>

#ifndef IPIXELBUFFER_H
#define IPIXELBUFFER_H

class PixelBuffer
{
public:

	/**
	 * Constructor.
	 *
	 * @param width.					width of the buffer
	 * @param height.					height of the buffer
	 */
	PixelBuffer(
		const int width,
		const int height);

	~PixelBuffer();

	/**
	 * Clear buffer
	 */
	void clear();

	/**
	 * Add pixels to the buffer
	 *
	 * @param offset_x. where to put in x axis
	 * @param offset_y. where to put in y axis
	 * @param width.	width of the sprite
	 * @param height.	height of the sprite
	 * @param pixels[]. '2d' array of pixels.
	 * sprites will be read as "bidimensional[x + y * width]"
	 * ex: 11112222
	 *	   10012112
	 *	   10012111
	 *	   11112222
	 * "0, 1, 2" are indexes for colors
	 * if the ofsets are greater than buffer width or height 
	 * it will wrap around the opposite direction
	 * 
	 * if the width or height are greater than buffer's it will be
	 * truncated to buffer's width and height
	 */
	void addPixels(
		const uint8_t offset_x,
		const uint8_t offset_y,
		const uint8_t width,
		const uint8_t height,
		const uint8_t pallet_indexes[]);
	
	void addPallet(
		uint8_t r,
		uint8_t g,
		uint8_t b);

	void getPixelColor(
		const int x, 
		const int y,
		uint8_t& r,
		uint8_t& g,
		uint8_t& b);

	const int getWidth();

	const int getHeight();

private:
	struct Pixel
	{
		uint8_t r;
		uint8_t g;
		uint8_t b;
	};

	int m_width;
	int m_height;
	
	uint8_t *m_buffer;
	std::vector<Pixel> m_pallet;
};

#endif
