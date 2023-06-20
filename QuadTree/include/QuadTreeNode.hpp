#pragma once

#include "Point.hpp"
#include <bits/stdc++.h>
using namespace std;

/**
 * @brief Nodos que se encuentran en QuadTree
 *
 */
class QuadTreeNode
{
  public:
    Point topLeftLimit;
    Point lowerRightLimit;

    string cityName;
    int population;

    bool isBlack;

    QuadTreeNode *nw; // primer cuadrante (northwest)
    QuadTreeNode *ne; // segundo cuadrante (northeast)
    QuadTreeNode *sw; // tercer cuadrante (southwest)
    QuadTreeNode *se; // cuarto cuadrante (southeast)

    /**
     * QuadTreeNode
     * @brief Contructor: Setea la ubicacion e información que posee cada nodo de QuadTree
     *
     * @param topLeftLimit esquina superior izquierda del cuadrante
     * @param lowerRightLimit esquina inferior derecha del cuadrante
     * @param cityName nombre de la ciudad
     * @param population población de la ciudad
     */
    QuadTreeNode(Point topLeftLimit, Point lowerRightLimit, string cityName, int population)
    {
        this->topLeftLimit = topLeftLimit;
        this->lowerRightLimit = lowerRightLimit;

        this->cityName = cityName;
        this->population = population;

        isBlack = false;

        nw = nullptr;
        ne = nullptr;
        sw = nullptr;
        se = nullptr;
    }
};
