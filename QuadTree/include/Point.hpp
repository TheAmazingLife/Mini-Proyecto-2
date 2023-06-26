#ifndef POINT_HPP
#define POINT_HPP

struct Point
{
    double x;
    double y;

    Point(double x, double y)
    {
        this->x = x;
        this->y = y;
    }

    Point()
    {
        x = 0;
        y = 0;
    }
};

#endif
