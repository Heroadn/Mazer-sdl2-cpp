#include <vector>
#include <stack>
#include <time.h>
#include "Tile.h"

class Maze
{
private:
    std::stack<Tile> m_track;  //used to keep track of the path
    std::vector<Tile> m_unvisited;

    Tile* m_grid;          //tile representation of grid
    uint8_t* m_pixels;          //pixel representation of grid

    Tile m_start;               //where to start in the grid
    Tile m_cursor;              //current location in the grid
    int m_width;
    int m_height;
public:
    Maze(int width,
         int height,
         Tile start)
        :m_width(width),
        m_height(height), 
        m_start(start)
    { 
        m_grid = new Tile[width * height];
        m_pixels = new uint8_t[width * height];
        srand(time(0));

        int index = start.getX() + (start.getY() * m_width);

        //probably remove to just setType
        if (m_grid[index].getType() == Tile::Cell)
        {
            start.setType(Tile::BlockFalse);
            m_grid[index].setType(Tile::BlockFalse);
        }

        start.setVisited(true);
        m_track.push(start);
        m_cursor = start;
        fill_grid();
    }

    ~Maze() { 
        //delete[] m_grid;
        //delete[] m_pixels;
    }

    void fill_grid() {
        for (int y = 0; y < m_height; y++)
        {
            for (int x = 0; x < m_width; x++)
            {
                int index = x + (y * m_width);
                m_grid[index].setType(Tile::BlockTrue);

                if (y % 2 != 0 && x % 2 == 0)
                {
                    m_grid[index].setType(Tile::Cell);
                }
            }
        }
    }

    void search_unvisited_coordinates(std::vector<Tile> &unvisited) {

        for (int i = -1; i < 2; i++){
            for (int j = -1; j < 2; j++){
                int x = m_cursor.getX() + i;
                int y = m_cursor.getY() + j;
                int index = x + (y * m_width);

                //is_edge, is_middle
                if (is_out_bounds(x, y, m_width, m_height) || i != 0 && j != 0 || i == j)
                {
                    continue;
                }

                if (m_grid[index].getVisited() == false)
                {
                    m_grid[index].setX(x);
                    m_grid[index].setY(y);
                    unvisited.push_back(m_grid[index]);
                }
            }
        }
    }

    void generate()
    {
        if (m_track.empty())
            return;

        search_unvisited_coordinates(m_unvisited);
        generate_step(m_unvisited);
        m_unvisited.clear();
    }

    void generate_full()
    {
        while (m_track.empty() == false)
        {
            search_unvisited_coordinates(m_unvisited);
            generate_step(m_unvisited);
            m_unvisited.clear();
        }

    }

    /// just generate a portion of it
    void generate_step(const std::vector<Tile> choices) {
        Tile choice;

        //if theres no choices, move cursor back
        if (choices.empty())
        {
            choice = m_track.top();
            m_track.pop();
            m_cursor.setX(choice.getX());
            m_cursor.setY(choice.getY());
            return;
        }

        choice = choices[rand() % choices.size()];
        int now_index = choice.getX()   + (choice.getY()   * m_width);
        int old_index = m_cursor.getX() + (m_cursor.getY() * m_width);
        m_grid[now_index].setVisited(true);

        //push to the stack
        m_track.push(m_grid[now_index]);

        //remove wall
        Maze::remove_wall(
            m_grid[old_index],
            m_grid[now_index]
        );

        //changing target to neighbour
        m_cursor.setX(choice.getX());
        m_cursor.setY(choice.getY());
    }

    void remove_wall(Tile source, Tile &target) {
        if (source.getType() == Tile::Cell)
            target.setType(Tile::BlockFalse);
    }


    bool is_out_bounds(int x, int y, int width, int height){
        return y < 0 || x < 0 || x >= width || y >= height;
    }

    uint8_t* tile_to_pixel()
    {
        for (int i = 0; i < m_width * m_height; i++)
            m_pixels[i] = m_grid[i].getType();

        //int index = m_cursor.getX() + (m_cursor.getY() * m_width);
        //m_pixels[index] = Tile::Cursor;

        return m_pixels;
    }

    int getWidth() { return m_width; }
    int getHeight() { return m_height; }
    Tile getCursor() { return m_cursor; }
    Tile* getTiles() { return m_grid; }
};