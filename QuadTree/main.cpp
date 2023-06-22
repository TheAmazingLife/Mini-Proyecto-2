#include <iostream>
#include <fstream>
#include <vector>

#include "include/Point.hpp"
#include "include/Quadtree.hpp"
#include "include/DataFormatter.hpp"

/*
void insertTest(Quadtree *quadtree, int n)
{
    auto start = chrono::high_resolution_clock::now();

    int count = 0;
    for (const auto &data : formattedData)
    {
        while (count < n)
        {
            Point point = std::get<0>(data);
            std::string cityName = std::get<1>(data);
            int population = std::get<2>(data);
            quadtree.insert(point, cityName, population);
            n++;
        }
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> elapsedTime = end - start;

    cout << "Tiempo total: " << elapsedTime.count() << " ms" << endl;
    double tiempo_promedio = static_cast<double>(elapsedTime.count()) / n;
    cout << "Tiempo promedio: " << fixed << setprecision(6) << tiempo_promedio << " ms" << endl << endl;
}
*/

int main()
{
    // Leer datos desde el archivo de entrada

    // ! RECORDAR CAMBIAR ESTA WEA
    std::ifstream inputFile("DataSet/worldcitiespop_fixed.csv");
    // std::ifstream inputFile("DataSet/test1.csv");

    std::stringstream buffer;
    buffer << inputFile.rdbuf();
    std::string input = buffer.str();

    // Formatear los datos
    std::vector<std::tuple<Point, std::string, int>> formattedData = formatData(input);

    // Crear el Quadtree y cargar los datos
    Quadtree quadtree;

    // vector<int> inputSizes = {100000, 200000, 400000, 800000, 1600000, 3173647};

    /*
    for (int size : inputSizes)
    {
        cout << "--------- Experimento ---------" << endl << endl;
        cout << "size: " << size << endl << endl;
        cout << "insert:" << endl;
        insertTest(&quadtree, size);
    }
    */

    for (const auto &data : formattedData)
    {
        Point point = std::get<0>(data);
        std::string cityName = std::get<1>(data);
        int population = std::get<2>(data);
        // ! comprobar en que formato imprime el nombre
        // std::cout << cityName << "_";
        quadtree.insert(point, cityName, population);
    }

    // Obtener la cantidad total de puntos
    int totalPoints = quadtree.totalPoints();
    std::cout << "Cantidad total de puntos: " << totalPoints << std::endl;

    // Obtener la cantidad total de nodos
    int totalNodes = quadtree.totalNodes();
    std::cout << "Cantidad total de nodos: " << totalNodes << std::endl;

    // ! RECORDAR DESCOMENTAR quadtree.printColorAndLevel();

    // ? metodo que busca una ciudad
    // ! en desarrollo
    quadtree.searchCity("Concepcion"); // acepta hasta el nodo 94

    // Obtener la lista de puntos almacenados en el Quadtree
    std::list<Point> pointList = quadtree.getPointList();
    std::cout << pointList.size() << "Cantidad de datos encontrados:" << std::endl;
    std::cout << "Lista de puntos almacenados en el Quadtree:" << std::endl;
    for (const auto &point : pointList)
    {
        std::cout << "Longitud: " << point.longitude << ", Latitud: " << point.latitude << std::endl;
    }

    return 0;
}
