#include <iostream>

#include "Playlist.h"

using namespace std;

int main() {
  string title;
  cout << "Enter playlist's title:" << endl;
  getline(cin, title);
  // verifies input and checks that the title is not empty
  if (!cin) { throw runtime_error("couldn't read playlist title"); }
  else if (title.empty()) { throw runtime_error("title can not be empty"); }
  cout << endl;

  Playlist P;

  while(true) {
    P.PrintMenu(title);

    // Read commands until error or end-of-file
    string command;
    if (!(cin >> command)) break;

    if (command == "a") {
      string uID, songName, artistName;
      int songLen;
      cout << "ADD SONG" << endl;
      cout << "Enter song's unique ID:" << endl;
      cin.ignore();
      getline(cin, uID);
      // verifies input and checks that the inputs arent empty
      if (!cin) { throw runtime_error("couldn't read unique ID"); }
      else if (uID.empty()) { throw runtime_error("unique ID can not be empty"); }

      cout << "Enter song's name:" << endl;
      getline(cin, songName);
      if (!cin) { throw runtime_error("couldn't read song name"); }
      else if (songName.empty()) { throw runtime_error("song name can not be empty"); }

      cout << "Enter artist's name:" << endl;
      getline(cin, artistName);
      if (!cin) { throw runtime_error("couldn't read artist name"); }
      else if (artistName.empty()) { throw runtime_error("artist name can not be empty"); }

      cout << "Enter song's length (in seconds):" << endl;
      cin >> songLen;
      // verifies input and checks that the song length is a non-negative number
      if (!cin) { throw runtime_error("couldn't read song length"); }
      else if (songLen < 0) { throw runtime_error("song length must be positive"); }
      // clears the cin buffer before asking for command using extraction operator
      cin.clear();
      cout << endl;
      P.AddSong(uID, songName, artistName, songLen);
    } else if (command == "d") {
      P.RemoveSong();
    } else if (command == "c") {
      P.ChangePositionSong();
    } else if (command == "s") {
      P.OutputSongsByArtist();
    } else if (command == "t") {
      P.OutputTotalTime();
    } else if (command == "o") {
      cout << title << " - OUTPUT FULL PLAYLIST" << endl;
      P.OutputFullPlaylist();
    } else if (command == "q") {
      break;
    }
  }

  // If cin is in an error state (even end-of-file), then
  // something went wrong
  if (!cin) {
    cout << "Program did not exit cleanly" << endl;
    return 1;
  }
  
  return 0;
}
