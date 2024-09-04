#include "Maze.h"
#include <stdlib.h> 

Maze::Maze(int width,
           int height,
           Tile start) : m_width(width),
                         m_height(height),
                         m_start(start)
{
    m_grid = new Tile[width * height];
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

Maze::~Maze() {
    //delete[] m_grid;
    //delete[] m_pixels;
}

void Maze::fill_grid() {
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

void Maze::walk_grid(const std::vector<Tile> choices) {
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
    int now_index = choice.getX() + (choice.getY() * m_width);
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

void Maze::search_unvisited(std::vector<Tile>& unvisited) {
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
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

bool Maze::generate_step()
{
    if (m_track.empty())
        return true;

    search_unvisited(m_unvisited);
    walk_grid(m_unvisited);
    m_unvisited.clear();
    return false;
}

void Maze::generate_full()
{
    while (generate_step() == false);
}

void Maze::remove_wall(Tile source, Tile& target) {
    if (source.getType() == Tile::Cell)
        target.setType(Tile::BlockFalse);
}

bool Maze::is_out_bounds(int x, int y, int width, int height) {
    return y < 0 || x < 0 || x >= width || y >= height;
}

Tile* Maze::grid()
{
    return m_grid;
}

