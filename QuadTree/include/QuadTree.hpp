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

private:
    void clearRecursive(Node *node);
    void insertRecursive(Node *&node, Point p, std::string cityName, int population);
    int totalPointsRecursive(Node *node);
    int totalNodesRecursive(Node *node);
    void getPointListRecursive(Node *node, std::list<Point> &pointList);
    int countRegionRecursive(Node *node, Point p, int d);
    int aggregateRegionRecursive(Node *node, Point p, int d);
};

#endif // QUADTREE_HPP
