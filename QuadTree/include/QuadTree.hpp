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
        std::string color; // "Black" para información, "Blanco" para nodo vacío
        Node* NW;
        Node* NE;
        Node* SW;
        Node* SE;

        Node(Point p, std::string name, int pop, std::string c) : point(p), cityName(name), population(pop), color(c), NW(new Node()), NE(new Node()), SW(new Node()), SE(new Node()) {}
        Node() : color("White") {} 
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
