#ifndef QUADTREE_H
#define QUADTREE_H

#include <bits/stdc++.h>
using namespace std;

class Point
{
  public:
    double x;
    double y;
};

class QuadTreeNode
{
  public:
    Point point;
    int data;

    QuadTreeNode *nw; // primer cuadrante
    QuadTreeNode *ne; // segundo cuadrante
    QuadTreeNode *sw; // tercer cuadrante
    QuadTreeNode *se; // cuarto cuadrante

    QuadTreeNode(Point p, int d)
    {
        point = p;
        data = d;

        nw = NULL;
        ne = NULL;
        sw = NULL;
        se = NULL;
    }
};

class QuadTree
{
  private:
    QuadTreeNode *root;

  public:
    QuadTree();
    int totalPoints();
    int totalNodes();
    void insert(Point p, int data);
    list<Point> list();
    int countRegion(Point p, int d);
    int aggregateRegion(Point p, int d);
};

#endif
