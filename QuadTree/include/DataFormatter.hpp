#ifndef DATA_FORMATTER_HPP
#define DATA_FORMATTER_HPP

#include <sstream>
#include <tuple>
#include <string>
#include <vector>

#include "Point.hpp"

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
    std::getline(iss, line); // Ignorar la primera linea (encabezado)

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

#endif