#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include <string>
#include <list>

struct Point {
    double longitude;
    double latitude;
};

class Quadtree {
private:
    struct Node {
        Point point;
        std::string cityName;
        int population;
        Node* NW;
        Node* NE;
        Node* SW;
        Node* SE;

        Node(Point p, std::string name, int pop) : point(p), cityName(name), population(pop), NW(nullptr), NE(nullptr), SW(nullptr), SE(nullptr) {}
    };

    Node* root;

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
    void clearRecursive(Node* node);
    void insertRecursive(Node*& node, Point p, std::string cityName, int population);
    int totalPointsRecursive(Node* node);
    int totalNodesRecursive(Node* node);
    void getPointListRecursive(Node* node, std::list<Point>& pointList);
    int countRegionRecursive(Node* node, Point p, int d);
    int aggregateRegionRecursive(Node* node, Point p, int d);
};

#endif // QUADTREE_HPP
