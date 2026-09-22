// ECCS 2671 - Project 1: Doubly Linked List Implementation (Music Playlist)
//
// main() - already implemented; comment out lines to debug as needed.
// Do NOT modify this file.

#include "MusicPlaylist.h"

int main() {
    MusicPlaylist playlist;

    cout << "--- Building the playlist ---" << endl;
    playlist.addSong("Clocks");                             // Student 1: head insert
    playlist.addSong("Fix You");                             // Student 1: head insert
    playlist.addSong("Viva la Vida", 2);                     // Student 1: middle insert
    playlist.addSong("Yellow", 4, "Coldplay");                // Student 2: tail/middle insert
    cout << playlist;

    cout << "\n--- Searching ---" << endl;
    cout << "Song number of \"Yellow\": " << playlist.getSongNum("Yellow") << endl;   // Student 1
    cout << "Song name at position 2: " << playlist.getSongName(2) << endl;           // Student 2

    cout << "\n--- Deleting ---" << endl;
    playlist.deleteSong("Fix You");   // Student 1
    playlist.deleteLastSong();        // Student 2
    cout << playlist;

    cout << "\nTotal songs remaining: " << playlist.getNumSongs() << endl;

    return 0;
}
