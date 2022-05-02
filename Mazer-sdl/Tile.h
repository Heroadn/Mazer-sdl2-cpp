class Tile
{
public:
    enum Type
    {
        Void,
        Cell,
        BlockFalse,
        BlockTrue,
        Cursor
    };

    Tile()
    {
        setTile(0, 0, false, Type::Cell);
    }

    Tile(int x, int y, bool visited, Type type)
    {
        setTile(x, y, visited, type);
    }

    Tile(int x, int y)
    {
        setTile(x, y, false, Type::Cell);
    }

    void setTile(int x, int y, bool visited, Type type)
    {
        m_coordiante = { x, y };
        m_state = { visited, type };
    }

    int getType() { return m_state.type; }
    int getVisited() { return m_state.visited; }
    int getX() { return m_coordiante.x; }
    int getY() { return m_coordiante.y; }
    void setX(int x) { m_coordiante.x = x; }
    void setY(int y) { m_coordiante.y = y; }
    void setType(Type type) { m_state.type = type; }
    void setVisited(bool visited) { m_state.visited = visited; }
private:
    struct Coordinate {
        int x;
        int y;
    } m_coordiante;
    struct State {
        bool visited;
        Type type;
    } m_state;
};