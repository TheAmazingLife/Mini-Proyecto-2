#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include <list>
#include <string>

#include "Node.hpp"
#include "Point.hpp"

class QuadTree
{
  private:
    Node *root;
    int insertCount;

  public:
    QuadTree();

    void clear(); // Limpia los nodos desde la raiz

    int totalPoints(); // Retorna la cantidad de puntos almacenados en el QuadTree
    int totalNodes();  // Retorna la cantidad de nodos, tanto blancos como negros, en el QuadTree
    void insert(Point p, std::string cityName,
                int population);         // Inserta un nuevo punto p en el QuadTree, junto con su data
    std::list<Node *> getPointList();    // Retorna una lista con todos los puntos almacenados en el QuadTree.
    int countRegion(Point p, int d);     // Retorna la poblacion estimada dentro de una region del plano
    int aggregateRegion(Point p, int d); // Retorna la poblacion estimada dentro de una region del plano

  private:
    void clearRecursive(Node *node);
    void insertRecursive(Node *&node, Point p, std::string cityName, int population);
    void totalNodesRecursive(Node *node, int &count);
    void getPointListRecursive(Node *node, std::list<Node *> &pointList);
    int countRegionRecursive(Node *node, Point p, int d);
    int aggregateRegionRecursive(Node *node, Point p, int d);
};

#endif // QUADTREE_HPP
