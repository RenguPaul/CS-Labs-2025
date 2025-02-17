#include "planet/planet.hpp"
#include <iostream>

int main() {
    const char* filename = "planets.txt";
    Planet* planets = nullptr;
    int count = 0;

    showDataBase(filename);

    readPlanetsFromFile(filename, &planets, count);

    sortPlanetsByDiameter(planets, count);
    std::cout << "Сортировка по ID:\n";
    for (int i = 0; i < count; ++i) {
        std::cout << planets[i];
    }

    deletePlanetById(filename, 2, planets, count);
    std::cout << "После удаления планеты с ID = 2:\n";
    for (int i = 0; i < count; ++i) {
        std::cout << planets[i];
    }
    showDataBase(filename);

    delete[] planets;

    return 0;
}
