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
    bool operator>(const Planet& planet) const {
        return this->diameter > planet.diameter;
    }
    bool operator==(const Planet& planet) const {
        return this->diameter == planet.diameter;
    }
    bool operator!=(const Planet& planet) const {
        return !(this->diameter == planet.diameter);
    }
    bool operator<(const Planet& planet) const {
        return !(this->diameter > planet.diameter);
    }

    static void readPlanetsFromFile(const char* filename, Planet** planetsArray, int& count);
    static void writePlanetsToFile(const char* filename, Planet* planetsArray, int count);
    /*static void sortPlanetsById(Planet* planetsArray, int count);
    static void sortPlanetsByLife(Planet* planetsArray, int count);*/
    static void sortPlanetsByDiameter(Planet*& planetsArray, int left, int right);
    /*static void sortPlanetsBySatellites(Planet* planetsArray, int count);*/
    static void deletePlanetById(const char* filename, int id, Planet* planetsArray, int& count);
    static void showDataBase(const char* filename);
    static void addPlanetToFile(const char* filename, Planet& newPlanet);
    static void editPlanetById(const char *filename, int id, const char *newName, int newDiameter, int newLife, int newSatelites, Planet *AlbumsArray, int count);


private:
    int id;
    char* name;
    int diameter;
    int life;
    int satellites;
};



#endif // PLANET_HPP
