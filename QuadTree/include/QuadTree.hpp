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

    void clear();
    void insert(Point p, std::string cityName, int population);
    int totalPoints();
    int totalNodes();
    std::list<Point> getPointList();
    int countRegion(Point p, int d);
    int aggregateRegion(Point p, int d);
    // ! Metodo extra
    void printColorAndLevel();
    void searchCity(const std::string& cityName);
    void searchCityNode(Node* node, const std::string& cityName);

private:
    void clearRecursive(Node *node);
    void insertRecursive(Node *&node, Point p, std::string cityName, int population);
    int totalPointsRecursive(Node *node);
    int totalNodesRecursive(Node *node);
    void getPointListRecursive(Node *node, std::list<Point> &pointList);
    int countRegionRecursive(Node *node, Point p, int d);
    int aggregateRegionRecursive(Node *node, Point p, int d);
    // ! Metodo extra
    void printNodeColorAndLevel(Node* node, int level);
};

#endif // QUADTREE_HPP
