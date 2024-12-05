#include<iostream>
#include<fstream>
#include<string>
#include "spotify.h"
#include <limits>

//Ni'mah - FUNGSI UNTUK SONGMENU
void spotify::printSongs(spotify::Song *song){
    if(song == nullptr){
        std::cout<<"No songs available.\n";
        return;
    }

    std::cout<<"Songs:\n";
    int count = 1;
    while(song){
        std::cout<< count++ << ". Title: " << song->title << ", Artist: " << song->artist << "\n";
        song = song->next;
    }
}

void spotify::addSong(spotify::Song *&head){
    spotify::Song *newSong = new spotify::Song;
    std::cout<< "Enter song title: ";
    std::cin.ignore();
    std::getline(std::cin, newSong->title);

    std::cout<<"Enter song artist: ";
    std::getline(std::cin, newSong->artist);

    newSong->next = nullptr;

    if(!head){
        head = newSong;
    } else {
        spotify::Song *temp = head;
        while(temp->next){
            temp = temp->next;
        }
        temp->next = newSong;
    }
    std::cout<<"Song '" << newSong->title << "' by '" << newSong ->artist << "' added successfully.\n";
}

void spotify::deleteSong(spotify::Song *&head){
    if(!head){
        std::cout << "No songs available to delete.\n";
        return;
    }

    std::string songTitle;
    std::cout<<"Enter the title of the song to delete: ";
    std::cin.ignore();
    std::getline(std::cin, songTitle);

    spotify::Song *current = head;
    spotify::Song *previous = nullptr;

    while(current){
        if(current->title == songTitle){
            if(!previous){
                head = current->next;
            } else {
                previous->next = current ->next;
            }

            delete current;

            std::cout<<"Song '" << songTitle << "' deleted successfully.\n";
            return;
        }

        previous = current;
        current = current->next;
    }
    std::cout<<"Song not found.\n";
}

// FUNGSI UNTUK MENU PLAYLIST
void spotify::printPlaylist(spotify::Playlist *playlist) {
    if (playlist ==nullptr) {
        std::cout << "No playlists available.\n";
        return;
    }
    
    spotify::Playlist *temp = playlist;
    std::cout << "Playlists:\n";
    int count = 1;

    while (temp) {
        std::cout << count++ << ". " << temp->name << std::endl;
        temp = temp->next;
    }
    
    showText(playlist, "PlaylistAku.txt");

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

    showText(playlist, "PlaylistAku.txt");

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

            showText(head, "PlaylistAku.txt");
        
            std::cout << "Playlist '" << playlistName << "' deleted successfully.\n";
            return;
        }
        previous = current;
        current = current->next;

    }

    std::cout << "Playlist not found.\n";
}

void spotify::selectPlaylist(spotify::Playlist *head, spotify::Playlist *&selectedPlaylist, bool &success) {
    if (!head) {
        std::cout << "No playlists available.\n";
        selectedPlaylist = nullptr; // Perbarui pointer di luar fungsi
        success = false;
        return;
    }

    std::string playlistName;
    std::cout << "Enter the name of the playlist to select: ";
    std::cin.ignore();
    std::getline(std::cin, playlistName);

    spotify::Playlist *current = head;
    while (current) {
        if (current->name == playlistName) {
            selectedPlaylist = current; // Perbarui pointer
            success = true;
            std::cout << "Playlist '" << playlistName << "' selected.\n";
            return;
        }
        current = current->next;
    }

    std::cout << "Playlist not found.\n";
    selectedPlaylist = nullptr; // Set pointer ke nullptr jika tidak ditemukan
    success = false;
}

void spotify::showText(spotify::Playlist *&text, std::string fileName){
    spotify::Playlist *show_text = text;
    std::ofstream outFile(fileName, std::ios::out);
            int counter = 1;
            while (show_text) {
                outFile.close(); // Close the file before reopening in overwrite mode
                outFile.open(fileName, std::ios::app); // Reopen the file in overwrite mode
                outFile << counter << ". " << show_text->name << std::endl;
                counter++;
                show_text = show_text->next;
            }
}


// // FUNGSI UNTUK MENU DETAIL PLAYLIST
void spotify::listPlaylistSongs(Playlist* playlist, int sortOption) {
    // Periksa apakah playlist valid dan memiliki lagu
    if (!playlist || !playlist->head) {
        std::cout << "Playlist " << playlist->name << " is empty or does not exist.\n";
        return;
    }

    // Sorting menggunakan bubble sort sederhana pada linked list
    bool swapped;
    do {
        swapped = false;
        spotify::Song* current = playlist->head;
        spotify::Song* prev = nullptr;

        while (current && current->next) {
            spotify::Song* next = current->next;

            // Bandingkan berdasarkan opsi
            bool shouldSwap = false;
            if (sortOption == 1) { // Sort by artist
                if (current->artist > next->artist) {
                    shouldSwap = true;
                }
            } else if (sortOption == 2) { // Sort by title
                if (current->title > next->title) {
                    shouldSwap = true;
                }
            }

            // Swap jika diperlukan
            if (shouldSwap) {
                if (prev) {
                    prev->next = next;
                } else {
                    playlist->head = next;
                }
                current->next = next->next;
                next->next = current;

                swapped = true;
            }
            prev = current;
            current = current->next;
        }
    } while (swapped);

    // Tampilkan daftar lagu
    std::cout << "Songs in playlist " << playlist->name << ":\n";
    spotify::Song* current = playlist->head;
    int index = 1;
    while (current) {
        std::cout << index++ << ". " << current->title << " by " << current->artist << "\n";
        current = current->next;
    }
} 

// void spotify::listPlaylistSongs(spotify::Playlist* playlist){
//     if(playlist->head == nullptr){
//         std::cout<<"No songs available.\n";
//         return;
//     }

//     std::cout << "Songs in playlist "" << playlist->name << "":\n";
//     spotify::Song* current = playlist->head;
//     int index = 1;
//     while (current) {
//         std::cout << index++ << ". " << current->title << " by " << current->artist << "\n";
//         current = current->next;
//     }
// }

//Fungsi untuk menambahkan lagu
void spotify::addSongToPlaylist(spotify::Playlist* selectedPlaylist) {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string title, artist;

    std::cout << "Enter song title: ";
    std::getline(std::cin, title);

    std::cout << "Enter artist name: ";
    std::getline(std::cin, artist);

    // Membuat node baru untuk lagu
    spotify::Song* newSong = new Song{title, artist, nullptr};

    if (selectedPlaylist->head == nullptr) {
        // Jika playlist kosong, tambahkan sebagai lagu pertama
        selectedPlaylist->head = newSong;
    } else {
        // Jika playlist sudah berisi lagu, tambahkan di akhir
        spotify::Song* current = selectedPlaylist->head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newSong;
    }
}

void spotify::deleteSongFromPlaylist(spotify::Playlist* playlist) {
    if (!playlist || !playlist->head) {
        std::cout << "No songs available in the playlist.\n";
        return;
    }

    std::string songTitle;
    std::cout << "Enter the title of the song to delete: ";
    std::cin.ignore();  // Untuk menghapus newline yang tertinggal di buffer
    std::getline(std::cin, songTitle);

    spotify::Song* current = playlist->head;
    spotify::Song* previous = nullptr;

    // Cari lagu berdasarkan judul
    while (current) {
        if (current->title == songTitle) {
            // Jika lagu yang dihapus adalah yang pertama (head)
            if (!previous) {
                playlist->head = current->next;
            } else {
                // Jika lagu ada di tengah atau akhir
                previous->next = current->next;
            }

            delete current;  // Hapus memori lagu yang ditemukan
            std::cout << "Song '" << songTitle << "' deleted successfully.\n";
            return;
        }
        previous = current;
        current = current->next;
    }

    // Jika lagu tidak ditemukan
    std::cout << "Song not found in the playlist.\n";
}
