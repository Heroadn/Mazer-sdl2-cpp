#include <vector>

class PixelBuffer
{
public:
	typedef struct Pixel Pixel;

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
	 * @param sprite[]. array of pixels.
	 * sprites will be read as "bidimensional[x + y * width]"
	 * ex: 11112222
	 *	   10012112
	 *	   10012111
	 *	   11112222
	 * "0, 1, 2" are indexes for colors
	 */
	void addPixels(
		uint8_t offset_x,
		uint8_t offset_y,
		uint8_t width,
		uint8_t height,
		uint8_t pallet_indexes[]);
	
	void addPallet(
		uint8_t r,
		uint8_t g,
		uint8_t b);

	const Pixel& PixelBuffer::getPixel(
		int x, 
		int y);

	uint8_t getRed(Pixel pixel);

	uint8_t getGreen(Pixel pixel);

	uint8_t getBlue(Pixel pixel);

	int getWidth();

	int getHeight();

private:
	int m_width;
	int m_height;
	
	uint8_t *m_buffer;
	std::vector<Pixel> m_pallet;
};
