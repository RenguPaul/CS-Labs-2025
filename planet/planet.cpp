#include "planet.hpp"
#include <iostream>
#include <cstring>
#include <fstream>
#include <algorithm>

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

int Planet::getId() const { return id; }
const char* Planet::getName() const { return name; }
int Planet::getDiameter() const { return diameter; }
int Planet::getLife() const { return life; }
int Planet::getSatellites() const { return satellites; }

std::ostream& operator<<(std::ostream& os, const Planet& planet) {
    os << planet.id << ' '
       << planet.name << ' '
       << planet.diameter << ' '
       << planet.life << ' '
       << planet.satellites << '\n';
    return os;
}


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
    is >> buffer;
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

void Planet::readPlanetsFromFile(const char* filename, Planet** planetsArray, int& count) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Ошибка открытия файла." << std::endl;
        return;
    }

    Planet planet;
    while (infile >> planet) {
        Planet* tmp = new Planet[count + 1];

        for (int i = 0; i < count; ++i) {
            tmp[i] = (*planetsArray)[i];
        }

        delete[] *planetsArray;

        *planetsArray = tmp;

        (*planetsArray)[count] = planet;
        count++;
    }

    infile.close();
}

void Planet::writePlanetsToFile(const char* filename, Planet* planetsArray, int count) {
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

/*void Planet::sortPlanetsById(Planet* planetsArray, int count) {
    std::sort(planetsArray, planetsArray + count, [](const Planet& a, const Planet& b) {
        return a.getId() < b.getId();
    });
}

void Planet::sortPlanetsByLife(Planet* planetsArray, int count) {
    std::sort(planetsArray, planetsArray + count, [](const Planet& a, const Planet& b) {
        return a.getLife() < b.getLife();
    });
}*/

void Planet::sortPlanetsByDiameter(Planet*& planetsArray, int left, int right) {
    if (left > right) {
        return;
      }
      Planet middle = planetsArray[(left + right) / 2];
      int i = left;
      int j = right;
      while (i <= j) {
        while (planetsArray[i] < middle) {
          ++i;
        }
        while (planetsArray[j] > middle) {
          --j;
        }
        if (i <= j) {
          if (planetsArray[i].getDiameter() != planetsArray[j].getDiameter()) {
            Planet temp(planetsArray[i]);
            planetsArray[i] = planetsArray[j];
            planetsArray[j] = temp;
          }
          ++i;
          --j;
        }
      }
      sortPlanetsByDiameter(planetsArray, left, j);
      sortPlanetsByDiameter(planetsArray, i, right);
}

/*void Planet::sortPlanetsBySatellites(Planet* planetsArray, int count) {
    std::sort(planetsArray, planetsArray + count, [](const Planet& a, const Planet& b) {
        return a.getSatellites() < b.getSatellites();
    });
}*/

void Planet::deletePlanetById(const char* filename, int id, Planet* planetsArray, int& count) {
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

    for (int i = index; i < count - 1; ++i) {
        planetsArray[i] = planetsArray[i + 1];
    }

    count--;

    writePlanetsToFile(filename, planetsArray, count);
}

void Planet::showDataBase(const char *filename) {
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

  void Planet::addPlanetToFile(const char *filename, Planet &newPlanet) {
    Planet *planetArray = nullptr;
    int count = 0;
    Planet::readPlanetsFromFile(filename, &planetArray, count);

    int maxId = -1;
    for (int i = 0; i < count; ++i) {
        if (planetArray[i].getId() > maxId) {
            maxId = planetArray[i].getId();
        }
    }

    newPlanet = Planet(maxId + 1, newPlanet.getName(), newPlanet.getDiameter(),
                          newPlanet.getLife(), newPlanet.getSatellites());

    Planet *newplanetArray = new Planet[count + 1];
    for (int i = 0; i < count; ++i) {
        newplanetArray[i] = planetArray[i];
    }
    newplanetArray[count] = newPlanet;

    delete[] planetArray;

    Planet::writePlanetsToFile(filename, newplanetArray, count + 1);

    delete[] newplanetArray;
  }

  void Planet::editPlanetById(const char *filename, int id, const char *newName, int newDiameter, int newLife, int newSatelites, Planet *planetsArray, int count) {
    int index = -1;
    for (int i = 0; i < count; ++i) {
        if (planetsArray[i].getId() == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        std::cerr << "Альбом с ID " << id << " не найден." << std::endl;
        return;
    }

    if (newName != nullptr) {
        delete[] planetsArray[index].name;
        planetsArray[index].name = new char[strlen(newName) + 1];
        strcpy(planetsArray[index].name, newName);
    }
    planetsArray[index].diameter = newDiameter;
    planetsArray[index].life = newLife;
    planetsArray[index].satellites = newSatelites;

    writePlanetsToFile(filename, planetsArray, count);
  }
