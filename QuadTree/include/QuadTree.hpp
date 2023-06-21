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
    bool inBoundary(Point* p);

    public : QuadTree(Point p1, Point p2);
    int totalPoints(); // Retorna la cantidad de puntos almacenados en el QuadTree
    int totalNodes(); // Retorna la cantidad de nodos, tanto blancos como negros, en el QuadTree
    void insert(Point p, string cityName, int population); // Inserta un nuevo punto p en el QuadTree, asociando a dicho punto la información disponible en data (ej. la población de una ciudad con coordenadas p).
    list<Point> getPointList(); // Retorna un contenedor con todos los puntos almacenados en el QuadTree.
    int countRegion(Point p, int d); // Retorna la cantidad de puntos en una región del plano, tomando como centro el punto p y una distancia d.
    int aggregateRegion(Point p, int d); // Retorna la población estimada dentro de una región del plano, tomando como centro el punto p y una distancia d.
};
