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
	struct Vector2i
	{
		int x = 0;
		int y = 0;
	};

	PixelBuffer mbBuffer;
	std::vector<Maze> mazes;
	std::vector<Vector2i> positions;

	int nMazesWidth  = 0;
	int nMazesHeight = 0;
	int nMazes = 0;

	void mazeTobuffer(int ox, int oy, Maze& maze);
};