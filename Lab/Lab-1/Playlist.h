#pragma once

#include <iostream>
using namespace std;

class PlaylistNode {
private:
  string uniqueID;
  string songName;
  string artistName;
  int songLength;
  PlaylistNode* nextNodePtr;
public:
  PlaylistNode();
  PlaylistNode(const string& uniqueID, const string& songName, const string& artistName, int songLength, PlaylistNode* nextNodePtr = nullptr);
  // getter functions return const values of private variables
  const string& GetID() const { return uniqueID; }
  const string& GetArtistName() const { return artistName; }
  const string& GetSongName() const { return songName; }
  int GetSongLength() const { return songLength; }
  // sets the nextNodePtr private variable to the function argument
  void SetNext(PlaylistNode* nextPtr) { nextNodePtr = nextPtr; }
  void InsertAfter(PlaylistNode* newNext) {
    // uses a temporary node to store the next node
    PlaylistNode *tempNode = GetNext();
    // sets the implicit parameter's next to the new next position
    SetNext(newNext);
    // assigns the original node's next to the new node
    newNext->SetNext(tempNode);
  }
  PlaylistNode* GetNext() { return nextNodePtr; }
  const PlaylistNode* GetNext() const { return nextNodePtr; }
  const void PrintPlaylistNode() const {
    cout << "Unique ID: " << uniqueID << '\n';
    cout << "Song Name: " << songName << '\n';
    cout << "Artist Name: " << artistName << '\n';
    cout << "Song Length (in seconds): " << songLength;
  }
};

class Playlist {
private:
  PlaylistNode* head;
  PlaylistNode* tail;
public:
  Playlist() : head(nullptr), tail(nullptr) {}
  // declares and defines the destructor, uses clear() (declared below)
  ~Playlist() { clear(); }
  Playlist(const Playlist&);
  Playlist& operator=(const Playlist&);
  // clears the list (defined in Playlist.cpp)
  void clear();
  // if the head returns nullptr, indicates the list is empty
  bool empty() const { return head == nullptr; }
  void PrintMenu(const string& title) const;
  void AddSong(const string& id, const std::string& song, const std::string& artist, int length);
  void RemoveSong();
  void ChangePositionSong();
  void OutputSongsByArtist() const;
  void OutputTotalTime() const;
  void OutputFullPlaylist() const;
};

