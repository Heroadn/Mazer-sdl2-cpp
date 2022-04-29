#include <SDL.h>
#include <vector>
#define INTERNAL_WIDTH  33
#define INTERNAL_HEIGHT 33
#define CHANNELS 3
#define LAYERS 4

class Graphics
{
public:
	Graphics(const int screen_width,
			 const int screen_height,
			 const int bits_per_pixel,
			 const uint8_t colors[LAYERS][CHANNELS],
			 const char* title);

	~Graphics();

	void draw_pixel(SDL_Rect rect,
				    uint8_t colors[]);

	//
	void draw_screen();

	//
	void clear();

	//
	void update();

	//
	void get_screen(uint8_t screen[INTERNAL_WIDTH][INTERNAL_HEIGHT]);

	//
	bool draw_sprite(uint8_t offset_x,
					 uint8_t offset_y,
					 uint8_t width,
					 uint8_t height,
					 uint8_t sprite[]);

	bool draw_sprite(uint8_t offset_x,
		uint8_t offset_y,
		uint8_t width,
		uint8_t height,
		std::vector<uint8_t> &sprite);

	//
	SDL_Surface* init_screen();

	//
	SDL_Window* init_window(const char* title);
private:
	SDL_Surface* m_screen;
	SDL_Window* m_window;

	int m_screen_width;
	int m_screen_height;
	int m_pixel_width;
	int m_pixel_height;
	int m_bits_per_pixel;

	uint8_t m_screen_pixels[INTERNAL_WIDTH][INTERNAL_HEIGHT];
	uint8_t m_colors[LAYERS][CHANNELS];
};
