#include "Engine\IEngine.h"
#include "PixelBuffer.h"
#include "Maze.h"

class PixelEngine : public IEngine
{
public:
	PixelEngine();

	~PixelEngine();

	void update();

	void clear();

	void render(IDrawing *draw);

	void input(IInput *input);

	static IEngine* create() { return new PixelEngine(); }
private:
	PixelBuffer mbBuffer;
	Maze mMaze;
	Maze mMaze2;
	Maze mMaze3;
	Maze mMaze4;

	void mazeTobuffer(int ox, int oy, Maze& maze);
};