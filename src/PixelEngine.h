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
	PixelBuffer *mbBuffer;
	std::vector<Maze> mazes;
	std::vector<std::tuple<int, int>> positions;

	int nMazesWidth  = 0;
	int nMazesHeight = 0;
	int nMazes = 0;

	void mazeTobuffer(int ox, int oy, Maze& maze);
};