#include <iostream>
#include <fstream>
#include <vector>

#include "include/Point.hpp"
#include "include/Quadtree.hpp"
#include "include/DataFormatter.hpp"

int main()
{
    // Leer datos desde el archivo de entrada
    // std::ifstream inputFile("DataSet/worldcitiespop_fixed.csv");
    std::ifstream inputFile("DataSet/test2.csv"); // Incluimos el .csv testeo
    std::stringstream buffer;
    buffer << inputFile.rdbuf();
    std::string input = buffer.str();

    // Formatear los datos
    std::vector<std::tuple<Point, std::string, int>> formattedData = formatData(input);

    // Crear el Quadtree y cargar los datos
    Quadtree quadtree;
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

    // Obtener la lista de puntos almacenados en el Quadtree
    // TODO: Falta agregar que imprima su data, elegir un tipo de recorrido, pre post variante inorder
    std::list<PointInfo> pointList = quadtree.getPointList();
    std::cout << "Cantidad de datos encontrados: " << pointList.size() << std::endl;
    std::cout << "Lista de puntos almacenados en el Quadtree:" << std::endl;
    for (const auto &point : pointList)
    {
        std::cout << "Ciudad: " << point.cityName << ", Poblacion: " << point.population << ", Longitud: " << point.longitude << ", Latitud: " << point.latitude << std::endl;
    }

    /* // Contar la cantidad de puntos en una region
    Point center = {40.920404, 39.19209};
    int radius = 10;
    int count = quadtree.countRegion(center, radius);
    std::cout << "Cantidad de puntos en la region (centro: " << center.longitude << ", " << center.latitude
              << ", radio: " << radius << "): " << count << std::endl;

    // Calcular la poblacion estimada dentro de una region
    int aggregate = quadtree.aggregateRegion(center, radius);
    std::cout << "Poblacion estimada en la region (centro: " << center.longitude << ", " << center.latitude
              << ", radio: " << radius << "): " << aggregate << std::endl; */

    /*     // Prueba adicional del método countRegion()
        Point center2 = {37.4816667, -83.3252778};
        int radius2 = 20;
        int count2 = quadtree.countRegion(center2, radius2);
        std::cout << "Cantidad de puntos en la region (centro: " << center2.longitude << ", " << center2.latitude
                  << ", radio: " << radius2 << "): " << count2 << std::endl;

        // Prueba adicional del método aggregateRegion()
        int aggregate2 = quadtree.aggregateRegion(center2, radius2);
        std::cout << "Poblacion estimada en la region (centro: " << center2.longitude << ", " << center2.latitude
                  << ", radio: " << radius2 << "): " << aggregate2 << std::endl;
     */
    return 0;
}
