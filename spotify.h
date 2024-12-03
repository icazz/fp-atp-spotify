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

    void printPlaylist(Playlist *playlist);
    void addPlaylist(Playlist *&playlist);
    void deletePlaylist(Playlist *&playlist);
    void selectPlaylist(spotify::Playlist *playlist, spotify::Playlist *&selectedPlaylist);
    //jangan lupa prototypenya, semangat gusy
    
}

#endif
