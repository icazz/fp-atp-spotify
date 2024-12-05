#ifndef SPOTIFY_H
#define SPOTIFY_H

#include <string>

namespace spotify {
    struct Song {
        std::string title; 
        std::string artist;
        Song* next = nullptr;
    };

    struct Playlist {
        std::string name;
        Song* head = nullptr;
        Playlist* next = nullptr;
    };
    void printSongs(Song *song);
    void addSong(Song *&head);
    void deleteSong(Song *&head);
    void printPlaylist(Playlist *playlist);
    void addPlaylist(Playlist *&playlist);
    void deletePlaylist(Playlist *&playlist);
    void selectPlaylist(Playlist *playlist, Playlist **selectedPlaylist, bool &success);
    void showText(Playlist *&playlist, std::string fileName);
    // void listPlaylistSongs(Playlist* playlist, int sortOption);
    void addSong(Playlist *playlist);
    // void deleteSong(Playlist* playlist);


    //jangan lupa prototypenya, semangat gusy
    
}

#endif
