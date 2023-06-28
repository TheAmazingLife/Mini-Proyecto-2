#include <iostream>
#include <fstream>
#include <vector>

#include "include/Point.hpp"
#include "include/QuadTree.hpp"
#include "include/DataFormatter.hpp"

int main()
{
    // Leer datos desde el archivo de entrada
    // std::ifstream inputFile("DataSet/worldcitiespop_fixed.csv");
    std::ifstream inputFile("DataSet/worldcitiespop_fixed.csv"); // Incluimos el .csv testeo
    std::stringstream buffer;
    buffer << inputFile.rdbuf();
    std::string input = buffer.str();

    // Formatear los datos
    std::vector<std::tuple<Point, std::string, int>> formattedData = formatData(input);

    // Crear el Quadtree y cargar los datos
    QuadTree quadtree;
    for (const auto &data : formattedData)
    {
        Point point = std::get<0>(data);
        std::string cityName = std::get<1>(data);
        int population = std::get<2>(data);
        quadtree.insert(point, cityName, population);
    }

    // Obtener la cantidad total de puntos
    int totalPoints = quadtree.totalPoints();
    std::cout << "Cantidad total de puntos: " << totalPoints << std::endl;

    // Obtener la cantidad total de nodos
    int totalNodes = quadtree.totalNodes();
    std::cout << "Cantidad total de nodos: " << totalNodes << std::endl;

    quadtree.printTotalPopulation();

/*     // Obtener la lista de puntos almacenados en el Quadtree
    std::list<Point> pointList = quadtree.getPointList();
    std::cout << "Cantidad de datos encontrados: " << pointList.size() << std::endl;
    std::cout << "Lista de puntos almacenados en el Quadtree:" << std::endl;
    for (const auto &point : pointList)
    {
        std::cout << "Longitud: " << point.longitude << ", Latitud: " << point.latitude << std::endl;
    } */

    return 0;
}
