#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

#include "include/DataFormatter.hpp"
#include "include/Point.hpp"
#include "include/Quadtree.hpp"

void insertTest(QuadTree *quadtree, int n)
{
    std::cout << "-- Se insertan: " << n << " ciudades --" << std::endl;

    std::ifstream inputFile("DataSet/worldcitiespop_fixed.csv"); // Incluimos el .csv testeo
    std::stringstream buffer;
    buffer << inputFile.rdbuf();
    std::string input = buffer.str();

    // Formatear los datos
    std::vector<std::tuple<Point, std::string, int>> formattedData = formatData(input);

    // Tiempo de ejecución de insert
    auto data = formattedData.begin();
    for (int i = 0; i < n; i++)
    {
        Point point = std::get<0>(*data);
        std::string cityName = std::get<1>(*data);
        int population = std::get<2>(*data);
        quadtree->insert(point, cityName, population);
        data++;
    }
}

void countRegionTest(QuadTree *quadtree, Point center, int r)
{

    // Tiempo de ejecución de countRegion
    auto start = std::chrono::high_resolution_clock::now();

    int count = quadtree->countRegion(center, r);
    std::cout << "Cantidad de puntos en la region (centro: " << center.x << ", " << center.y << ", radio: " << r
              << ", rango: " << r << " X " << r << "): " << count << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsedTime = end - start;

    std::cout << "Tiempo total countRegion(): " << elapsedTime.count() << " ms" << std::endl;
}

void aggregateRegionTest(QuadTree *quadtree, Point center, int r)
{
    // Tiempo de ejecución de aggregateRegion
    auto start = std::chrono::high_resolution_clock::now();

    int aggregate = quadtree->aggregateRegion(center, r);
    std::cout << "Poblacion estimada en la region (centro: " << center.x << ", " << center.y << ", radio: " << r
              << ", rango: " << r << " X " << r << "): " << aggregate << std::endl;

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsedTime = end - start;
    std::cout << "Tiempo total aggregateRegion(): " << elapsedTime.count() << " ms" << std::endl;
}

int main()
{
    int n;
    int r;
    int cities[6] = {100000, 200000, 400000, 800000, 1600000, 3173647};
    int radio[6] = {15, 30, 45, 60, 75, 90};
    int expNum = 1;
    while (expNum <= 20)
    {
        std::cout << "* Experimento N:" << expNum << std::endl;

        // Crear el Quadtree y cargar los datos
        QuadTree quadtree;
        for (int i = 0; i < 6; i++)
        {
            n = cities[i];

            // insertar los datos
            insertTest(&quadtree, n);

            // ciudades en un radio de r (ciudades en area de 2*r+1 X 2*r+1), a partir del (0, 0)
            Point center = {0, 0};
            for (int j = 0; j < 6; j++)
            {
                r = radio[j];
                std::cout << ">> Prueba radio: " << r << std::endl;
                // Contar la cantidad de puntos en una region
                countRegionTest(&quadtree, center, r);

                // Calcular la poblacion estimada dentro de una region
                aggregateRegionTest(&quadtree, center, r);
                std::cout << '\n';
            }
            std::cout << '\n';
        }
        std::cout << '\n';
        expNum++;
    }
    return 0;
}
