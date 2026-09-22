// ECCS 2671 - Project 1: Doubly Linked List Implementation (Music Playlist)
//
// Student 1 Name: __________________________
// Student 2 Name: __________________________
//
// Do NOT modify this file's SongNode struct or the MusicPlaylist class
// declaration below. Implement the marked functions in MusicPlaylist.cpp.
//
// Student 1 implements the functions marked "STUDENT 1" below.
// Student 2 implements the functions marked "STUDENT 2" below.

#ifndef MUSICPLAYLIST_H
#define MUSICPLAYLIST_H

#include <iostream>
#include <string>
using namespace std;

// ---------------------------------------------------------------------
// SongNode - one song in the playlist (doubly linked: prev and next)
// ---------------------------------------------------------------------
struct SongNode {
    string songName;
    string artistName;
    int songNumber;
    SongNode* prev;
    SongNode* next;

    SongNode(string name, string artist, int num, SongNode* p, SongNode* n) {
        songName = name;
        artistName = artist;
        songNumber = num;
        prev = p;
        next = n;
    }
};

// ---------------------------------------------------------------------
// MusicPlaylist - the doubly linked list class
// ---------------------------------------------------------------------
class MusicPlaylist {
private:
    SongNode* head;
    SongNode* tail;
    int numSongs;

    // STUDENT 1 - private helper
    SongNode* getSongNode(const string song);

    // STUDENT 2 - private helper
    SongNode* getSongNode(const int songNumber);

public:
    MusicPlaylist();
    ~MusicPlaylist();

    int getNumSongs();

    // STUDENT 1
    void addSong(const string addedSongName);
    // STUDENT 1
    void addSong(const string addedSongName, const int songOrder);
    // STUDENT 2
    void addSong(const string addedSongName, const int songOrder, const string artistName);

    // STUDENT 1
    void deleteSong(const string deletedSongName);
    // STUDENT 2
    void deleteLastSong();
    // STUDENT 2
    void deleteSong(const int songNumInList);

    // STUDENT 1
    int getSongNum(const string searchedSongName);
    // STUDENT 2
    string getSongName(const int songNumInList);

    friend ostream& operator<<(ostream& os, const MusicPlaylist& list);
};

#endif
