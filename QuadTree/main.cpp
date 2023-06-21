#include <iostream>
#include <fstream>
#include <sstream>
#include <tuple>
#include <vector>
#include "include/Quadtree.hpp"

// Función auxiliar para reemplazar la coma por un punto en una cadena
std::string replaceCommaWithDot(const std::string &str)
{
    std::string result = str;
    std::size_t commaPos = result.find(',');
    if (commaPos != std::string::npos)
    {
        result.replace(commaPos, 1, ".");
    }
    return result;
}

// Función para formatear la entrada en un formato admitido por insert
std::vector<std::tuple<Point, std::string, int>> formatData(const std::string &input)
{
    std::vector<std::tuple<Point, std::string, int>> formattedData;

    std::istringstream iss(input);
    std::string line;
    std::getline(iss, line); // Ignorar la primera línea (encabezado)

    while (std::getline(iss, line))
    {
        std::istringstream lineStream(line);
        std::string field;
        std::vector<std::string> fields;

        while (std::getline(lineStream, field, ';'))
        {
            fields.push_back(field);
        }

        if (fields.size() >= 8)
        {
            double latitude = std::stod(replaceCommaWithDot(fields[5]));
            double longitude = std::stod(replaceCommaWithDot(fields[6]));
            int population = std::stoi(fields[4]);

            Point point = {longitude, latitude};
            std::tuple<Point, std::string, int> dataTuple = std::make_tuple(point, fields[2], population);

            formattedData.push_back(dataTuple);
        }
    }

    return formattedData;
}
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
    std::ifstream inputFile("../DataSet/worldcitiespop_fixed.csv");
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
        quadtree.insert(point, cityName, population);
    }

    // Obtener la cantidad total de puntos
    int totalPoints = quadtree.totalPoints();
    std::cout << "Cantidad total de puntos: " << totalPoints << std::endl;

    // Obtener la cantidad total de nodos
    int totalNodes = quadtree.totalNodes();
    std::cout << "Cantidad total de nodos: " << totalNodes << std::endl;

    // Contar la cantidad de puntos en una región
    Point center = {40.920404, 39.19209};
    int radius = 10;
    int count = quadtree.countRegion(center, radius);
    std::cout << "Cantidad de puntos en la región (centro: " << center.longitude << ", " << center.latitude
              << ", radio: " << radius << "): " << count << std::endl;

    // Calcular la población estimada dentro de una región
    int aggregate = quadtree.aggregateRegion(center, radius);
    std::cout << "Población estimada en la región (centro: " << center.longitude << ", " << center.latitude
              << ", radio: " << radius << "): " << aggregate << std::endl;

    // Prueba adicional del método countRegion()
    Point center2 = {37.4816667, -83.3252778};
    int radius2 = 20;
    int count2 = quadtree.countRegion(center2, radius2);
    std::cout << "Cantidad de puntos en la región (centro: " << center2.longitude << ", " << center2.latitude
              << ", radio: " << radius2 << "): " << count2 << std::endl;

    // Prueba adicional del método aggregateRegion()
    int aggregate2 = quadtree.aggregateRegion(center2, radius2);
    std::cout << "Población estimada en la región (centro: " << center2.longitude << ", " << center2.latitude
              << ", radio: " << radius2 << "): " << aggregate2 << std::endl;

    // Obtener la lista de puntos almacenados en el Quadtree
    std::list<Point> pointList = quadtree.getPointList();
    std::cout << "Lista de puntos almacenados en el Quadtree:" << std::endl;
    for (const auto &point : pointList)
    {
        std::cout << "Longitud: " << point.longitude << ", Latitud: " << point.latitude << std::endl;
    }

    return 0;
}
