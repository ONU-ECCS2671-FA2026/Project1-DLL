// ECCS 2671 - Project 1: Doubly Linked List Implementation (Music Playlist)
//
// Do NOT modify the constructor, destructor, getNumSongs(), or the
// operator<< friend function below -- they are already implemented.
//
// Student 1 implements the functions marked "STUDENT 1" below.
// Student 2 implements the functions marked "STUDENT 2" below.

#include "MusicPlaylist.h"

// ---------------------------------------------------------------------
// Already implemented - do not modify
// ---------------------------------------------------------------------
MusicPlaylist::MusicPlaylist() {
    head = nullptr;
    tail = nullptr;
    numSongs = 0;
}

MusicPlaylist::~MusicPlaylist() {
    SongNode* cur = head;
    while (cur != nullptr) {
        SongNode* toDelete = cur;
        cur = cur->next;
        delete toDelete;
    }
    head = nullptr;
    tail = nullptr;
    numSongs = 0;
}

int MusicPlaylist::getNumSongs() {
    return numSongs;
}

ostream& operator<<(ostream& os, const MusicPlaylist& list) {
    SongNode* cur = list.head;
    if (cur == nullptr) {
        os << "Empty Play List" << endl;
        return os;
    }
    while (cur != nullptr) {
        os << cur->songNumber << ". " << cur->songName;
        if (!cur->artistName.empty()) {
            os << " - " << cur->artistName;
        }
        os << endl;
        cur = cur->next;
    }
    return os;
}

// =======================================================================
// STUDENT 1 - implement the five functions below
// =======================================================================

// Traverses the list looking for the given song name and returns a
// pointer to the first node with that name, or nullptr if not present.
SongNode* MusicPlaylist::getSongNode(const string song) {
    // TODO (Student 1): implement per the spec in the Description doc.
    return nullptr;
}

// Adds a new song at the head of the playlist. All other song numbers
// shift up by one. No artist is given, so use an empty string.
void MusicPlaylist::addSong(const string addedSongName) {
    // TODO (Student 1): implement per the spec in the Description doc.
    // Reminder: this is a doubly linked list -- when you link the new
    // node in, set BOTH its prev and next, and fix the old head's prev.
}

// Adds a new song at position songOrder (valid range 1..numSongs).
// If songOrder < 2, place at the head; if songOrder > numSongs, place
// at the tail. No artist is given, so use an empty string.
void MusicPlaylist::addSong(const string addedSongName, const int songOrder) {
    // TODO (Student 1): implement per the spec in the Description doc.
    // Reminder: this is a doubly linked list -- whichever node(s) you
    // splice next to, fix BOTH their prev and next pointers, not just next.
}

// Deletes the song node with the given name, if present.
void MusicPlaylist::deleteSong(const string deletedSongName) {
    // TODO (Student 1): implement per the spec in the Description doc.
    // Reminder: this is a doubly linked list -- fix BOTH the prev and
    // next pointers of the deleted node's neighbors before you delete it.
}

// Searches for searchedSongName and returns its song number if found,
// or -1 if it is not in the playlist.
int MusicPlaylist::getSongNum(const string searchedSongName) {
    // TODO (Student 1): implement per the spec in the Description doc.
    return -1;
}

// =======================================================================
// STUDENT 2 - implement the five functions below
// =======================================================================

// Traverses the list looking for the node with the given song number.
// Return head if songNumber < 2, tail if songNumber >= numSongs, or the
// first node whose song number is at least songNumber.
SongNode* MusicPlaylist::getSongNode(const int songNumber) {
    // TODO (Student 2): implement per the spec in the Description doc.
    return nullptr;
}

// Adds a new song at position songOrder (valid range 1..numSongs) with
// the given artist. If songOrder < 2, place at the head; if
// songOrder > numSongs, place at the tail.
void MusicPlaylist::addSong(const string addedSongName, const int songOrder, const string artistName) {
    // TODO (Student 2): implement per the spec in the Description doc.
    // Reminder: this is a doubly linked list -- whichever node(s) you
    // splice next to, fix BOTH their prev and next pointers, not just next.
}

// Deletes the last song in the playlist (at the tail).
void MusicPlaylist::deleteLastSong() {
    // TODO (Student 2): implement per the spec in the Description doc.
}

// Deletes the song node at the given position (songNumInList). Delete
// the first song if songNumInList < 2, or the last node if
// songNumInList >= numSongs.
void MusicPlaylist::deleteSong(const int songNumInList) {
    // TODO (Student 2): implement per the spec in the Description doc.
    // Reminder: this is a doubly linked list -- fix BOTH the prev and
    // next pointers of the deleted node's neighbors before you delete it.
}

// Returns the name of the song at the given position. Return the head's
// name if songNumInList < 2, and the tail's name if
// songNumInList >= numSongs. For an empty list, return "Empty Play List".
string MusicPlaylist::getSongName(const int songNumInList) {
    // TODO (Student 2): implement per the spec in the Description doc.
    return "Empty Play List";
}
