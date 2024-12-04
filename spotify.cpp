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

//Fungsi untuk menambahkan lagu
void addSong(Playlist* playlist) {
    if (!playlist) {
        std::cout << "No playlist selected. Please select a playlist first.\n";
        return;
    }

    Song* newSong = new Song;
    std::cout << "Enter song title: ";
    std::cin.ignore();
    std::getline(std::cin, newSong->title);
    std::cout << "Enter song artist: ";
    std::getline(std::cin, newSong->artist);
    newSong->next = nullptr; // Inisialisasi pointer ke lagu berikutnya

    // Jika playlist kosong
    if (!playlist->head) {
        playlist->head = newSong; // Head menunjuk ke lagu pertama
    } else {
        // Cari lagu terakhir di linked list
        Song* temp = playlist->head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newSong; // Tambahkan lagu baru di akhir list
    }

    std::cout << "Song added successfully to playlist '" << playlist->name << "'.\n";
}

//fungsi untuk menghapus lagu
void deleteSong(Playlist* playlist) {
    if (!playlist || !playlist->head) {
        std::cout << "No songs available in the playlist.\n";
        return;
    }

    std::string songTitle;
    std::cout << "Enter the title of the song to delete: ";
    std::cin.ignore();
    std::getline(std::cin, songTitle);

    Song* current = playlist->head;
    Song* previous = nullptr;

    // Cari lagu berdasarkan judul
    while (current) {
        if (current->title == songTitle) {
            if (!previous) {
                // Jika lagu yang dihapus adalah head
                playlist->head = current->next;
            } else {
                // Jika lagu ada di tengah atau di akhir
                previous->next = current->next;
            }
            delete current;
            std::cout << "Song '" << songTitle << "' deleted successfully.\n";
            return;
        }
        previous = current;
        current = current->next;
    }

    std::cout << "Song not found in the playlist.\n";
}

// FUNGSI UNTUK MENU DETAIL PLAYLIST
void menuDetailPlaylist(Playlist* playlist) {
    if (!playlist) {
        std::cout << "Playlist is not valid.\n";
        return;
    }

    int choice;

    do {
        std::cout << "\n--- Playlist: " << playlist->name << " ---\n";
        std::cout << "1. List Songs\n";
        std::cout << "2. Add Song\n";
        std::cout << "3. Delete Song\n";
        std::cout << "4. Back to Playlist Menu\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: { // List Songs with Sorting Options
                int sortOption;
                do {
                    std::cout << "\n--- List Songs Menu ---\n";
                    std::cout << "1. Default\n";
                    std::cout << "2. Title\n";
                    std::cout << "3. Artist\n";
                    std::cout << "4. Back to Playlist Menu\n";
                    std::cout << "Enter your sorting choice: ";
                    std::cin >> sortOption;

                    switch (sortOption) {
                        case 1:
                            playlist->listSongs(SortOption::DEFAULT); // Menampilkan lagu secara default
                            break;
                        case 2:
                            playlist->listSongs(SortOption::TITLE); // Menampilkan lagu diurutkan berdasarkan judul
                            break;
                        case 3:
                            playlist->listSongs(SortOption::ARTIST); // Menampilkan lagu diurutkan berdasarkan artis
                            break;
                        case 4:
                            std::cout << "Returning to Playlist Detail Menu...\n";
                            break;
                        default:
                            std::cout << "Invalid choice. Try again.\n";
                    }
                } while (sortOption != 4);
                break;
            }

            case 2: { // Add Song to Playlist
                std::string songTitle, songArtist;
                std::cout << "Enter song title: ";
                std::cin.ignore(); 
                std::cout << "Enter artist name: ";
                std::getline(std::cin, songArtist);

                playlist->addSong(Song(songTitle, songArtist)); // Menambahkan lagu ke playlist
                std::cout << "Song added to playlist!\n";
                break;
            }

            case 3: { // Delete Song from Playlist
                std::string songTitle;
                std::cout << "Enter the title of the song to delete: ";
                std::cin.ignore(); 
                std::getline(std::cin, songTitle);

                if (playlist->deleteSong(songTitle)) {
                    std::cout << "Song deleted from playlist.\n";
                } else {
                    std::cout << "Song not found in playlist.\n";
                }
                break;
            }

            case 4:
                std::cout << "Returning to Playlist Menu...\n";
                break;

            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);
}

void listPlaylistSongs(Playlist* playlist, int sortOption){
    if (!playlist || !playlist->head) {
        std::cout << "No songs available in the playlist.\n";
        return;
    }

    Song* currentSong = playlist->head;
    Song* index = nullptr;
    Song temp;

    // Sorting berdasarkan pilihan 
    switch (sortOption) {
        case 1: // Sort by artis
            for (currentSong = playlist->head; currentSong != nullptr; currentSong = currentSong->next) {
                for (index = currentSong->next; index != nullptr; index = index->next) {
                    if (currentSong->artist > index->artist) {
                        // Tukar posisi lagu berdasarkan artist
                        temp = *currentSong;
                        *currentSong = *index;
                        *index = temp;
                    }
                }
            }
            std::cout << "Songs sorted by artist.\n";
            break;

        case 2: // Sort by judul
            for (currentSong = playlist->head; currentSong != nullptr; currentSong = currentSong->next) {
                for (index = currentSong->next; index != nullptr; index = index->next) {
                    if (currentSong->title > index->title) {
                        // Tukar posisi lagu berdasarkan judul
                        temp = *currentSong;
                        *currentSong = *index;
                        *index = temp;
                    }
                }
            }
            std::cout << "Songs sorted by title.\n";
            break;

        default: // Default sorting
            std::cout << "Invalid sorting option. Showing default order.\n";
            break;
    }

    // Menampilkan lagu setelah sorting
    std::cout << "Songs in playlist '" << playlist->name << "':\n";
    for (Song* song = playlist->head; song != nullptr; song = song->next) {
        std::cout << "Title: " << song->title << ", Artist: " << song->artist << "\n";
    }
    // isi sini
    // jangan lupa cek .h udah kutambahin prototype, nah kek gitu kalo mau buat fungsi baru
    // kalo program ga jalan wajar aja, soalnya menu ini nyambung sama menu playlist, belum ku benerin errornya hehe
}

