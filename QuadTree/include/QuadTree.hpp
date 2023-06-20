#pragma once

#include "QuadTreeNode.hpp"
#include <bits/stdc++.h>
using namespace std;

class QuadTree
{
  private:
    QuadTreeNode *root;

    void insertNode(QuadTreeNode *currentNode, Point p, std::string cityName, int population);
    void getPointList(QuadTreeNode *node, std::list<Point> &pointList);
    int countPointsInRegion(QuadTreeNode *node, Point p, int d);
    int calculatePopulationInRegion(QuadTreeNode *node, Point p, int d);

  public:
    QuadTree(Point p1, Point p2);
    int totalPoints();
    int totalNodes();
    void insert(Point p, string cityName, int population);
    list<Point> getPointList();
    int countRegion(Point p, int d);
    int aggregateRegion(Point p, int d);
};
