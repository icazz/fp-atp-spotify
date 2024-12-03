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
<<<<<<< HEAD
    void listPlaylistSongs(Playlist* playlist, int sortOption);
=======
    //jangan lupa prototypenya, semangat gusy
>>>>>>> e6ebb0ef157625f4179f63c16ef3519b500a1b02
    
}

#endif
