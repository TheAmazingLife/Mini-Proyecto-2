#include "include\QuadTree.hpp"
#include <bits/stdc++.h>
using namespace std;

int main()
{
    // Crear un QuadTree
    QuadTree quadTree(Point(0, 0), Point(100, 100));

    // Insertar puntos en el QuadTree
    quadTree.insert(Point(20, 30), "Ciudad A", 100000);
    quadTree.insert(Point(40, 60), "Ciudad B", 50000);
    quadTree.insert(Point(80, 70), "Ciudad C", 200000);

    // Obtener la cantidad total de puntos y nodos
    int totalPoints = quadTree.totalPoints();
    int totalNodes = quadTree.totalNodes();

    cout << "Total de puntos: " << totalPoints << endl;
    cout << "Total de nodos: " << totalNodes << endl;

    // Obtener la lista de puntos en el QuadTree
    list<Point> pointList = quadTree.getPointList();

    cout << "Puntos almacenados en el QuadTree:" << endl;
    for (const Point &point : pointList)
    {
        cout << "Coordenadas: (" << point.x << ", " << point.y << ")" << endl;
    }

    // Contar la cantidad de puntos en una región
    Point center(50, 50);
    int radius = 30;
    int count = quadTree.countRegion(center, radius);

    cout << "Cantidad de puntos en la region (centro: " << center.x << ", " << center.y << ", radio: " << radius
         << "): " << count << endl;

    // Calcular la población estimada dentro de una región
    int population = quadTree.aggregateRegion(center, radius);

    cout << "Población estimada en la region (centro: " << center.x << ", " << center.y << ", radio: " << radius
         << "): " << population << endl;

    return 0;
}
