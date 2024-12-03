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
    void listPlaylistSongs(Playlist* playlist, int sortOption);
    
}

#endif


// // Function prototypes for songs
// void addSong(Song *&song);
// void printSongs(Song *song);
// void deleteSong(Song *&song);

// // Function prototypes for playlists

// void deletePlaylist(Playlist *&playlist);
// void selectPlaylist(Playlist *playlist, Playlist *&selectedPlaylist);

// // Function prototypes for playlist details
// void listPlaylistSongs(Playlist *selectedPlaylist);
// void addSongToPlaylist(Playlist *selectedPlaylist, Song *allSongs);
// void deleteSongFromPlaylist(Playlist *selectedPlaylist);