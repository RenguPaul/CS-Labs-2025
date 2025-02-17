#include "musicAlbum.hpp"
#include <iostream>
#include <cstring>
#include <fstream>
#include <algorithm>

MusicAlbum::MusicAlbum() : id(-1), name(nullptr), songsCount(0), minutesCount(0), tracksCount(0) {
    //std::cout << "Создание альбома по умолчанию" << std::endl;
}

MusicAlbum::MusicAlbum(int _id, const char* _name, int _songsCount, int _minutesCount, int _tracksCount)
    : id(_id), songsCount(_songsCount), minutesCount(_minutesCount), tracksCount(_tracksCount) {
    //std::cout << "Создание альбома " << _name << "С ID: " << _id << std::endl;
    name = new char[strlen(_name) + 1];
    strcpy(name, _name);
}

MusicAlbum::MusicAlbum(const MusicAlbum& other) {
    //std::cout << "Создание копии альбома " << other.name << "С ID: " << other.id << std::endl;
    id = other.id;
    songsCount = other.songsCount;
    minutesCount = other.minutesCount;
    tracksCount = other.tracksCount;
    name = new char[strlen(other.name) + 1];
    strcpy(name, other.name);
}

MusicAlbum& MusicAlbum::operator=(const MusicAlbum& other) {
    if (this != &other) {
        delete[] name;

        id = other.id;
        songsCount = other.songsCount;
        minutesCount = other.minutesCount;
        tracksCount = other.tracksCount;
        name = new char[strlen(other.name) + 1];
        strcpy(name, other.name);
    }
    return *this;
}

MusicAlbum::~MusicAlbum() {
    //std::cout << "Альбом " << this->name << ' ' << "С ID: " << this->id << "удален" << std::endl;
    delete[] name;
}

int MusicAlbum::getId() const { return id; }
const char* MusicAlbum::getName() const { return name; }
int MusicAlbum::getSongsCount() const { return songsCount; }
int MusicAlbum::getMinutesCount() const { return minutesCount; }
int MusicAlbum::getTracksCount() const { return tracksCount; }

std::ostream& operator<<(std::ostream& os, const MusicAlbum& musicAlbum) {
    os << musicAlbum.id << ' '
       << musicAlbum.name << ' '
       << musicAlbum.songsCount << ' '
       << musicAlbum.minutesCount << ' '
       << musicAlbum.tracksCount << '\n';
    return os;
}

std::istream& operator>>(std::istream& is, MusicAlbum& musicAlbum) {
    if (musicAlbum.name != nullptr) {
        delete[] musicAlbum.name;
        musicAlbum.name = nullptr;
    }

    is >> musicAlbum.id;
    if (is.fail()) {
        return is;
    }

    char buffer[100];
    is >> buffer;
    size_t len = strlen(buffer);
    musicAlbum.name = new char[len + 1];
    strcpy(musicAlbum.name, buffer);

    is >> musicAlbum.songsCount;
    if (is.fail()) {
        return is;
    }

    is >> musicAlbum.minutesCount;
    if (is.fail()) {
        return is;
    }

    is >> musicAlbum.tracksCount;
    if (is.fail()) {
        return is;
    }

    return is;
}

void readAlbumsFromFile(const char* filename, MusicAlbum** AlbumsArray, int& count) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Ошибка открытия файла." << std::endl;
        return;
    }

    MusicAlbum musicAlbum;
    while (infile >> musicAlbum) {
        // Создаем новый массив большего размера
        MusicAlbum* tmp = new MusicAlbum[count + 1];

        // Копируем старые элементы
        for (int i = 0; i < count; ++i) {
            tmp[i] = (*AlbumsArray)[i];
        }

        // Освобождаем память старого массива
        delete[] *AlbumsArray;

        // Присваиваем новый массив
        *AlbumsArray = tmp;

        // Добавляем новый элемент
        (*AlbumsArray)[count] = musicAlbum;
        count++;
    }

    infile.close();
}

void writeAlbumsToFile(const char* filename, MusicAlbum* AlbumsArray, int count) {
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "Ошибка открытия файла." << std::endl;
        return;
    }

    for (int i = 0; i < count; ++i) {
        outfile << AlbumsArray[i];
    }

    outfile.close();
}

void sortAlbumsById(MusicAlbum* AlbumsArray, int count) {
    std::sort(AlbumsArray, AlbumsArray + count, [](const MusicAlbum& a, const MusicAlbum& b) {
        return a.getId() < b.getId();
    });
}

void sortAlbumsByminutesCount(MusicAlbum* AlbumsArray, int count) {
    std::sort(AlbumsArray, AlbumsArray + count, [](const MusicAlbum& a, const MusicAlbum& b) {
        return a.getMinutesCount() < b.getMinutesCount();
    });
}

void sortAlbumsBysongsCount(MusicAlbum* AlbumsArray, int count) {
    std::sort(AlbumsArray, AlbumsArray + count, [](const MusicAlbum& a, const MusicAlbum& b) {
        return a.getSongsCount() < b.getSongsCount();
    });
}

void sortAlbumsBytracksCount(MusicAlbum* AlbumsArray, int count) {
    std::sort(AlbumsArray, AlbumsArray + count, [](const MusicAlbum& a, const MusicAlbum& b) {
        return a.getTracksCount() < b.getTracksCount();
    });
}

void deletemusicAlbumById(const char* filename, int id, MusicAlbum* AlbumsArray, int& count) {
    // Ищем альбомову с указанным ID
    int index = -1;
    for (int i = 0; i < count; ++i) {
        if (AlbumsArray[i].getId() == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        std::cerr << "Альбом с ID " << id << " не найден." << std::endl;
        return;
    }

    // Сдвигаем элементы массива
    for (int i = index; i < count - 1; ++i) {
        AlbumsArray[i] = AlbumsArray[i + 1];
    }

    // Уменьшаем количество альбомов
    count--;

    // Перезаписываем файл
    writeAlbumsToFile(filename, AlbumsArray, count);
}

void showDataBase(const char* filename) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Ошибка открытия файла." << std::endl;
        return;
    }
    std::cout << "Вывод БД" << std::endl;
    MusicAlbum musicAlbum;
    while (infile >> musicAlbum) {
        std::cout << musicAlbum;
    }

    infile.close();
}
