#include "../include/QuadTree.hpp"
#include <iostream>
#include <list>

QuadTree::QuadTree()
{
    root = new Node();
    insertCount = 0;
}

QuadTree::~QuadTree()
{
    // llamada a clear() que limpia desde el nodo raiz
    clear();
}

void QuadTree::clear() // ? Podria recibir un nodo como parametro y eliminar desde ahi en caso de cambiarla cambiamos el
                       // comentario tambien
{
    // Llamada a la funcion para eliminar el quadTree
    clearRecursive(root);
    root = new Node(); // Asigna la raiz como un nodo "White" vacio y disponible
}

void QuadTree::clearRecursive(Node *node) // ? Podria llamarse deleteQuadTree
{
    // Si el color del nodo es "White" (blanco), el nodo no contiene nodos y retorna
    if (node->color == "White")
    {
        return;
    }

    // Elimina los nodos hijos en cada direccion
    clearRecursive(node->NW);
    clearRecursive(node->NE);
    clearRecursive(node->SW);
    clearRecursive(node->SE);

    // Libera la memoria del nodo actual
    delete node;
}

void QuadTree::insert(Point p, std::string cityName, int population)
{
    // Inserta recursivamente desde la raiz, en base a un punto p, agrega nombre ciudad y poblacion
    insertRecursive(root, p, cityName, population);
    insertCount++;
}

void QuadTree::insertRecursive(Node *&node, Point p, std::string cityName, int population)
{
    // Verifica si el nodo actual es un nodo vacío
    if (node->color == "White")
    {
        // El nodo actual es un nodo vacío, por lo que se puede insertar el punto aquí
        node->color = "Black";
        node->point = p;
        node->cityName = cityName;
        node->population = population;

        node->NW = new Node();
        node->NE = new Node();
        node->SW = new Node();
        node->SE = new Node();

        // Verifica si los hijos del nodo son nulos y, en caso afirmativo, crea nuevos nodos blancos para ellos
        if (node->NW == nullptr)
        {
            node->NW = new Node();
            node->NW->color = "White";
        }
        if (node->NE == nullptr)
        {
            node->NE = new Node();
            node->NE->color = "White";
        }
        if (node->SW == nullptr)
        {
            node->SW = new Node();
            node->SW->color = "White";
        }
        if (node->SE == nullptr)
        {
            node->SE = new Node();
            node->SE->color = "White";
        }

        return;
    }

    // El nodo actual contiene información, por lo que se divide el espacio y se inserta el punto en el hijo
    // correspondiente

    // Calcula el punto medio del nodo actual
    Point midpoint;
    midpoint.x = (node->point.x + node->point.x + 1) / 2;
    midpoint.y = (node->point.y + node->point.y + 1) / 2;

    // Determina en qué cuadrante cae el punto
    bool isNorth = p.y > midpoint.y;
    bool isWest = p.x < midpoint.x;

    // Selecciona el hijo correspondiente en base al cuadrante
    Node **child = nullptr;
    if (isNorth && isWest)
    {
        child = &node->NW;
    }
    else if (isNorth && !isWest)
    {
        child = &node->NE;
    }
    else if (!isNorth && isWest)
    {
        child = &node->SW;
    }
    else
    {
        child = &node->SE;
    }

    // Si el hijo no existe, se crea un nuevo nodo vacío y se lo asigna
    if (*child == nullptr)
    {
        *child = new Node();
        (*child)->color = "White";
    }

    // Se llama recursivamente a la función en el hijo correspondiente
    insertRecursive(*child, p, cityName, population);
}

int QuadTree::totalPoints()
{
    // Calcula el total de puntos recursivamente desde la raiz
    return insertCount;
}

int QuadTree::totalNodes()
{
    int count = 0; // Contador inicializado en 0

    // Se llama a la función recursiva pasando la raíz del árbol y el contador
    totalNodesRecursive(root, count);

    return count;
}

std::list<Node *> QuadTree::getPointList()
{
    std::list<Node *> leafNodes;
    getPointListRecursive(root, leafNodes);
    return leafNodes;
}

int QuadTree::countRegion(Point p, int d)
{
    // Cuenta los puntos recursivamente desde la raiz, en base a un punto p, y un radio d
    return countRegionRecursive(root, p, d + 1);
}

int QuadTree::aggregateRegion(Point p, int d)
{
    // Cuenta la poblacion recursivamente la desde la raiz, en base a un punto p, y un radio d
    return aggregateRegionRecursive(root, p, d + 1);
}

void QuadTree::totalNodesRecursive(Node *node, int &count)
{
    if (node == NULL)
    {
        count++;
        return;
    }
    if (node->color == "White")
    {
        count++;
        return;
    }

    count++; // Se incrementa el contador por cada nodo visitado

    // Se llama recursivamente a la función para los cuatro hijos del nodo actual
    totalNodesRecursive(node->NW, count);
    totalNodesRecursive(node->NE, count);
    totalNodesRecursive(node->SW, count);
    totalNodesRecursive(node->SE, count);
}

void QuadTree::getPointListRecursive(Node *node, std::list<Node *> &pointList)
{
    // Verifica si el nodo actual es negro
    if (node->color == "Black")
    {
        // Verifica si todos los hijos son blancos
        if (node->NW->color == "White" && node->NE->color == "White" && node->SW->color == "White" &&
            node->SE->color == "White")
        {
            pointList.push_back(node);
        }
        else
        {
            // Se llama recursivamente a la función para los cuatro hijos del nodo actual
            getPointListRecursive(node->NW, pointList);
            getPointListRecursive(node->NE, pointList);
            getPointListRecursive(node->SW, pointList);
            getPointListRecursive(node->SE, pointList);
        }
    }
}

int QuadTree::countRegionRecursive(Node *node, Point p, int d)
{
    // Si el color del nodo es "White" (blanco), el nodo no contiene puntos y devuelve 0
    if (node->color == "White")
    {
        return 0;
    }

    // Calcula la distancia al cuadrado entre el punto almacenado en el nodo actual y el punto p
    double dx = node->point.x - p.x;
    double dy = node->point.y - p.y;

    int count = 0;

    // Si la distancia al cuadrado es menor o igual al cuadrado del radio d*d, se incrementa el contador en 1
    if (dx * dx + dy * dy <= d * d)
    {
        count++;
    }

    // Se llama recursivamente a la funcion para los cuatro hijos del nodo actual, pasando el mismo centro y radio
    count += countRegionRecursive(node->NW, p, d);
    count += countRegionRecursive(node->NE, p, d);
    count += countRegionRecursive(node->SW, p, d);
    count += countRegionRecursive(node->SE, p, d);

    return count; // Se devuelve el total de puntos contados en la region circular
}

int QuadTree::aggregateRegionRecursive(Node *node, Point p, int d)
{
    // Si el color del nodo es "White" (blanco), el nodo no contiene datos y devuelve 0 como valor agregado
    if (node->color == "White")
    {
        return 0;
    }

    // Calcula la distancia al cuadrado entre el punto almacenado en el nodo actual y el punto p
    double dx = node->point.x - p.x;
    double dy = node->point.y - p.y;
    int aggregate = 0;

    // Si la distancia al cuadrado es menor o igual al cuadrado del radio d*d, se agrega el valor de poblacion del nodo
    // al valor agregado
    if (dx * dx + dy * dy <= d * d)
    {
        aggregate += node->population;
    }

    // Se llama recursivamente a la funcion para los cuatro hijos del nodo actual, pasando el mismo centro y radio
    aggregate += aggregateRegionRecursive(node->NW, p, d);
    aggregate += aggregateRegionRecursive(node->NE, p, d);
    aggregate += aggregateRegionRecursive(node->SW, p, d);
    aggregate += aggregateRegionRecursive(node->SE, p, d);

    return aggregate; // Se devuelve el valor agregado de poblacion en la region circular
}
