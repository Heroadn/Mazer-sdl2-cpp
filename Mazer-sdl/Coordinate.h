#ifndef COORDINATE_H
#define COORDINATE_H

class Coordinate
{
private:

public:
    int x;
    int y;

    Coordinate()
        : x(0),
          y(0)
    {}

    Coordinate(int x, int y)
        : x(x),
          y(y)
    {}

};

#endif