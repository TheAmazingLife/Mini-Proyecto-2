#ifndef POINT_HPP
#define POINT_HPP

#include <string>

struct Point
{
    double x;
    double y;

    // Constructor que toma dos parámetros para inicializar las coordenadas x e y.
    Point(double x, double y)
    {
        this->x = x;
        this->y = y;
    }

    // Constructor por defecto que inicializa las coordenadas x e y en 0.
    Point()
    {
        x = 0;
        y = 0;
    }
};

#endif
