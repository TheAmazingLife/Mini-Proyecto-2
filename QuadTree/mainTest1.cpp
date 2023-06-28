#include "include/DataFormatter.hpp"
#include "include/Point.hpp"
#include "include/Quadtree.hpp"
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

void insertTest(QuadTree *quadtree, int n)
{
    std::cout << "Se insertan: " << n << " ciudades" << std::endl;

    std::ifstream inputFile("DataSet/worldcitiespop_fixed.csv"); // Incluimos el .csv testeo
    std::stringstream buffer;
    buffer << inputFile.rdbuf();
    std::string input = buffer.str();

    // Formatear los datos
    std::vector<std::tuple<Point, std::string, int>> formattedData = formatData(input);

    // Tiempo de ejecución de insert
    auto start = std::chrono::high_resolution_clock::now();
    auto data = formattedData.begin();
    for (int i = 0; i < n; i++)
    {
        Point point = std::get<0>(*data);
        std::string cityName = std::get<1>(*data);
        int population = std::get<2>(*data);
        quadtree->insert(point, cityName, population);
        data++;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsedTime = end - start;

    std::cout << "Tiempo total: " << elapsedTime.count() << " ms" << std::endl;
    double tiempo_promedio = static_cast<double>(elapsedTime.count()) / n;
    std::cout << "Tiempo promedio: " << std::fixed << std::setprecision(6) << tiempo_promedio << " ms" << std::endl
              << std::endl
              << std::endl;
}

void countRegionTest(QuadTree *quadtree, Point center, int r)
{
    int count = quadtree->countRegion(center, r);
    std::cout << "Cantidad de puntos en la region (centro: " << center.x << ", " << center.y << ", radio: " << r
              << ", rango: " << 2 * r + 1 << "X" << 2 * r + 1 << ") " << count << std::endl;
}
void aggregateRegionTest(QuadTree *quadtree, Point center, int r)
{
    int aggregate = quadtree->aggregateRegion(center, r);
    std::cout << "Poblacion estimada en la region (centro: " << center.x << ", " << center.y << ", radio: " << r
              << ", rango: " << 2 * r + 1 << "X" << 2 * r + 1 << ") " << aggregate << std::endl;
}

int main()
{
    int n;
    int r;
    int cities[6] = {100000, 200000, 400000, 800000, 1600000, 3173647};
    int radio[6] = {2, 100, 20000, 520000, 1000000, 3173647};
    int expNum = 1;
    while (expNum <= 20)
    {
        std::cout << "Experimento nro: " << expNum << std::endl;
        // Crear el Quadtree y cargar los datos
        QuadTree quadtree;
        for (int i = 0; i < 5; i++)
        {
            n = cities[i];

            // test de inserción
            insertTest(&quadtree, n);

            // Obtener la cantidad total de puntos
            int totalPoints = quadtree.totalPoints();
            std::cout << "Cantidad total de puntos: " << totalPoints << std::endl;

            // Obtener la cantidad total de nodos
            int totalNodes = quadtree.totalNodes();
            std::cout << "Cantidad total de nodos: " << totalNodes << std::endl;

            // Obtener la lista de puntos almacenados en el Quadtree
            std::list<Node *> pointList = quadtree.getPointList();
            // std::cout << "Cantidad de datos encontrados: " << pointList.size() << std::endl;
            
            /*std::cout << "Lista de puntos almacenados en el Quadtree:" << std::endl;
            for (const auto &node : pointList)
            {
                std::cout << "Ciudad: " << node->cityName << ", Poblacion: " << node->population
                          << ", Longitud: " << node->point.x << ", Latitud: " << node->point.y << std::endl;
            }*/

            // ciudades en un radio de r (ciudades en area de 2*r+1 X 2*r+1), a partir del (0, 0)
            Point center = {0, 0};
            for (int j = 0; i < 6; j++)
            {
                r = radio[j];
                // Contar la cantidad de puntos en una region
                countRegionTest(&quadtree, center, r);

                // Calcular la poblacion estimada dentro de una region
                aggregateRegionTest(&quadtree, center, r);
            }
        }
        expNum++;
    }
    return 0;
}
