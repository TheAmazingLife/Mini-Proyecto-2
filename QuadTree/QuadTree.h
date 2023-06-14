#ifndef QUADTREE_H
#define QUADTREE_H

#include <bits/stdc++.h>
using namespace std;

/**
 * @brief Ubicación en el plano 2D
 *
 */
class Point
{
  public:
    double x;
    double y;
};

/**
 * @brief Nodos que se encuentran en QuadTree
 *
 */
class QuadTreeNode
{
  public:
    Point point;
    int data;

    QuadTreeNode *nw; // primer cuadrante
    QuadTreeNode *ne; // segundo cuadrante
    QuadTreeNode *sw; // tercer cuadrante
    QuadTreeNode *se; // cuarto cuadrante

    /**
     * QuadTreeNode
     * @brief Contructor: Setea la ubicacion e información que posee cada nodo de QuadTree
     *
     * @param p ubicacion en el plano 2D del nodo
     * @param d información que contiene el nodo
     */
    QuadTreeNode(Point p, int d)
    {
        point = p;
        data = d;

        nw = nullptr;
        ne = nullptr;
        sw = nullptr;
        se = nullptr;
    }
};

class QuadTree
{
  private:
    QuadTreeNode *root;

  public:
    /**
     * TODO: Necesario implementar todos los métodos
     *
     */
    QuadTree();
    int totalPoints();
    int totalNodes();
    void insert(Point p, int data);
    list<Point> list();
    int countRegion(Point p, int d);
    int aggregateRegion(Point p, int d);
};

#endif
