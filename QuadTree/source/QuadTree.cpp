#include "..\include\QuadTree.hpp"

/**
 * @brief Constructor de la clase QuadTree.
 * @param topLeftLimit Coordenada de la esquina superior izquierda del área cubierta por el QuadTree.
 * @param lowerRightLimit Coordenada de la esquina inferior derecha del área cubierta por el QuadTree.
 */
QuadTree::QuadTree(Point topLeftLimit, Point lowerRightLimit)
{
    root = new QuadTreeNode(topLeftLimit, lowerRightLimit, "", 0);
}

/**
 * @brief Calcula la cantidad total de puntos almacenados en el QuadTree.
 * @return Cantidad total de puntos almacenados.
 */
int QuadTree::totalPoints()
{
    list<Point> pointList;
    getPointList(root, pointList);
    return pointList.size();
}

/**
 * @brief Calcula la cantidad total de nodos en el QuadTree, incluyendo tanto nodos blancos como negros.
 * @return Cantidad total de nodos.
 */
int QuadTree::totalNodes()
{
    // Total nodes = Total points + Total internal nodes
    list<Point> pointList;
    getPointList(root, pointList);
    return pointList.size() + 1;
}

/**
 * @brief Inserta un nuevo punto en el QuadTree, asociado con la información disponible (nombre de la ciudad y
 * población).
 * @param p Punto a insertar.
 * @param cityName Nombre de la ciudad asociada al punto.
 * @param population Población de la ciudad asociada al punto.
 */
void QuadTree::insert(Point p, string cityName, int population)
{
    insertNode(root, p, cityName, population);
}

/**
 * @brief Obtiene una lista de todos los puntos almacenados en el QuadTree.
 * @return Lista de puntos almacenados.
 */
list<Point> QuadTree::getPointList()
{
    list<Point> pointList;
    getPointList(root, pointList);
    return pointList;
}

/**
 * @brief Calcula la cantidad de puntos dentro de una región del plano, tomando como centro el punto p y una distancia
 * d.
 * @param p Punto central de la región.
 * @param d Distancia desde el punto central que define la región.
 * @return Cantidad de puntos dentro de la región.
 */
int QuadTree::countRegion(Point p, int d)
{
    return countPointsInRegion(root, p, d);
}

/**
 * @brief Calcula la población estimada dentro de una región del plano, tomando como centro el punto p y una distancia
 * d.
 * @param p Punto central de la región.
 * @param d Distancia desde el punto central que define la región.
 * @return Población estimada dentro de la región.
 */
int QuadTree::aggregateRegion(Point p, int d)
{
    return calculatePopulationInRegion(root, p, d);
}

/**
 * @brief Inserta un nodo en el QuadTree recursivamente.
 * @param currentNode Nodo actual en el proceso de inserción.
 * @param p Punto a insertar.
 * @param cityName Nombre de la ciudad asociada al punto.
 * @param population Población de la ciudad asociada al punto.
 */
void QuadTree::insertNode(QuadTreeNode *currentNode, Point p, string cityName, int population)
{
    if (currentNode->isBlack)
    {
        return;
    }

    // Nodo actual es hoja
    if (currentNode->topLeftLimit.x == currentNode->lowerRightLimit.x &&
        currentNode->topLeftLimit.y == currentNode->lowerRightLimit.y)
    {
        currentNode->isBlack = true;
        currentNode->cityName = cityName;
        currentNode->population = population;
        return;
    }

    // mid corresponde al punto medio
    int xMid = (currentNode->topLeftLimit.x + currentNode->lowerRightLimit.x) / 2;
    int yMid = (currentNode->topLeftLimit.y + currentNode->lowerRightLimit.y) / 2;

    if (p.x <= xMid)
    {
        /*
        Si el punto p se encuentra en el cuadrante superior-izquierdo del nodo actual, se agrega un nuevo
        nodo nw en ese cuadrante si aún no existe. Luego, la función se llama recursivamente con nw.
        */
        if (p.y <= yMid)
        {
            if (currentNode->nw == nullptr)
            {
                currentNode->nw = new QuadTreeNode(currentNode->topLeftLimit, Point(xMid, yMid), "", 0);
            }
            insertNode(currentNode->nw, p, cityName, population);
        }
        else
        {
            /*
            Si p se encuentra en el cuadrante inferior-izquierdo, se agrega un nuevo nodo sw en ese cuadrante si aún no
            existe. Luego, la función se llama recursivamente con sw.
            */
            if (currentNode->sw == nullptr)
            {
                currentNode->sw = new QuadTreeNode(Point(currentNode->topLeftLimit.x, yMid + 1),
                                                   Point(xMid, currentNode->lowerRightLimit.y), "", 0);
            }
            insertNode(currentNode->sw, p, cityName, population);
        }
    }
    else
    {
        /*
        Si p se encuentra en el cuadrante superior-derecho, se agrega un nuevo nodo ne en ese cuadrante si aún no
        existe. Luego, la función se llama recursivamente con ne.
        */
        if (p.y <= yMid)
        {
            if (currentNode->ne == nullptr)
            {
                currentNode->ne = new QuadTreeNode(Point(xMid + 1, currentNode->topLeftLimit.y),
                                                   Point(currentNode->lowerRightLimit.x, yMid), "", 0);
            }
            insertNode(currentNode->ne, p, cityName, population);
        }
        else
        {
            /*
            Si p se encuentra en el cuadrante inferior-derecho, se agrega un nuevo nodo se en ese cuadrante si aún no
            existe. Luego, la función se llama recursivamente con se.
            */
            if (currentNode->se == nullptr)
            {
                currentNode->se = new QuadTreeNode(Point(xMid + 1, yMid + 1), currentNode->lowerRightLimit, "", 0);
            }
            insertNode(currentNode->se, p, cityName, population);
        }
    }
}

/**
 * @brief Obtiene una lista de todos los puntos almacenados en el QuadTree.
 * @param node Nodo actual en el proceso de obtención de puntos.
 * @param pointList Lista de puntos.
 */
void QuadTree::getPointList(QuadTreeNode *node, list<Point> &pointList)
{
    if (node == nullptr)
    {
        return;
    }

    if (node->isBlack)
    {
        pointList.push_back(Point((node->topLeftLimit.x + node->lowerRightLimit.x) / 2,
                                  (node->topLeftLimit.y + node->lowerRightLimit.y) / 2));
    }
    else
    {
        getPointList(node->nw, pointList);
        getPointList(node->ne, pointList);
        getPointList(node->sw, pointList);
        getPointList(node->se, pointList);
    }
}

/**
 * @brief Calcula la cantidad de puntos dentro de una región del plano, tomando como centro el punto p y una distancia
 * d.
 * @param node Nodo actual en el proceso de conteo de puntos.
 * @param p Punto central de la región.
 * @param d Distancia desde el punto central que define la región.
 * @return Cantidad de puntos dentro de la región.
 */
int QuadTree::countPointsInRegion(QuadTreeNode *node, Point p, int d)
{
    if (node == nullptr)
    {
        return 0;
    }

    if (node->isBlack)
    {
        if (p.x - d <= (node->topLeftLimit.x + node->lowerRightLimit.x) / 2 &&
            p.x + d >= (node->topLeftLimit.x + node->lowerRightLimit.x) / 2 &&
            p.y - d <= (node->topLeftLimit.y + node->lowerRightLimit.y) / 2 &&
            p.y + d >= (node->topLeftLimit.y + node->lowerRightLimit.y) / 2)
        {
            return 1;
        }
        return 0;
    }

    int count = 0;
    int xMid = (node->topLeftLimit.x + node->lowerRightLimit.x) / 2;
    int yMid = (node->topLeftLimit.y + node->lowerRightLimit.y) / 2;

    if (p.x - d <= xMid)
    {
        if (p.y - d <= yMid)
        {
            count += countPointsInRegion(node->nw, p, d);
        }
        if (p.y + d > yMid)
        {
            count += countPointsInRegion(node->sw, p, d);
        }
    }
    if (p.x + d > xMid)
    {
        if (p.y - d <= yMid)
        {
            count += countPointsInRegion(node->ne, p, d);
        }
        if (p.y + d > yMid)
        {
            count += countPointsInRegion(node->se, p, d);
        }
    }

    return count;
}

/**
 * @brief Calcula la población estimada dentro de una región del plano, tomando como centro el punto p y una distancia
 * d.
 * @param node Nodo actual en el proceso de cálculo de población.
 * @param p Punto central de la región.
 * @param d Distancia desde el punto central que define la región.
 * @return Población estimada dentro de la región.
 */
int QuadTree::calculatePopulationInRegion(QuadTreeNode *node, Point p, int d)
{
    if (node == nullptr)
    {
        return 0;
    }

    if (node->isBlack)
    {
        if (p.x - d <= (node->topLeftLimit.x + node->lowerRightLimit.x) / 2 &&
            p.x + d >= (node->topLeftLimit.x + node->lowerRightLimit.x) / 2 &&
            p.y - d <= (node->topLeftLimit.y + node->lowerRightLimit.y) / 2 &&
            p.y + d >= (node->topLeftLimit.y + node->lowerRightLimit.y) / 2)
        {
            return node->population;
        }
        return 0;
    }

    int population = 0;
    int xMid = (node->topLeftLimit.x + node->lowerRightLimit.x) / 2;
    int yMid = (node->topLeftLimit.y + node->lowerRightLimit.y) / 2;

    if (p.x - d <= xMid)
    {
        if (p.y - d <= yMid)
        {
            population += calculatePopulationInRegion(node->nw, p, d);
        }
        if (p.y + d > yMid)
        {
            population += calculatePopulationInRegion(node->sw, p, d);
        }
    }
    if (p.x + d > xMid)
    {
        if (p.y - d <= yMid)
        {
            population += calculatePopulationInRegion(node->ne, p, d);
        }
        if (p.y + d > yMid)
        {
            population += calculatePopulationInRegion(node->se, p, d);
        }
    }

    return population;
}
