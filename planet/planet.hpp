#ifndef PLANET_HPP
#define PLANET_HPP

#include <iostream>
#include <cstring>

class Planet {
public:
    // Конструкторы
    Planet();
    Planet(int _id, const char* _name, int _diameter, int _life, int _satellites);
    Planet(const Planet& other); // Конструктор копирования
    ~Planet();

    // Оператор присваивания
    Planet& operator=(const Planet& other);

    // Геттеры
    int getId() const;
    const char* getName() const;
    int getDiameter() const;
    int getLife() const;
    int getSatellites() const;

    // Дружественные операторы ввода и вывода
    friend std::ostream& operator<<(std::ostream& os, const Planet& planet);
    friend std::istream& operator>>(std::istream& is, Planet& planet);

private:
    int id;          // Уникальный идентификатор планеты
    char* name;      // Название планеты
    int diameter;    // Диаметр планеты
    int life;        // Наличие жизни (0 - нет, 1 - есть)
    int satellites;  // Количество спутников
};

// Функции для работы с файлами и массивом планет
void readPlanetsFromFile(const char* filename, Planet** planetsArray, int& count);
void writePlanetsToFile(const char* filename, Planet* planetsArray, int count);
void sortPlanetsById(Planet* planetsArray, int count);
void sortPlanetsByLife(Planet* planetsArray, int count);
void sortPlanetsByDiameter(Planet* planetsArray, int count);
void sortPlanetsBySatellites(Planet* planetsArray, int count);
void deletePlanetById(const char* filename, int id, Planet* planetsArray, int& count);
void showDataBase(const char* filename);

#endif // PLANET_HPP
