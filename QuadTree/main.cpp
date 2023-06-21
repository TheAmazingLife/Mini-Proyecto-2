#include "include\QuadTree.hpp"
#include <bits/stdc++.h>
using namespace std;

/**
 * @brief Encuentra la "," de un numero y la transforme en ".". (Ambos numeros siguen representados en cadena de
 * caracteres)
 *
 * @param str
 */
void commaToDot(string &str)
{
    size_t found = str.find(",");
    while (found != std::string::npos)
    {
        str.replace(found, 1, ".");
        found = str.find(",", found + 1);
    }
}

int main()
{
    /*
    TODO Ubicar puntos negativos en el plano 2D
    */
    // Crear un QuadTree
    QuadTree quadTree(Point(-1000000000, -1000000000), Point(1000000000, 1000000000));

    ifstream file("prueba.csv");
    string line;
    int lineIndex = 1;

    // Leer la primera línea (títulos)
    getline(file, line);

    // Leer las líneas restantes
    while (getline(file, line))
    {
        stringstream ss(line);
        string token;
        vector<string> tokens;

        // Dividir la línea en columnas
        while (getline(ss, token, ';'))
        {
            commaToDot(token);
            tokens.push_back(token);
            cout << token << endl;
        }

        if (tokens.size() >= 7)
        {
            // Obtener los valores de las columnas relevantes
            double x = stoi(tokens[5]);       // 6ta columna
            double y = stoi(tokens[6]);       // 7ma columna
            string cityName = tokens[1];      // 2da columna
            int population = stoi(tokens[4]); // 5ta columna

            // Insertar el punto en el QuadTree
            quadTree.insert(Point(x, y), cityName, population);
        }
    }

    file.close();

    cout << "Número total de nodos en el QuadTree: " << quadTree.totalNodes() << endl;
    cout << "Población total en la región: " << quadTree.countRegion(Point(0, 0), 8) << endl;

    return 0;
}
