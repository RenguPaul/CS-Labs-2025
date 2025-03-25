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

    bool operator>(const MusicAlbum& album) const {
        return this->getMinutesCount() > album.getMinutesCount();
    }
    bool operator<(const MusicAlbum& album) const {
        return !(this->getMinutesCount() > album.getMinutesCount());
    }
    bool operator==(const MusicAlbum& album) const {
        return this->getMinutesCount() == album.getMinutesCount();
    }
    bool operator!=(const MusicAlbum& album) const {
        return !(this->getMinutesCount() == album.getMinutesCount());
    }

    friend std::ostream& operator<<(std::ostream& os, const MusicAlbum& MusicAlbum);
    friend std::istream& operator>>(std::istream& is, MusicAlbum& MusicAlbum);

    static void readAlbumsFromFile(const char* filename, MusicAlbum** AlbumsArray, int& count);
    static void writeAlbumsToFile(const char* filename, MusicAlbum* AlbumsArray, int count);
    static void sortAlbumsByminutesCount(MusicAlbum *&AlbumsArray, int left, int right);
    /*static void sortAlbumsBysongsCount(MusicAlbum *&AlbumsArray, int left, int right);
    static void sortAlbumsBytracksCount(MusicAlbum *&AlbumsArray, int left, int right);*/
    static void deletemusicAlbumById(const char* filename, int id, MusicAlbum* AlbumsArray, int& count);
    static void showDataBase(const char* filename);
    static void addAlbumToFile(const char *filename, MusicAlbum &newAlbum, MusicAlbum* albumsArray, int& count);
    static void editAlbumById(const char *filename, int id, const char *newName, int newSongsCount, int newMinutesCount, int newTracksCount, MusicAlbum *AlbumsArray, int count);


private:
    int id;
    char* name;
    int songsCount;
    int minutesCount;
    int tracksCount;
};

#endif // MUSICALBUM_HPP
