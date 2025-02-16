#include "planet.hpp"
#include <iostream>
#include <cstring>
#include <fstream>
#include <algorithm>

// Конструкторы
Planet::Planet() : id(-1), name(nullptr), diameter(0), life(0), satellites(0) {
    //std::cout << "Создание планеты по умолчанию" << std::endl;
}

Planet::Planet(int _id, const char* _name, int _diameter, int _life, int _satellites)
    : id(_id), diameter(_diameter), life(_life), satellites(_satellites) {
    //std::cout << "Создание планеты " << _name << "С ID: " << _id << std::endl;
    name = new char[strlen(_name) + 1];
    strcpy(name, _name);
}

Planet::Planet(const Planet& other) {
    //std::cout << "Создание копии планеты " << other.name << "С ID: " << other.id << std::endl;
    id = other.id;
    diameter = other.diameter;
    life = other.life;
    satellites = other.satellites;
    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);
}

Planet& Planet::operator=(const Planet& other) {
    if (this != &other) {
        delete[] name;

        id = other.id;
        diameter = other.diameter;
        life = other.life;
        satellites = other.satellites;
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
    }
    return *this;
}

Planet::~Planet() {
    //std::cout << "Планета " << this->name << ' ' << "С ID: " << this->id << "удалена" << std::endl;
    delete[] name;
}

// Геттеры
int Planet::getId() const { return id; }
const char* Planet::getName() const { return name; }
int Planet::getDiameter() const { return diameter; }
int Planet::getLife() const { return life; }
int Planet::getSatellites() const { return satellites; }

// Оператор вывода
std::ostream& operator<<(std::ostream& os, const Planet& planet) {
    os << planet.id << ' '
       << planet.name << ' '
       << planet.diameter << ' '
       << planet.life << ' '
       << planet.satellites << '\n';
    return os;
}

// Оператор ввода
std::istream& operator>>(std::istream& is, Planet& planet) {
    if (planet.name != nullptr) {
        delete[] planet.name;
        planet.name = nullptr;
    }

    is >> planet.id;
    if (is.fail()) {
        return is;
    }

    char buffer[100];
    is >> buffer;  // Считываем только первое слово (имя планеты)
    size_t len = strlen(buffer);
    planet.name = new char[len + 1];
    strcpy(planet.name, buffer);

    is >> planet.diameter;
    if (is.fail()) {
        return is;
    }

    is >> planet.life;
    if (is.fail()) {
        return is;
    }

    is >> planet.satellites;
    if (is.fail()) {
        return is;
    }

    return is;
}

// Чтение планет из файла
void readPlanetsFromFile(const char* filename, Planet** planetsArray, int& count) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Ошибка открытия файла." << std::endl;
        return;
    }

    Planet planet;
    while (infile >> planet) {
        // Создаем новый массив большего размера
        Planet* tmp = new Planet[count + 1];

        // Копируем старые элементы
        for (int i = 0; i < count; ++i) {
            tmp[i] = (*planetsArray)[i];
        }

        // Освобождаем память старого массива
        delete[] *planetsArray;

        // Присваиваем новый массив
        *planetsArray = tmp;

        // Добавляем новый элемент
        (*planetsArray)[count] = planet;
        count++;
    }

    infile.close();
}

// Запись планет в файл
void writePlanetsToFile(const char* filename, Planet* planetsArray, int count) {
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "Ошибка открытия файла." << std::endl;
        return;
    }

    for (int i = 0; i < count; ++i) {
        outfile << planetsArray[i];
    }

    outfile.close();
}

// Сортировка по ID
void sortPlanetsById(Planet* planetsArray, int count) {
    std::sort(planetsArray, planetsArray + count, [](const Planet& a, const Planet& b) {
        return a.getId() < b.getId();
    });
}

// Сортировка по наличию жизни
void sortPlanetsByLife(Planet* planetsArray, int count) {
    std::sort(planetsArray, planetsArray + count, [](const Planet& a, const Planet& b) {
        return a.getLife() < b.getLife();
    });
}

// Сортировка по диаметру
void sortPlanetsByDiameter(Planet* planetsArray, int count) {
    std::sort(planetsArray, planetsArray + count, [](const Planet& a, const Planet& b) {
        return a.getDiameter() < b.getDiameter();
    });
}

// Сортировка по количеству спутников
void sortPlanetsBySatellites(Planet* planetsArray, int count) {
    std::sort(planetsArray, planetsArray + count, [](const Planet& a, const Planet& b) {
        return a.getSatellites() < b.getSatellites();
    });
}

// Удаление планеты по ID
void deletePlanetById(const char* filename, int id, Planet* planetsArray, int& count) {
    // Ищем планету с указанным ID
    int index = -1;
    for (int i = 0; i < count; ++i) {
        if (planetsArray[i].getId() == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        std::cerr << "Планета с ID " << id << " не найдена." << std::endl;
        return;
    }

    // Сдвигаем элементы массива
    for (int i = index; i < count - 1; ++i) {
        planetsArray[i] = planetsArray[i + 1];
    }

    // Уменьшаем количество планет
    count--;

    // Перезаписываем файл
    writePlanetsToFile(filename, planetsArray, count);
}

void showDataBase(const char* filename) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Ошибка открытия файла." << std::endl;
        return;
    }
    std::cout << "Вывод БД" << std::endl;
    Planet planet;
    while (infile >> planet) {
        std::cout << planet;
    }

    infile.close();
}
