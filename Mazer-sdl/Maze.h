#include <vector>
#include <stack>
#include <time.h>
#include "Tile.h"

class Maze
{
private:
    std::stack<Tile> m_track;       //used to keep track of the path
    std::vector<Tile> m_unvisited;

    Tile* m_grid;                   //tile representation of grid
    uint8_t* m_pixels;              //pixel representation of grid

    Tile m_start;                   //where to start in the grid
    Tile m_cursor;                  //current location in the grid
    int m_width;                    //width of the Maze
    int m_height;                   //height of the Maze
public:
    Maze(int width,
        int height,
        Tile start);
   
    ~Maze();

    /**
     * Description.
     * @param name.					description
     */
    void fill_grid();

    /**
     * Walk 'm_grid' removing walls and backtraking if necessary
     * @param choices.					unvisited elements
     */
    void walk_grid(const std::vector<Tile> choices);

    /**
     * Search unvisited elements around m_cursor
     * @param unvisited.			fill '&unvisited' with unvisited elements around m_cursor
     */
    void search_unvisited(std::vector<Tile>& unvisited);

    /**
     * Generates part of the maze
     * @return true when there's elements to be visited, otherwise false
     */
    bool generate_step();

    /**
     * Generates all the maze
     */
    void generate_full();

    /**
     * Removing walls between 'source', '&target'
     * @param choices.					unvisited elements
     */
    void remove_wall(Tile source, Tile& target);

    /**
     * check if index of 'm_grid'[x][y] is out of bounds
     * @param x.					x element axis
     * @param y.					y element axis
     * @param width.				width of 'm_grid'
     * @param height.				height of 'm_grid'
     * @return true when out of bounds, otherwise false
     */
    bool is_out_bounds(int x, int y, int width, int height);

    /**
     * the representation of tiles in pixels
     * @return the representation of 'm_grid' for pixels
     */
    uint8_t* tile_to_pixel();

    int getWidth() { return m_width; }
    int getHeight() { return m_height; }
    Tile getCursor() { return m_cursor; }
};