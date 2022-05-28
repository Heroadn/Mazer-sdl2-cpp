#include "Engine\IEngine.h"
#include "PixelBuffer.h"
#include "Maze.h"

class PixelEngine : public IEngine
{
public:
	PixelEngine(PixelBuffer* buffer);

	~PixelEngine();

	void update();

	void clear();

	void render(IDrawing *draw);

	void input(IInput *input);

	static IEngine* create(PixelBuffer* buffer) { return new PixelEngine(buffer); }
private:
	PixelBuffer *mbBuffer;
	Maze mMaze;
	Maze mMaze2;
	Maze mMaze3;
	Maze mMaze4;
};