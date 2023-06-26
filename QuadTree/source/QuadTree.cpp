#include "../include/QuadTree.hpp"
#include "../include/Point.hpp"
#include <iostream>
#include <vector>

QuadTree::QuadTree()
{
    topLeft = Point(0, 0);
    botRight = Point(0, 0);
    n = nullptr;
    topLeftTree = nullptr;
    topRightTree = nullptr;
    botLeftTree = nullptr;
    botRightTree = nullptr;
}

QuadTree::QuadTree(Point topL, Point botR)
{
    n = nullptr;
    topLeftTree = nullptr;
    topRightTree = nullptr;
    botLeftTree = nullptr;
    botRightTree = nullptr;
    topLeft = topL;
    botRight = botR;
}

// Insert a node into the quadtree
void QuadTree::insert(Node *node)
{
    if (node == nullptr)
        return;

    // Current quad cannot contain it
    if (!inBoundary(node->pos))
        return;

    // We are at a quad of unit area
    // We cannot subdivide this quad further
    if (abs(topLeft.x - botRight.x) <= 1 && abs(topLeft.y - botRight.y) <= 1)
    {
        if (n == nullptr)
            n = node;

        return;
    }

    if ((topLeft.x + botRight.x) / 2 > node->pos.x)
    {
        // Indicates topLeftTree
        if ((topLeft.y + botRight.y) / 2 > node->pos.y)
        {
            if (topLeftTree == nullptr)
                topLeftTree = new QuadTree(Point(topLeft.x, topLeft.y),
                                           Point((topLeft.x + botRight.x) / 2, (topLeft.y + botRight.y) / 2));

            topLeftTree->insert(node);
        }

        // Indicates botLeftTree
        else
        {
            if (botLeftTree == nullptr)
                botLeftTree = new QuadTree(Point(topLeft.x, (topLeft.y + botRight.y) / 2),
                                           Point((topLeft.x + botRight.x) / 2, botRight.y));

            botLeftTree->insert(node);
        }
    }
    else
    {
        // Indicates topRightTree
        if ((topLeft.y + botRight.y) / 2 > node->pos.y)
        {
            if (topRightTree == nullptr)
                topRightTree = new QuadTree(Point((topLeft.x + botRight.x) / 2, topLeft.y),
                                            Point(botRight.x, (topLeft.y + botRight.y) / 2));

            topRightTree->insert(node);
        }

        // Indicates botRightTree
        else
        {
            if (botRightTree == nullptr)
                botRightTree = new QuadTree(Point((topLeft.x + botRight.x) / 2, (topLeft.y + botRight.y) / 2),
                                            Point(botRight.x, botRight.y));

            botRightTree->insert(node);
        }
    }
}

// Find a node in a quadtree
Node *QuadTree::search(Point p)
{
    // Current quad cannot contain it
    if (!inBoundary(p))
        return nullptr;

    // We are at a quad of unit length
    // We cannot subdivide this quad further
    if (n != nullptr)
        return n;

    if ((topLeft.x + botRight.x) / 2 > p.x)
    {
        // Indicates topLeftTree
        if ((topLeft.y + botRight.y) / 2 > p.y)
        {
            if (topLeftTree == nullptr)
                return nullptr;
            return topLeftTree->search(p);
        }

        // Indicates botLeftTree
        else
        {
            if (botLeftTree == nullptr)
                return nullptr;
            return botLeftTree->search(p);
        }
    }
    else
    {
        // Indicates topRightTree
        if ((topLeft.y + botRight.y) / 2 > p.y)
        {
            if (topRightTree == nullptr)
                return nullptr;
            return topRightTree->search(p);
        }

        // Indicates botRightTree
        else
        {
            if (botRightTree == nullptr)
                return nullptr;
            return botRightTree->search(p);
        }
    }
};

// Check if current quadtree contains the point
bool QuadTree::inBoundary(Point p)
{
    return (p.x >= topLeft.x && p.x <= botRight.x && p.y >= topLeft.y && p.y <= botRight.y);
}

int QuadTree::totalPoints()
{
    if (n != nullptr)
    {
        // Si es una hoja negra, retorna 1
        return 1;
    }

    int count = 0;

    if (topLeftTree != nullptr)
        count += topLeftTree->totalPoints();
    if (topRightTree != nullptr)
        count += topRightTree->totalPoints();
    if (botLeftTree != nullptr)
        count += botLeftTree->totalPoints();
    if (botRightTree != nullptr)
        count += botRightTree->totalPoints();

    return count;
}

int QuadTree::totalNodes()
{
    int count = 0;

    if (n != nullptr)
        count++; // Increment count for the current node

    if (topLeftTree != nullptr)
        count += topLeftTree->totalNodes();
    if (topRightTree != nullptr)
        count += topRightTree->totalNodes();
    if (botLeftTree != nullptr)
        count += botLeftTree->totalNodes();
    if (botRightTree != nullptr)
        count += botRightTree->totalNodes();

    return count;
}
