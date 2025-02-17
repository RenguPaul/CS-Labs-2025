#ifndef MUSICALBUM_HPP
#define MUSICALBUM_HPP

#include <iostream>
#include <cstring>

class MusicAlbum {
public:
    MusicAlbum();
    MusicAlbum(int _id, const char* _name, int _songsCount, int _minutesCount, int _tracksCount);
    MusicAlbum(const MusicAlbum& other);
    ~MusicAlbum();

    MusicAlbum& operator=(const MusicAlbum& other);

    int getId() const;
    const char* getName() const;
    int getSongsCount() const;
    int getMinutesCount() const;
    int getTracksCount() const;

    friend std::ostream& operator<<(std::ostream& os, const MusicAlbum& MusicAlbum);
    friend std::istream& operator>>(std::istream& is, MusicAlbum& MusicAlbum);

private:
    int id;
    char* name;
    int songsCount;
    int minutesCount;
    int tracksCount;
};

void readAlbumsFromFile(const char* filename, MusicAlbum** AlbumsArray, int& count);
void writeAlbumsToFile(const char* filename, MusicAlbum* AlbumsArray, int count);
void sortAlbumsById(MusicAlbum* AlbumsArray, int count);
void sortAlbumsByminutesCount(MusicAlbum* AlbumsArray, int count);
void sortAlbumsBysongsCount(MusicAlbum* AlbumsArray, int count);
void sortAlbumsBytracksCount(MusicAlbum* AlbumsArray, int count);
void deletemusicAlbumById(const char* filename, int id, MusicAlbum* AlbumsArray, int& count);
void showDataBase(const char* filename);

#endif // MUSICALBUM_HPP
