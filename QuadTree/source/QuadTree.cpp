#include "../include/Quadtree.hpp"

Quadtree::Quadtree() : root(new Node()) {}

Quadtree::~Quadtree() {
    clear();
}

void Quadtree::clear() {
    clearRecursive(root);
    root = new Node();
}

void Quadtree::clearRecursive(Node* node) {
    if (node->color == "White") {
        return;
    }

    clearRecursive(node->NW);
    clearRecursive(node->NE);
    clearRecursive(node->SW);
    clearRecursive(node->SE);

    delete node;
}

void Quadtree::insert(Point p, std::string cityName, int population) {
    insertRecursive(root, p, cityName, population);
}

void Quadtree::insertRecursive(Node*& node, Point p, std::string cityName, int population) {
    if (node->color == "White") {
        node = new Node(p, cityName, population, "Black"); // Asigna "Black" cuando se inserta información
    } else {
        if (p.longitude < node->point.longitude) {
            if (p.latitude < node->point.latitude) {
                insertRecursive(node->SW, p, cityName, population);
            } else {
                insertRecursive(node->NW, p, cityName, population);
            }
        } else {
            if (p.latitude < node->point.latitude) {
                insertRecursive(node->SE, p, cityName, population);
            } else {
                insertRecursive(node->NE, p, cityName, population);
            }
        }
    }
}

int Quadtree::totalPoints() {
    return totalPointsRecursive(root);
}

int Quadtree::totalNodes() {
    return totalNodesRecursive(root);
}

std::list<Point> Quadtree::getPointList() {
    std::list<Point> pointList;
    getPointListRecursive(root, pointList);
    return pointList;
}

int Quadtree::countRegion(Point p, int d) {
    return countRegionRecursive(root, p, d);
}

int Quadtree::aggregateRegion(Point p, int d) {
    return aggregateRegionRecursive(root, p, d);
}

int Quadtree::totalPointsRecursive(Node* node) {
    if (node->color == "White") {
        return 0;
    }

    int count = 1;

    count += totalPointsRecursive(node->NW);
    count += totalPointsRecursive(node->NE);
    count += totalPointsRecursive(node->SW);
    count += totalPointsRecursive(node->SE);

    return count;
}

int Quadtree::totalNodesRecursive(Node* node) {
    if (node->color == "White") {
        return 0;
    }

    int count = 1;

    count += totalNodesRecursive(node->NW);
    count += totalNodesRecursive(node->NE);
    count += totalNodesRecursive(node->SW);
    count += totalNodesRecursive(node->SE);

    return count;
}

void Quadtree::getPointListRecursive(Node* node, std::list<Point>& pointList) {
    if (node->color == "White") {
        return;
    }

    pointList.push_back(node->point);

    getPointListRecursive(node->NW, pointList);
    getPointListRecursive(node->NE, pointList);
    getPointListRecursive(node->SW, pointList);
    getPointListRecursive(node->SE, pointList);
}

int Quadtree::countRegionRecursive(Node* node, Point p, int d) {
    if (node->color == "White") {
        return 0;
    }

    double dx = node->point.longitude - p.longitude;
    double dy = node->point.latitude - p.latitude;
    int count = 0;

    if (dx * dx + dy * dy <= d * d) {
        count++;
    }

    count += countRegionRecursive(node->NW, p, d);
    count += countRegionRecursive(node->NE, p, d);
    count += countRegionRecursive(node->SW, p, d);
    count += countRegionRecursive(node->SE, p, d);

    return count;
}

int Quadtree::aggregateRegionRecursive(Node* node, Point p, int d) {
    if (node->color == "White") {
        return 0;
    }

    double dx = node->point.longitude - p.longitude;
    double dy = node->point.latitude - p.latitude;
    int aggregate = 0;

    if (dx * dx + dy * dy <= d * d) {
        aggregate += node->population;
    }

    aggregate += aggregateRegionRecursive(node->NW, p, d);
    aggregate += aggregateRegionRecursive(node->NE, p, d);
    aggregate += aggregateRegionRecursive(node->SW, p, d);
    aggregate += aggregateRegionRecursive(node->SE, p, d);

    return aggregate;
}
