#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

#include "include/Point.hpp"
#include "include/Quadtree.hpp"
#include "include/DataFormatter.hpp"

int main()
{
    std::ifstream inputFile("DataSet/worldcitiespop_fixed.csv");
    std::stringstream buffer;
    buffer << inputFile.rdbuf();
    std::string input = buffer.str();

    std::vector<std::tuple<Point, std::string, int>> formattedData = formatData(input);

    std::vector<int> cityCounts = {100000, 200000, 400000, 800000, 1600000, static_cast<int>(formattedData.size())};

    const int numIterations = 20;

    for (int count : cityCounts)
    {
        long long totalDuration = 0;

        for (int i = 0; i < numIterations; i++)
        {
            Quadtree quadtree;
            auto dataSubset = std::vector<std::tuple<Point, std::string, int>>(formattedData.begin(), formattedData.begin() + count);

            auto start = std::chrono::high_resolution_clock::now();

            for (const auto &data : dataSubset)
            {
                Point point = std::get<0>(data);
                std::string cityName = std::get<1>(data);
                int population = std::get<2>(data);
                quadtree.insert(point, cityName, population);
            }

            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

            totalDuration += duration.count();
        }

        double averageDuration = static_cast<double>(totalDuration) / numIterations;

        std::cout << "Tiempo promedio de insercion para " << count << " ciudades: " << averageDuration << " ms" << std::endl;
    }

    return 0;
}
