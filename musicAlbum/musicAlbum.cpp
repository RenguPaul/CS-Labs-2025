#include "musicAlbum.hpp"
#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>

MusicAlbum::MusicAlbum()
    : id(-1), name(nullptr), songsCount(0), minutesCount(0), tracksCount(0) {
  // std::cout << "Создание альбома по умолчанию" << std::endl;
}

MusicAlbum::MusicAlbum(int _id, const char *_name, int _songsCount,
                       int _minutesCount, int _tracksCount)
    : id(_id), songsCount(_songsCount), minutesCount(_minutesCount),
      tracksCount(_tracksCount) {
  // std::cout << "Создание альбома " << _name << "С ID: " << _id << std::endl;
  name = new char[strlen(_name) + 1];
  strcpy(name, _name);
}

MusicAlbum::MusicAlbum(const MusicAlbum &other) {
  // std::cout << "Создание копии альбома " << other.name << "С ID: " <<
  // other.id << std::endl;
  id = other.id + 1;
  songsCount = other.songsCount;
  minutesCount = other.minutesCount;
  tracksCount = other.tracksCount;
  name = new char[strlen(other.name) + 1];
  strcpy(name, other.name);
}

MusicAlbum &MusicAlbum::operator=(const MusicAlbum &other) {
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
  // std::cout << "Альбом " << this->name << ' ' << "С ID: " << this->id <<
  // "удален" << std::endl;
  delete[] name;
}

int MusicAlbum::getId() const { return id; }
const char *MusicAlbum::getName() const { return name; }
int MusicAlbum::getSongsCount() const { return songsCount; }
int MusicAlbum::getMinutesCount() const { return minutesCount; }
int MusicAlbum::getTracksCount() const { return tracksCount; }

std::ostream &operator<<(std::ostream &os, const MusicAlbum &musicAlbum) {
  os << musicAlbum.id << ' ' << musicAlbum.name << ' ' << musicAlbum.songsCount
     << ' ' << musicAlbum.minutesCount << ' ' << musicAlbum.tracksCount << '\n';
  return os;
}

std::istream &operator>>(std::istream &is, MusicAlbum &musicAlbum) {
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

void MusicAlbum::readAlbumsFromFile(const char *filename,
                                    MusicAlbum **AlbumsArray, int &count) {
  std::ifstream infile(filename);
  if (!infile.is_open()) {
    std::cerr << "Ошибка открытия файла." << std::endl;
    return;
  }

  MusicAlbum musicAlbum;
  while (infile >> musicAlbum) {
    // Создаем новый массив большего размера
    MusicAlbum *tmp = new MusicAlbum[count + 1];

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

void MusicAlbum::writeAlbumsToFile(const char *filename,
                                   MusicAlbum *AlbumsArray, int count) {
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

void MusicAlbum::sortAlbumsByminutesCount(MusicAlbum *&AlbumsArray, int left, int right) {
    if (left > right) {
      return;
    }
    double middle = AlbumsArray[(left + right) / 2].getMinutesCount();
    int i = left;
    int j = right;
    while (i <= j) {
      while (AlbumsArray[i].getMinutesCount() < middle) {
        ++i;
      }
      while (AlbumsArray[j].getMinutesCount() > middle) {
        --j;
      }
      if (i <= j) {
        if (AlbumsArray[i].getMinutesCount() != AlbumsArray[j].getMinutesCount()) {
          MusicAlbum temp(AlbumsArray[i]);
          AlbumsArray[i] = AlbumsArray[j];
          AlbumsArray[j] = temp;
        }
        ++i;
        --j;
      }
    }
    sortAlbumsByminutesCount(AlbumsArray, left, j);
    sortAlbumsByminutesCount(AlbumsArray, i, right);
  }

void MusicAlbum::sortAlbumsBysongsCount(MusicAlbum *&AlbumsArray, int left, int right) {
    if (left > right) {
        return;
      }
      double middle = AlbumsArray[(left + right) / 2].getSongsCount();
      int i = left;
      int j = right;
      while (i <= j) {
        while (AlbumsArray[i].getSongsCount() < middle) {
          ++i;
        }
        while (AlbumsArray[j].getSongsCount() > middle) {
          --j;
        }
        if (i <= j) {
          if (AlbumsArray[i].getSongsCount() != AlbumsArray[j].getSongsCount()) {
            MusicAlbum temp(AlbumsArray[i]);
            AlbumsArray[i] = AlbumsArray[j];
            AlbumsArray[j] = temp;
          }
          ++i;
          --j;
        }
      }
      sortAlbumsBysongsCount(AlbumsArray, left, j);
      sortAlbumsBysongsCount(AlbumsArray, i, right);
}

void MusicAlbum::sortAlbumsBytracksCount(MusicAlbum *&AlbumsArray, int left, int right) {
    if (left > right) {
        return;
      }
      double middle = AlbumsArray[(left + right) / 2].getTracksCount();
      int i = left;
      int j = right;
      while (i <= j) {
        while (AlbumsArray[i].getTracksCount() < middle) {
          ++i;
        }
        while (AlbumsArray[j].getTracksCount() > middle) {
          --j;
        }
        if (i <= j) {
          if (AlbumsArray[i].getTracksCount() != AlbumsArray[j].getTracksCount()) {
            MusicAlbum temp(AlbumsArray[i]);
            AlbumsArray[i] = AlbumsArray[j];
            AlbumsArray[j] = temp;
          }
          ++i;
          --j;
        }
      }
      sortAlbumsBytracksCount(AlbumsArray, left, j);
      sortAlbumsBytracksCount(AlbumsArray, i, right);
}

void MusicAlbum::deletemusicAlbumById(const char *filename, int id,
                                      MusicAlbum *AlbumsArray, int &count) {
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

  for (int i = index; i < count - 1; ++i) {
    AlbumsArray[i] = AlbumsArray[i + 1];
  }

  count--;

  writeAlbumsToFile(filename, AlbumsArray, count);
}

void MusicAlbum::addAlbumToFile(const char *filename, MusicAlbum &newAlbum) {
  MusicAlbum *albumsArray = nullptr;
  int count = 0;
  readAlbumsFromFile(filename, &albumsArray, count);

  int maxId = -1;
  for (int i = 0; i < count; ++i) {
      if (albumsArray[i].getId() > maxId) {
          maxId = albumsArray[i].getId();
      }
  }

  newAlbum = MusicAlbum(maxId + 1, newAlbum.getName(), newAlbum.getSongsCount(),
                        newAlbum.getMinutesCount(), newAlbum.getTracksCount());

  MusicAlbum *newAlbumsArray = new MusicAlbum[count + 1];
  for (int i = 0; i < count; ++i) {
      newAlbumsArray[i] = albumsArray[i];
  }
  newAlbumsArray[count] = newAlbum;

  delete[] albumsArray;

  writeAlbumsToFile(filename, newAlbumsArray, count + 1);

  delete[] newAlbumsArray;
}

void MusicAlbum::showDataBase(const char *filename) {
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

void MusicAlbum::editAlbumById(const char *filename, int id, const char *newName, int newSongsCount, int newMinutesCount, int newTracksCount, MusicAlbum *AlbumsArray, int count) {
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

  if (newName != nullptr) {
      delete[] AlbumsArray[index].name;
      AlbumsArray[index].name = new char[strlen(newName) + 1];
      strcpy(AlbumsArray[index].name, newName);
  }
  AlbumsArray[index].songsCount = newSongsCount;
  AlbumsArray[index].minutesCount = newMinutesCount;
  AlbumsArray[index].tracksCount = newTracksCount;

  writeAlbumsToFile(filename, AlbumsArray, count);
}
