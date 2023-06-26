#ifndef NODE_HPP
#define NODE_HPP

#include "Point.hpp"
#include <vector>

// The objects that we want stored in the quadtree
struct Node
{
    Point pos;
    int data;
    bool isBlack; // New attribute
    Node(Point _pos, int _data)
    {
        pos = _pos;
        data = _data;
        isBlack = false; // Default value is false
    }
    Node()
    {
        data = 0;
        isBlack = false;
    }
};

#endif