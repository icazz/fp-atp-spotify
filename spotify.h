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
    void showText(Playlist *&text, std::string fileName);
    void printSongs(Song *song);
    void addSong(Song *&head);
    void deleteSong(Song *&head);
    void printPlaylist(Playlist *playlist);
    void addPlaylist(Playlist *&playlist);
    void deletePlaylist(Playlist *&playlist);
    void selectPlaylist(Playlist *playlist, Playlist *&selectedPlaylist, bool &success);
    void listPlaylistSongs(Playlist* playlist, int sortOption);
    void addSongToPlaylist(Playlist *&playlist, Playlist *selectedPlaylist);
    void deleteSongFromPlaylist(Playlist *&playlist, Playlist* selectedPlaylist);
    //void showText(Playlist *&playlist, string fileName);

    //jangan lupa prototypenya, semangat gusy
    
}

#endif
