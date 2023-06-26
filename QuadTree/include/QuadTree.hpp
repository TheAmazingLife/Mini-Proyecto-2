#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include <list>
#include <vector>

#include "Node.hpp"
#include "Point.hpp"

class QuadTree
{
    // Hold details of the boundary of this node
    Point topLeft;
    Point botRight;

    // Contains details of node
    Node *n;

    // Children of this tree
    QuadTree *topLeftTree;
    QuadTree *topRightTree;
    QuadTree *botLeftTree;
    QuadTree *botRightTree;

  public:
    QuadTree();
    QuadTree(Point topL, Point botR);
    void insert(Node *node);
    Node *search(Point p);
    bool inBoundary(Point p);
    int totalPoints(); // Returns the total number of points stored in the QuadTree
    int totalNodes();
    int blackNodes();
    void insert(Point p,
                int data); // Inserts a new point with associated data into the QuadTree
};
#endif // QUADTREE_HPP
