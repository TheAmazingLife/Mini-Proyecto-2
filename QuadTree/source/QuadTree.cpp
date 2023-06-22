#include <iostream>
#include "../include/Quadtree.hpp"

Quadtree::Quadtree() : root(new Node()) {}

Quadtree::~Quadtree()
{
    clear();
}

void Quadtree::clear()
{
    // Llamada a la función para eliminar el quadtree
    clearRecursive(root);
    root = new Node();
}

void Quadtree::clearRecursive(Node *node) // ? Podria llamarse deleteQuadtree
{
    if (node->color == "White")
    {
        return;
    }

    // Elimina los nodos hijos en cada dirección
    clearRecursive(node->NW);
    clearRecursive(node->NE);
    clearRecursive(node->SW);
    clearRecursive(node->SE);

    // Libera la memoria del nodo actual
    delete node;
}

void Quadtree::insert(Point p, std::string cityName, int population)
{
    insertRecursive(root, p, cityName, population);
}

void Quadtree::insertRecursive(Node *&node, Point p, std::string cityName, int population)
{
    if (node->color == "White")
    {
        delete node;
        node = new Node(p, cityName, population, "Black"); // Asigna "Black" cuando se inserta información
    }
    else
    {
        if (p.longitude < node->point.longitude)
        {
            if (p.latitude < node->point.latitude)
            {
                insertRecursive(node->SW, p, cityName, population);
            }
            else
            {
                insertRecursive(node->NW, p, cityName, population);
            }
        }
        else
        {
            if (p.latitude < node->point.latitude)
            {
                insertRecursive(node->SE, p, cityName, population);
            }
            else
            {
                insertRecursive(node->NE, p, cityName, population);
            }
        }
    }
}

int Quadtree::totalPoints()
{
    return totalPointsRecursive(root);
}

int Quadtree::totalNodes()
{
    return totalNodesRecursive(root);
}

std::list<Point> Quadtree::getPointList()
{
    std::list<Point> pointList;
    getPointListRecursive(root, pointList);
    return pointList;
}

int Quadtree::countRegion(Point p, int d)
{
    return countRegionRecursive(root, p, d);
}

int Quadtree::aggregateRegion(Point p, int d)
{
    return aggregateRegionRecursive(root, p, d);
}

int Quadtree::totalPointsRecursive(Node *node)
{
    if (node->color == "White")
    {
        return 0;
    }

    int count = 1;

    count += totalPointsRecursive(node->NW);
    count += totalPointsRecursive(node->NE);
    count += totalPointsRecursive(node->SW);
    count += totalPointsRecursive(node->SE);

    return count;
}

int Quadtree::totalNodesRecursive(Node *node)
{
    if (node->color == "White")
    {
        return 0;
    }

    int count = 1;

    count += totalNodesRecursive(node->NW);
    count += totalNodesRecursive(node->NE);
    count += totalNodesRecursive(node->SW);
    count += totalNodesRecursive(node->SE);

    return count;
}

void Quadtree::getPointListRecursive(Node *node, std::list<Point> &pointList)
{
    if (node->color == "White")
    {
        return;
    }

    // ! metodo extra
    // std::cout << node->cityName;
    pointList.push_back(node->point);

    getPointListRecursive(node->NW, pointList);
    getPointListRecursive(node->NE, pointList);
    getPointListRecursive(node->SW, pointList);
    getPointListRecursive(node->SE, pointList);
}

int Quadtree::countRegionRecursive(Node *node, Point p, int d)
{
    if (node->color == "White")
    {
        return 0;
    }

    double dx = node->point.longitude - p.longitude;
    double dy = node->point.latitude - p.latitude;
    int count = 0;

    if (dx * dx + dy * dy <= d * d)
    {
        count++;
    }

    count += countRegionRecursive(node->NW, p, d);
    count += countRegionRecursive(node->NE, p, d);
    count += countRegionRecursive(node->SW, p, d);
    count += countRegionRecursive(node->SE, p, d);

    return count;
}

int Quadtree::aggregateRegionRecursive(Node *node, Point p, int d)
{
    if (node->color == "White")
    {
        return 0;
    }

    double dx = node->point.longitude - p.longitude;
    double dy = node->point.latitude - p.latitude;
    int aggregate = 0;

    if (dx * dx + dy * dy <= d * d)
    {
        aggregate += node->population;
    }

    aggregate += aggregateRegionRecursive(node->NW, p, d);
    aggregate += aggregateRegionRecursive(node->NE, p, d);
    aggregate += aggregateRegionRecursive(node->SW, p, d);
    aggregate += aggregateRegionRecursive(node->SE, p, d);

    return aggregate;
}

// TODO: metodo extra
// ! AMBOS EN DESARROLLO

void Quadtree::printColorAndLevel()
{
    printNodeColorAndLevel(root, 0);
}

void Quadtree::printNodeColorAndLevel(Node *node, int level)
{
    if (node->color != "White")
    {
        std::cout << "Color: " << node->color << ", Nivel: " << level << std::endl;

        printNodeColorAndLevel(node->NW, level + 1);
        printNodeColorAndLevel(node->NE, level + 1);
        printNodeColorAndLevel(node->SW, level + 1);
        printNodeColorAndLevel(node->SE, level + 1);
    }
}

void Quadtree::searchCity(const std::string &cityName)
{
    try
    {
        searchCityNode(root, cityName);
    }
    catch (const std::exception &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

// Método para buscar una ciudad por nombre y devolver información
void Quadtree::searchCityNode(Node *node, const std::string &cityName)
{
    if (node == nullptr || node->color == "White")
    {
        // Nodo vacío, se alcanzó una hoja
        throw std::runtime_error("La ciudad '" + cityName + "' no fue encontrada en el Quadtree.");
    }

    if (node->cityName == cityName)
    {
        // Ciudad encontrada
        std::cout << "Información de la ciudad '" << cityName << "':" << std::endl;
        std::cout << "Ubicación: Latitud: " << node->point.latitude << ", Longitud: " << node->point.longitude << std::endl;
        std::cout << "Población: " << node->population << std::endl;
        return;
    }

    // Buscar en los nodos hijos recursivamente
    searchCityNode(node->NW, cityName);
    searchCityNode(node->NE, cityName);
    searchCityNode(node->SW, cityName);
    searchCityNode(node->SE, cityName);
}
