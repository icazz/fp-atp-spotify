#include<iostream>
#include<fstream>
#include<string>
#include "spotify.h"

// FUNGSI UNTUK MENU PLAYLIST
void spotify::printPlaylist(spotify::Playlist *playlist) {
    if (playlist ==nullptr) {
        std::cout << "No playlists available.\n";
        return;
    }
    std::cout << "Playlists:\n";
    int count = 1;
    while (playlist) {
        std::cout << count++ << ". " << playlist->name << std::endl;
        playlist = playlist->next;
    }
}

void spotify::addPlaylist(spotify::Playlist *&playlist) {
    spotify::Playlist *newPlaylist = new spotify::Playlist;
    std::cout << "Enter playlist name: ";
    std::cin.ignore();
    getline(std::cin, newPlaylist->name);
    newPlaylist->head = nullptr;
    newPlaylist->next = nullptr;

    if (!playlist) {
        playlist = newPlaylist;
    } else {
        spotify::Playlist *temp = playlist;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newPlaylist;
    }

    std::cout << "Playlist '" << newPlaylist->name << "' added successfully!\n";
}

void spotify::deletePlaylist(spotify::Playlist *&head) {
    if (!head) {
        std::cout << "No playlists available.\n";
        return;
    }

    std::string playlistName;
    std::cout << "Enter the name of the playlist to delete: ";
    std::cin.ignore();
    std::getline(std::cin, playlistName);

    spotify::Playlist *current = head;
    spotify::Playlist *previous = nullptr;

    // Cari playlist dengan nama yang sesuai
    while (current) {
        if (current->name == playlistName) {
            if (!previous) {
                // Jika playlist yang dihapus adalah head
                head = current->next;
            } else {
                // Jika playlist di tengah atau di akhir
                previous->next = current->next;
            }

            delete current;
            std::cout << "Playlist '" << playlistName << "' deleted successfully.\n";
            return;
        }
        previous = current;
        current = current->next;
    }

    std::cout << "Playlist not found.\n";
}


void spotify::selectPlaylist(spotify::Playlist *head, spotify::Playlist *&selectedPlaylist) {
    if (!head) {
        std::cout << "No playlists available.\n";
        selectedPlaylist = nullptr;
        return;
    }

    std::string playlistName;
    std::cout << "Enter the name of the playlist to select: ";
    std::cin.ignore();
    std::getline(std::cin, playlistName);

    spotify::Playlist *current = head;
    while (current) {
        if (current->name == playlistName) {
            selectedPlaylist = current;
            std::cout << "Playlist '" << playlistName << "' selected.\n";
            return;
        }
        current = current->next;
    }

    std::cout << "Playlist not found.\n";
    selectedPlaylist = nullptr;
}

// FUNGSI UNTUK MENU DETAIL PLAYLIST

void listPlaylistSongs(Playlist* playlist, int sortOption){
    // isi sini
    // jangan lupa cek .h udah kutambahin prototype, nah kek gitu kalo mau buat fungsi baru
    // kalo program ga jalan wajar aja, soalnya menu ini nyambung sama menu playlist, belum ku benerin errornya hehe
}

