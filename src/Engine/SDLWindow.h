/*
Class responsible for initiating things like SDL
*/
#include <cstdint>
#include "IWindow.h"

class SDLWindow : public IWindow
{
public:
	/**
	 * Constructor.
	 *
	 * @param screen_width.					width of the screen
	 * @param screen_height.				height of the screen
	 * @param bits_per_pixel.				bits per pixel
	 * @param title.						array of pixels in "hexadecimal".
	 */
	SDLWindow(const int screen_width,
			const int screen_height,
			const int bits_per_pixel,
			const char* title);

	~SDLWindow();

	void run(IEngine* graphics);

	int sizeWidth();

	int sizeHeight();
private:
	SDLWindow(SDLWindow  const&) = delete;

	struct Impl;
	Impl* mImpl;
};
