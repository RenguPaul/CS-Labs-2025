#ifndef PLANET_HPP
#define PLANET_HPP

#include <iostream>
#include <cstring>

class Planet {
public:

    Planet();
    Planet(int _id, const char* _name, int _diameter, int _life, int _satellites);
    Planet(const Planet& other);
    ~Planet();

    Planet& operator=(const Planet& other);

    int getId() const;
    const char* getName() const;
    int getDiameter() const;
    int getLife() const;
    int getSatellites() const;


    friend std::ostream& operator<<(std::ostream& os, const Planet& planet);
    friend std::istream& operator>>(std::istream& is, Planet& planet);

private:
    int id;
    char* name;
    int diameter;
    int life;
    int satellites;
};

void readPlanetsFromFile(const char* filename, Planet** planetsArray, int& count);
void writePlanetsToFile(const char* filename, Planet* planetsArray, int count);
void sortPlanetsById(Planet* planetsArray, int count);
void sortPlanetsByLife(Planet* planetsArray, int count);
void sortPlanetsByDiameter(Planet* planetsArray, int count);
void sortPlanetsBySatellites(Planet* planetsArray, int count);
void deletePlanetById(const char* filename, int id, Planet* planetsArray, int& count);
void showDataBase(const char* filename);

#endif // PLANET_HPP
