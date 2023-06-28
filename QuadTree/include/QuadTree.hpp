#ifndef QUADTREE_HPP
#define QUADTREE_HPP

#include <list>
#include <string>

#include "Node.hpp"
#include "Point.hpp"

class QuadTree
{
private:
  Node *root;         // Puntero al nodo raíz del QuadTree
  int insertCount;    // Contador de inserciones

public:
  QuadTree();         // Constructor de la clase QuadTree

  void clear();       // Limpia los nodos desde la raíz

  int totalPoints();  // Retorna la cantidad de puntos almacenados en el QuadTree
  int totalNodes();   // Retorna la cantidad de nodos, tanto blancos como negros, en el QuadTree
  void insert(Point p, std::string cityName, int population);  // Inserta un nuevo punto p en el QuadTree, junto con su data
  std::list<Node *> getPointList();   // Retorna una lista con todos los puntos almacenados en el QuadTree.
  long long countRegion(Point p, int d);  // Retorna la población estimada dentro de una región del plano
  long long aggregateRegion(Point p, int d);  // Retorna la población estimada dentro de una región del plano
  void printTotalPopulation();  // Imprime la población total en los nodos

private:
  void clearRecursive(Node *node);  // Función recursiva para limpiar los nodos a partir de un nodo dado
  void insertRecursive(Node *&node, Point p, std::string cityName, int population);  // Función recursiva para insertar un nodo en el QuadTree
  void totalNodesRecursive(Node *node, int &count);  // Función recursiva para contar los nodos en el QuadTree
  void getPointListRecursive(Node *node, std::list<Node *> &pointList);  // Función recursiva para obtener una lista de todos los puntos en el QuadTree
  long long countRegionRecursive(Node *node, Point p, int d);  // Función recursiva para contar la población en una región del plano
  long long aggregateRegionRecursive(Node *node, Point p, int d);  // Función recursiva para sumar la población en una región del plano
  long long calculateTotalPopulation(Node *node);  // Función para calcular la población total en los nodos del QuadTree
};

#endif // QUADTREE_HPP
