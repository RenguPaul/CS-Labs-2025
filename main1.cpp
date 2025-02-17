#include "musicAlbum/musicAlbum.hpp"
#include <iostream>

int main() {
    const char* filename = "MusicAlbums.txt";
    MusicAlbum* MusicAlbums = nullptr;
    int count = 0;

    showDataBase(filename);

    readAlbumsFromFile(filename, &MusicAlbums, count);

    sortAlbumsById(MusicAlbums, count);
    std::cout << "Сортировка по ID:\n";
    for (int i = 0; i < count; ++i) {
        std::cout << MusicAlbums[i];
    }

    deletemusicAlbumById(filename, 2, MusicAlbums, count);
    std::cout << "После удаления альбома с ID = 2:\n";
    for (int i = 0; i < count; ++i) {
        std::cout << MusicAlbums[i];
    }
    showDataBase(filename);

    delete[] MusicAlbums;

    return 0;
}
