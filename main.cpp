#include "planet/planet.hpp"
#include <iostream>

int main() {
    const char* filename = "planets.txt";
    Planet* planets = nullptr;
    int count = 0;

    showDataBase(filename);

    // Чтение данных из файла
    readPlanetsFromFile(filename, &planets, count);

    // Сортировка по ID
    sortPlanetsByDiameter(planets, count);
    std::cout << "Сортировка по ID:\n";
    for (int i = 0; i < count; ++i) {
        std::cout << planets[i];
    }

    // Удаление планеты с ID = 2
    deletePlanetById(filename, 2, planets, count);
    std::cout << "После удаления планеты с ID = 2:\n";
    for (int i = 0; i < count; ++i) {
        std::cout << planets[i];
    }
    showDataBase(filename);

    // Освобождение памяти
    delete[] planets;

    return 0;
}
