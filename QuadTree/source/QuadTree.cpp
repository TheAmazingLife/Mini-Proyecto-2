#include <iostream>
#include "../include/Quadtree.hpp"

Quadtree::Quadtree() : root(new Node()) {}

Quadtree::~Quadtree()
{
    // llamada a clear() que limpia desde el nodo raiz
    clear();
}

void Quadtree::clear() // ? Podria recibir un nodo como parametro y eliminar desde ahi en caso de cambiarla cambiamos el comentario tambien
{
    // Llamada a la funcion para eliminar el quadtree
    clearRecursive(root);
    root = new Node(); // Asigna la raiz como un nodo "White" vacio y disponible
}

void Quadtree::clearRecursive(Node *node) // ? Podria llamarse deleteQuadtree
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

void Quadtree::insert(Point p, std::string cityName, int population)
{
    // Inserta recursivamente desde la raiz, en base a un punto p, agrega nombre ciudad y poblacion
    insertRecursive(root, p, cityName, population);
}

void Quadtree::insertRecursive(Node *&node, Point p, std::string cityName, int population)
{
    // Si el color del nodo es "White" (blanco), significa que no hay datos en el nodo y se puede insertar la informacion
    if (node->color == "White")
    {
        delete node;                                       // Elimina el nodo existente
        node = new Node(p, cityName, population, "Black"); // Crea un nuevo nodo con los datos proporcionados y asigna el color "Black" (negro)
    }
    else
    {
        // Si el nodo no es blanco, se determina qué hijo del nodo actual se debe explorar para la insercion según las coordenadas del punto p
        if (p.longitude < node->point.longitude)
        {
            if (p.latitude < node->point.latitude)
            {
                // Si p tiene una longitud y latitud menor que las del nodo actual, se inserta recursivamente en el hijo suroeste (SW)
                insertRecursive(node->SW, p, cityName, population);
            }
            else
            {
                // Si p tiene una longitud menor pero una latitud mayor que las del nodo actual, se inserta recursivamente en el hijo noroeste (NW)
                insertRecursive(node->NW, p, cityName, population);
            }
        }
        else
        {
            if (p.latitude < node->point.latitude)
            {
                // Si p tiene una longitud mayor pero una latitud menor que las del nodo actual, se inserta recursivamente en el hijo sureste (SE)
                insertRecursive(node->SE, p, cityName, population);
            }
            else
            {
                // Si p tiene una longitud y latitud mayor que las del nodo actual, se inserta recursivamente en el hijo noreste (NE)
                insertRecursive(node->NE, p, cityName, population);
            }
        }
    }
}

int Quadtree::totalPoints()
{
    // Calcula el total de puntos recursivamente desde la raiz
    return totalPointsRecursive(root);
}

int Quadtree::totalNodes()
{
    // Calcula el total de nodos recursivamente desde la raiz
    return totalNodesRecursive(root);
}

std::list<PointInfo> Quadtree::getPointList()
{
    std::list<PointInfo> pointList;             // Lista que almacena los puntos
    getPointListRecursive(root, pointList); // Llama a obtener lista de puntos recursiva
    return pointList;                       // Retorna lista de puntos
}

int Quadtree::countRegion(Point p, int d)
{
    // Cuenta los puntos recursivamente desde la raiz, en base a un punto p, y un radio d
    return countRegionRecursive(root, p, d);
}

int Quadtree::aggregateRegion(Point p, int d)
{
    // Cuenta la poblacion recursivamente la desde la raiz, en base a un punto p, y un radio d
    return aggregateRegionRecursive(root, p, d);
}

int Quadtree::totalPointsRecursive(Node *node)
{
    // Si el color del nodo es "White" (blanco), no tiene hijos y no se cuentan más nodos
    if (node->color == "White")
    {
        return 0;
    }

    int count = 1; // Contador inicializado en 1 para contar el punto actual

    // Se llama recursivamente a la funcion para los cuatro hijos del nodo actual y se suma el resultado al contador
    count += totalPointsRecursive(node->NW);
    count += totalPointsRecursive(node->NE);
    count += totalPointsRecursive(node->SW);
    count += totalPointsRecursive(node->SE);

    return count; // Se devuelve el total de nodos contados
}

int Quadtree::totalNodesRecursive(Node *node)
{
    // Si el color del nodo es "White" (blanco), no tiene hijos y no se cuentan más nodos
    if (node->color == "White")
    {
        return 1;
    }

    int count = 1; // Contador inicializado en 1 para contar el nodo actual

    // Se llama recursivamente a la funcion para los cuatro hijos del nodo actual y se suma el resultado al contador
    count += totalNodesRecursive(node->NW);
    count += totalNodesRecursive(node->NE);
    count += totalNodesRecursive(node->SW);
    count += totalNodesRecursive(node->SE);

    return count; // Se devuelve el total de nodos contados
}

void Quadtree::getPointListRecursive(Node *node, std::list<PointInfo> &pointList)
{
    // Si el color del nodo es "White", no hay puntos en ese nodo, no se agrega nada a la lista
    if (node->color == "White")
    {
        return;
    }

    // Se llama recursivamente a la función para los cuatro hijos del nodo actual, pasando la misma lista
    getPointListRecursive(node->NW, pointList); // Recorrido postorder en el hijo NW
    getPointListRecursive(node->NE, pointList); // Recorrido postorder en el hijo NE
    getPointListRecursive(node->SW, pointList); // Recorrido postorder en el hijo SW
    getPointListRecursive(node->SE, pointList); // Recorrido postorder en el hijo SE

    // Se crea una instancia de la estructura PointInfo y se asignan los valores correspondientes
    PointInfo pointInfo;
    pointInfo.longitude = node->point.longitude;
    pointInfo.latitude = node->point.latitude;
    pointInfo.cityName = node->cityName;
    pointInfo.population = node->population;

    // Se agrega el punto junto con su información a la lista
    pointList.push_back(pointInfo); // Agrega el punto al final de la lista (recorrido Post Order)
}

int Quadtree::countRegionRecursive(Node *node, Point p, int d)
{
    // Si el color del nodo es "White" (blanco), el nodo no contiene puntos y devuelve 0
    if (node->color == "White")
    {
        return 0;
    }

    // Calcula la distancia al cuadrado entre el punto almacenado en el nodo actual y el punto p
    double dx = node->point.longitude - p.longitude;
    double dy = node->point.latitude - p.latitude;

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

int Quadtree::aggregateRegionRecursive(Node *node, Point p, int d)
{
    // Si el color del nodo es "White" (blanco), el nodo no contiene datos y devuelve 0 como valor agregado
    if (node->color == "White")
    {
        return 0;
    }

    // Calcula la distancia al cuadrado entre el punto almacenado en el nodo actual y el punto p
    double dx = node->point.longitude - p.longitude;
    double dy = node->point.latitude - p.latitude;
    int aggregate = 0;

    // Si la distancia al cuadrado es menor o igual al cuadrado del radio d*d, se agrega el valor de poblacion del nodo al valor agregado
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
