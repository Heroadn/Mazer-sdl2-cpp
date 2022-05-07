/*
Class responsible for initiating things like SDL,
and drawing sprites in the screen
uses a variation of the graphics lib for chip8
<https://github.com/Heroadn/Chip8Emu/>
*/

#include <SDL.h>
#include <vector>
#define INTERNAL_WIDTH  33		//width of internal pixel screen
#define INTERNAL_HEIGHT 33		//height of internal pixel screen
#define CHANNELS 3				//color chanels like RGB
#define LAYERS 5				//fixed amount of pallets <- should be dynamic

class Graphics
{
public:
	/**
	 * Constructor.
	 *
	 * @param screen_width.					width of the screen
	 * @param screen_height.				height of the screen
	 * @param bits_per_pixel.				bits per pixel
	 * @param title.						array of pixels in "hexadecimal".
	 * @param colors[LAYERS][CHANNELS].		pallet of the sprites
	 * sprites can use it as index for colors
	 */
	Graphics(const int screen_width,
			 const int screen_height,
			 const int bits_per_pixel,
			 const uint8_t colors[LAYERS][CHANNELS],
			 const char* title);

	~Graphics();

	/**
	 * Clear pixels in the screen
	 */
	void clear();

	/**
	 * render screen
	 */
	void render();//

	/**
	 * Check input, like close request
	 */
	void input();//

	/**
	 * Add pixels of sprite to the screen.
	 *
	 * @param offset_x. where to put in x axis
	 * @param offset_y. where to put in y axis
	 * @param width.	width of the sprite
	 * @param height.	height of the sprite
	 * @param sprite[]. array of pixels, they are indexes to the pallet(coloring).
	 * sprites will be read as "bidimensional[x + y * width]" 
	 * ex: 11112222   
	 *	   10012112
	 *	   10012111
	 *	   11112222
	 * "0, 1, 2" are indexes for colors
	 */
	void draw_sprite(uint8_t offset_x,
					 uint8_t offset_y,
					 uint8_t width,
					 uint8_t height,
					 uint8_t sprite[]);

	/**
	 * Add pixels of sprite to the screen.
	 *
	 * @param offset_x
	 * @param offset_y.
	 * @param width.
	 * @param height.
	 * @param sprite[]. vector of pixels, they are indexes to the pallet(coloring).
	 * sprites will be read as "bidimensional[x + y * width]" 
	 * ex: 11112222   
	 *	   10012112
	 *	   10012111
	 *	   11112222
	 * "0, 1, 2" are indexes for colors
	 */
	void draw_sprite(uint8_t offset_x,
					 uint8_t offset_y,
					 uint8_t width,
					 uint8_t height,
					 std::vector<uint8_t> &sprite);

	bool is_close_request();

private:
	SDL_Surface* m_screen;
	SDL_Window* m_window;

	int m_screen_width;
	int m_screen_height;
	int m_pixel_width;
	int m_pixel_height;
	int m_bits_per_pixel;
	int m_is_close_request;

	uint8_t m_screen_pixels[INTERNAL_WIDTH][INTERNAL_HEIGHT];
	uint8_t m_colors[LAYERS][CHANNELS];

	//
	SDL_Surface* init_screen();

	//
	SDL_Window* init_window(const char* title);

	/**
	 * Draw all pixels from buffer to the screen
	 */
	void draw_buffer();


	/**
	 * Draw a pixel into the buffer
	 */
	void draw_pixel(int x, 
					int y, 
					uint8_t color);

	/**
	 * Draw a pixel pixel into the screen
	 */
	void fill_rect(SDL_Surface* screen,
					SDL_Rect* rect,
					uint8_t colors[]);
};
