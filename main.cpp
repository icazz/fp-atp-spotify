#include <iostream>
#include <fstream>
#include <locale>
#include <string>
#include "spotify.h"

enum State { MAIN = 1, SONG, PLAYLIST, DETAIL_PLAYLIST};
enum MainMenu { MENU_SONG = 1, MENU_PLAYLIST, MENU_EXIT };
enum SongMenu { SONG_BACK = 0, SONG_LIST, SONG_ADD, SONG_DELETE };
enum PlaylistMenu { PLAYLIST_BACK = 0, PLAYLIST_LIST, PLAYLIST_ADD, PLAYLIST_DELETE, PLAYLIST_SELECT };
enum PlaylistDetailMenu { PLAYLIST_DETAIL_BACK = 0, PLAYLIST_DETAIL_LIST, PLAYLIST_DETAIL_ADD, PLAYLIST_DETAIL_DELETE };

// Function prototypes
void mainMenu(State &state);
void songMenu(State &state, spotify::Song *&song);
void playlistMenu(State &state, spotify::Playlist *&playlist, spotify::Playlist *selectedPlaylist);
void playlistDetailMenu(State &state, spotify::Playlist *&selectedPlaylist);

int main() {
    spotify::Playlist *playlist = nullptr;
    spotify::Playlist *selectedPlaylist = nullptr;
    spotify::Song *song = nullptr;
    bool end = false;
    State state = MAIN;

    while (true) {
        switch (state) {
        case MAIN:
            mainMenu(state);
            break;
        case SONG:
            songMenu(state, song);
            break;
        case PLAYLIST:
            playlistMenu(state, playlist, selectedPlaylist);
            break;
        case DETAIL_PLAYLIST:
            playlistDetailMenu(state, selectedPlaylist);
            break;
        }
        if (end) break;
    }

    return 0;
}

void mainMenu(State &state) {
    int choice;

    std::cout << "1. Song\n";
    std::cout << "2. Playlist\n";
    std::cout << "3. Exit\n";
    std::cout << "Choice: ";
    std::cin >> choice;

    switch (choice) {
    case MENU_SONG:
        state = SONG;
        break;
    case MENU_PLAYLIST:
        state = PLAYLIST;
        break;
    case MENU_EXIT:
        std::exit(0);
    }
}

void songMenu(State &state, spotify::Song *&song) {
    int choice;

    std::cout << "0. Back\n";
    std::cout << "1. List songs\n";
    std::cout << "2. Add song\n";
    std::cout << "3. Delete song\n";
    std::cout << "Choice: ";
    std::cin >> choice;

    switch (choice) {
    case SONG_LIST:
        // spotify::printSongs(song);
        break;
    case SONG_ADD:
        // spotify::addSong(song);
        break;
    case SONG_DELETE:
        // spotify::deleteSong(song);
        break;
    case SONG_BACK:
        state = MAIN;
        break;
    }
}

void playlistMenu(State &state, spotify::Playlist *&playlist, spotify::Playlist *selectedPlaylist) {
    int choice;

    std::cout << "0. Back\n";
    std::cout << "1. List playlists\n";
    std::cout << "2. Add playlist\n";
    std::cout << "3. Delete playlist\n";
    std::cout << "4. Select playlist\n";
    std::cout << "Choice: ";
    std::cin >> choice;

    switch (choice) {
    case PLAYLIST_LIST:
        spotify::printPlaylist(playlist);
        break;
    case PLAYLIST_ADD:
        spotify::addPlaylist(playlist);
        break;
    case PLAYLIST_DELETE:
        spotify::deletePlaylist(playlist);
        break;
    case PLAYLIST_SELECT:
        //select playlist masih error, nanti kubenerin
        spotify::selectPlaylist(playlist, selectedPlaylist);
        if (!selectedPlaylist) break;
        state = DETAIL_PLAYLIST;
        break;
    case PLAYLIST_BACK:
        state = MAIN;
        break;
    }
}

void playlistDetailMenu(State &state, spotify::Playlist *&selectedPlaylist) {

    int choice;
    std::cout << "Playlist: " << selectedPlaylist -> name << std::endl;
    std::cout << "0. Back\n";
    std::cout << "1. List songs\n";
    std::cout << "2. Add song\n";
    std::cout << "3. Delete song\n";
    std::cout << "Choice: ";
    std::cin >> choice;

    switch (choice) {
    case PLAYLIST_DETAIL_LIST:
        int sortChoice;
        std::cout << "Sort songs:\n";
        std::cout << "0. Default\n";
        std::cout << "1. By artist\n";
        std::cout << "2. By title\n";
        std::cout << "Choice: ";
        std::cin >> sortChoice;

        //spotify::listPlaylistSongs(selectedPlaylist, sortChoice);
        break;
    case PLAYLIST_DETAIL_ADD:
        // spotify::addSongToPlaylist(selectedPlaylist);
        break;
    case PLAYLIST_DETAIL_DELETE:
        // spotify::deleteSongFromPlaylist(selectedPlaylist);
        break;
    case PLAYLIST_DETAIL_BACK:
        state = PLAYLIST;
        break;
    default:
        std::cout << "Invalid choice.\n";
        break;
    }
}
