#ifndef POINT_HPP
#define POINT_HPP

#include <string>

struct Point
{
    double longitude;
    double latitude;
};

struct PointInfo
{
    double longitude;
    double latitude;
    std::string cityName;
    int population;
};

#endif