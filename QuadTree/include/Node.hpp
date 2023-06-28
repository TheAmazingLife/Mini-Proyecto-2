#ifndef NODE_HPP
#define NODE_HPP

#include <string>

#include "Point.hpp"

struct Node
{
public:
    Point point;          // Coordenadas del punto
    std::string cityName; // Nombre de la ciudad asociada al nodo
    int population;       // Poblacion de la ciudad
    std::string color;    // Color del nodo: "Black" para información, "White" para nodo vacio
    Node *NW;             // Puntero al nodo hijo del noroeste
    Node *NE;             // Puntero al nodo hijo del noreste
    Node *SW;             // Puntero al nodo hijo del suroeste
    Node *SE;             // Puntero al nodo hijo del sureste

    Node(Point p, std::string name, int pop, std::string c)
    {
        point = p;
        cityName = name;
        population = pop;
        color = c;
    }

    // Constructor sin parámetros, genera un nodo vacío disponible con color "White"
    Node()
    {
        color = "White";
    }
};

#endif
