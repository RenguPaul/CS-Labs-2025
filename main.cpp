#include "musicAlbum/musicAlbum.hpp"
#include "planet/planet.hpp"
#include <iostream>
#include <limits> // Для std::numeric_limits

enum class Options : int {
    ReadDB = 1,
    AddElement = 2,
    SortDB = 3,
    DeleteElement = 4,
    EditElement = 5,
    WriteDB = 6
};

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Ошибка: Не указан режим работы. Используйте 'd' для демо-режима или 'i' для интерактивного режима.\n";
        return 1;
    }

    char* mode = argv[1];
    std::cout << "Режим: " << mode << "\n";

    if (mode[0] == 'd') {
        const char* filename = "planets.txt";
        Planet* Planets = nullptr;
        int count = 0;

        Planet::showDataBase(filename);

        Planet::readPlanetsFromFile(filename, &Planets, count);

        Planet::sortPlanetsByDiameter(Planets, 0, count - 1);
        std::cout << "Сортировка по диаметру:\n";
        for (int i = 0; i < count; ++i) {
            std::cout << Planets[i];
        }

        Planet::deletePlanetById(filename, 2, Planets, count);
        std::cout << "После удаления планеты с ID = 2:\n";
        for (int i = 0; i < count; ++i) {
            std::cout << Planets[i];
        }
        Planet::showDataBase(filename);

        Planet newPlanet{5, "Slipknot", 2000000, 200000, 200000};
        Planet::addPlanetToFile(filename, newPlanet);
        Planet::showDataBase(filename);

        delete[] Planets;
    } else if (mode[0] == 'i') {
        char continueExecution = 'y';
        const char* filename = "musicAlbums.txt";
        MusicAlbum* musicAlbums = nullptr;
        int count = 0;
        MusicAlbum newMusicAlbum{};
        MusicAlbum::readAlbumsFromFile(filename, &musicAlbums, count);

        while (continueExecution == 'y') {
            std::cout << "Выберите, что хотите сделать:\n";
            std::cout << "1 Прочитать БД\n";
            std::cout << "2 Добавить элемент в БД\n";
            std::cout << "3 Отсортировать БД (по минутамы)\n";
            std::cout << "4 Удалить элемент в БД по ID\n";
            std::cout << "5 Отредактировать элемент в БД по ID\n";
            std::cout << "6 Записать объекты в БД\n";
            int choice{};
            if (!(std::cin >> choice)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Ошибка: Введите число.\n";
                continue;
            }

            switch (choice) {
                case static_cast<int>(Options::ReadDB):
                    MusicAlbum::showDataBase(filename);
                    break;
                case static_cast<int>(Options::AddElement):
                    std::cout << "Введите название альбома, количество песен, количество минут и треков:\n";
                    std::cin >> newMusicAlbum;
                    MusicAlbum::addAlbumToFile(filename, newMusicAlbum, musicAlbums, count);
                    break;
                case static_cast<int>(Options::SortDB):
                    if (count > 0) {
                        std::cout << "Сортировка БД по количеству песен\n";
                        MusicAlbum::sortAlbumsByminutesCount(musicAlbums, 0, count - 1);
                        MusicAlbum::writeAlbumsToFile(filename, musicAlbums, count);
                    } else {
                        std::cout << "База данных пуста. Сортировка невозможна.\n";
                    }
                    break;
                case static_cast<int>(Options::DeleteElement): {
                    std::cout << "Введите ID для удаления:\n";
                    int id = 0;
                    std::cin >> id;
                    if (id >= 0 && id < count) {
                        MusicAlbum::deletemusicAlbumById(filename, id, musicAlbums, count);
                    } else {
                        std::cout << "Ошибка: Неверный ID.\n";
                    }
                    break;
                }
                case static_cast<int>(Options::EditElement): {
                    std::cout << "Введите ID объекта, которого хотите изменить, а потом название, количество песен, количество минут и количество треков:\n";
                    int id{};
                    char name[100];
                    int songs{};
                    int minutes{};
                    int tracks{};
                    std::cout << "Введите в формате: id name songs minutes tracks\n";
                    std::cin >> id >> name >> songs >> minutes >> tracks;
                    if (id >= 0 && id < count) {
                        MusicAlbum::editAlbumById(filename, id, name, songs, minutes, tracks, musicAlbums, count);
                        MusicAlbum::showDataBase(filename);
                    } else {
                        std::cout << "Ошибка: Неверный ID.\n";
                    }
                    break;
                }
                case static_cast<int>(Options::WriteDB):
                    MusicAlbum::writeAlbumsToFile(filename, musicAlbums, count);
                    std::cout << "Объекты записаны в файл\n";
                    break;
                default:
                    std::cout << "Неверный выбор. Попробуйте снова.\n";
                    break;
            }

            std::cout << "Продолжить выполнение? (y/n): ";
            std::cin >> continueExecution;
        }

        delete[] musicAlbums;
    }

    return 0;
}
