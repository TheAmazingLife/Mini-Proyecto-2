#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include <string>
#include <list>

#include "Point.hpp"
#include "Node.hpp"

class Quadtree
{
private:
    Node *root;

public:
    Quadtree();
    ~Quadtree();

    void clear(); // Limpia los nodos desde la raiz

    int totalPoints(); // Retorna la cantidad de puntos almacenados en el QuadTree
    int totalNodes(); // Retorna la cantidad de nodos, tanto blancos como negros, en el QuadTree
    void insert(Point p, std::string cityName, int population); // Inserta un nuevo punto p en el QuadTree, junto con su data
    std::list<PointInfo> getPointList(); // Retorna una lista con todos los puntos almacenados en el QuadTree.
    int countRegion(Point p, int d); // Retorna la poblacion estimada dentro de una region del plano
    int aggregateRegion(Point p, int d); // Retorna la poblacion estimada dentro de una region del plano

private:
    void clearRecursive(Node *node);
    void insertRecursive(Node *&node, Point p, std::string cityName, int population);
    int totalPointsRecursive(Node *node);
    int totalNodesRecursive(Node *node);
    void getPointListRecursive(Node *node, std::list<PointInfo> &pointList);
    int countRegionRecursive(Node *node, Point p, int d);
    int aggregateRegionRecursive(Node *node, Point p, int d);
};

#endif // QUADTREE_HPP
