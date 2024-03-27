#include "Playlist.h"

// CHANGE POSITION 5 TO 1 NOT WORKING PROPERLY



// default constructor for the playlist node, setting default values
PlaylistNode::PlaylistNode() 
  : uniqueID("none"), songName("none"), artistName("none"), songLength(0), nextNodePtr(nullptr) 
{}

// parametrized constructor, setting private member variables to user specified input
PlaylistNode::PlaylistNode(const string& uniqueID, const string& songName, const string& artistName, int songLength, PlaylistNode* nextNodePtr)
  : uniqueID(uniqueID), songName(songName), artistName(artistName), songLength(songLength), nextNodePtr(nullptr) 
{}

// copy constructor for the playlist
Playlist::Playlist(const Playlist& cpy) {
  head = nullptr;
  tail = nullptr;

  // checks if the copy's head is nullptr to proceed with creating a deep copy
  if (cpy.head != nullptr) {
    PlaylistNode *currNode = cpy.head;

    // allocates new memory in the heap for each node of the original playlist
    while (currNode != nullptr) {
      PlaylistNode* newNode = new PlaylistNode( currNode->GetID(), 
                                                currNode->GetSongName(), 
                                                currNode->GetArtistName(), 
                                                currNode->GetSongLength() );
      // if the original's head is nullptr, copy's head and tail are set to nullptr
      if (head == nullptr) {
        head = tail = newNode;
      }
      // moves the tail until the final node is reached
      else {
        tail->SetNext(newNode);
        tail = newNode;
      }
      // updates the current node to the next node in the list
      currNode = currNode->GetNext();
    }
  }
}

// copy assignment operator for the playlist
Playlist& Playlist::operator=(const Playlist& rhs) {
  // checks implicit parameter (left hand side or lhs) to make sure lhs and rhs are different
  if (this != &rhs) {
    clear();

    // same function as copy constructor
    if (rhs.head != nullptr) {
      PlaylistNode *currNode = rhs.head;

      while (currNode != nullptr) {
        PlaylistNode* newNode = new PlaylistNode(currNode->GetID(), 
                                                 currNode->GetSongName(), 
                                                 currNode->GetArtistName(), 
                                                 currNode->GetSongLength());
        if (empty()) {
          head = tail = newNode;
        }
        else {
          tail->SetNext(newNode);
          tail = newNode;
        }
        currNode = currNode->GetNext();
      }
    }
  }
  return *this;
}

void Playlist::clear() {
  // checks if playlist is empty, if false, deallocates the nodes from memory and
  // sets head and tail to nullptr to prevent a dangling pointer
  if (empty()) { return; }
  while (!empty()) {
    PlaylistNode *nextNode = head->GetNext();
    delete head;
    head = nextNode;
  }
  head = nullptr;
  tail = nullptr;
}

// prints the menu using user's playlist title
void Playlist::PrintMenu(const string& title) const {
  cout << title << " PLAYLIST MENU" << endl
       << "a - Add song" << endl
       << "d - Remove song" << endl
       << "c - Change position of song" << endl
       << "s - Output songs by specific artist" << endl
       << "t - Output total time of playlist (in seconds)" << endl
       << "o - Output full playlist" << endl
       << "q - Quit" << endl 
       << endl
       << "Choose an option:" << endl;
}

void Playlist::AddSong(const string& id, const std::string& song, const std::string& artist, int length) {
  // allocates memory for a node using user input for arguments
  PlaylistNode *newSong = new PlaylistNode(id, song, artist, length);
  // adds song to the end of the playlist and only updates tail if
  // list is not empty
  if (empty()) {
    head = tail = newSong;
  }
  else {
    tail->SetNext(newSong);
    tail = tail->GetNext();
  }
}
    
void Playlist::RemoveSong() {
  if (empty()) { return; }

  cout << endl << "REMOVE SONG" << endl;
  string uID;
  cout << "Enter song's unique ID:" << endl;
  // uses .ignore() to remove new line character before using getline
  cin.ignore();
  getline(cin, uID);
  // verifies input and checks if unique ID is empty
  if (!cin) { throw runtime_error("couldn't read unique ID"); }
  else if (uID.empty()) { throw runtime_error("unique ID can not be empty"); }

  // if the song to remove is the head, sets head to next node and deallocates the original head
  if (head->GetID() == uID) {
    cout << "\"" << head->GetSongName() << "\"" << " removed." << endl << endl;
    PlaylistNode *tempNode = head;
    head = head->GetNext();
    delete tempNode;
  }
  else {
    PlaylistNode *prevNode = head;
    PlaylistNode *currNode = head->GetNext();
    // traverses linked list until id is found, then deallocates the node
    while (currNode != nullptr) {
      if (currNode->GetID() == uID) {
        cout << "\"" << currNode->GetSongName() << "\"" << " removed." << endl << endl;
        prevNode->SetNext(currNode->GetNext());
        // checks if the id is in the tail
        if (tail == currNode) { tail = prevNode; }
        delete currNode;
        // break is used to exit the loop once the first instance of the song is removed
        break;
      }
      // updates position of the nodes, if id is not found
      prevNode = currNode;
      currNode = currNode->GetNext();
    }
  }
}
    
void Playlist::ChangePositionSong() {
  // if empty, return to main
  if (empty()) { return; }

  int currPositionIndex = 0, newPositionIndex = 0, numSongsInPlaylist = 0, i = 1;

  PlaylistNode *currPosPrevNode = nullptr;
  PlaylistNode *currPosNode = head;
  PlaylistNode *newPositionPrevNode = nullptr;
  PlaylistNode *newPositionNode = head;

  // uses for loop to count the number of songs in the playlist, incrementing by 1 for each song
  for(const PlaylistNode* curr = head; curr != nullptr; curr = curr->GetNext()) { numSongsInPlaylist++; }

  cout << "CHANGE POSITION OF SONG" << endl
       << "Enter song's current position:" << endl;
  cin.clear();
  cin >> currPositionIndex;
  // verifies input and checks to see if song positions are out of bounds or if position
  // change is necessary based on the current and new positions
  if (!cin) { throw runtime_error("couldn't read current song's position"); }
  else if (currPositionIndex < 1 || currPositionIndex > numSongsInPlaylist) { throw out_of_range("invalid input, current position out of bounds"); }
  else if (currPositionIndex < 1 && newPositionIndex <= 1) { return; }
  else if (currPositionIndex == numSongsInPlaylist && newPositionIndex >= numSongsInPlaylist) { return; }

  cout << "Enter new position for song:" << endl;
  cin.clear();
  cin >> newPositionIndex;
  if (!cin) { throw runtime_error("couldn't read new song's position"); }

  // traverses linked list to find the current position of the song and the node before it
  while (i < currPositionIndex) {
    // checks if node is nullptr before updating i and moving to next node
    if (currPosNode != nullptr) {
      i++;
      currPosPrevNode = currPosNode;
      currPosNode = currPosNode->GetNext();
    }
  }

  string currPosSongName = currPosNode->GetSongName();

  // resets iterator i and traverses list to find the new position of the song 
  // and the node before it
  i = 1;
  while (i < newPositionIndex) {
    if (newPositionNode != nullptr) {
      i++;
      newPositionPrevNode = newPositionNode;
      newPositionNode = newPositionNode->GetNext();
    }
  }

  string newPosSongName = newPositionNode->GetSongName();
  
  // if current position is head, handles cases where song is moved to the middle
  // or moved to the tail, using InsertAfter()
  if (currPositionIndex <= 1) {
    head = head->GetNext();
    // after the position of the new node, inserts the current node
    newPositionNode->InsertAfter(currPosNode);
  }
  // if current position is tail, handles special cases where song is moved to the middle
  // or moved to the head, using InsertAfter()
  else if (currPositionIndex >= numSongsInPlaylist) {
    // if new position is head, inserts current node after the head
    if (newPositionIndex == 1) {
      head->InsertAfter(currPosNode);
    }
    // else, uses the previous node in the new position to insert the current node
    else {
      newPositionPrevNode->InsertAfter(currPosNode);
    }
    // once old tail is moved, tail is updated
    tail = currPosPrevNode;
    tail->SetNext(nullptr);
  }
  // handles case where song is moved down the list, special case if new position is tail
  else if (newPositionIndex > currPositionIndex) {
    newPositionNode->InsertAfter(currPosNode);
    // if new position is tail and not in the middle of the list, adjusts to update tail
    if (newPositionIndex >= numSongsInPlaylist) {
      currPosPrevNode->SetNext(newPositionPrevNode);
      tail = currPosNode;
    }
    else {
      currPosPrevNode->SetNext(newPositionPrevNode);
    }
  }
  // handles case where song is moved up the list, special case if new position is head
  else if (newPositionIndex < currPositionIndex) {
    currPosPrevNode->SetNext(currPosNode->GetNext());
    // if new position is head and not in the middle of the list, adjusts to update head
    if (newPositionIndex == 1) {
      head = currPosNode;
      currPosNode->SetNext(newPositionNode);
    }
    // else, inserts after a node in the middle of the list
    else {
      newPositionPrevNode->InsertAfter(currPosNode);
    }
  }

  cout << "\"" << currPosSongName << "\"" << " moved to position " << newPositionIndex << endl << endl;

}
    
void Playlist::OutputSongsByArtist() const {
  // checks that playlist is not empty, return to main
  if (empty()) { return; }

  int i = 0;
  string artistName;
  cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl
       << "Enter artist's name:" << endl;
  cin.ignore();
  getline(cin, artistName);
  cout << endl;
  // verifies input and checks if artist name to search for is empty
  if (!cin) { throw runtime_error("couldn't read artist name"); }
  else if (artistName.empty()) { throw runtime_error("artist name can not be empty"); }

  // uses for loop and iterator variable 'i' for numbering of each node
  for(const PlaylistNode* curr = head; curr != nullptr; curr = curr->GetNext()) {
    ++i;
    // if statement checks if the node's artist matches the artist of interest
    if (curr->GetArtistName() == artistName) {
      cout << i << "." << endl
            << "Unique ID: " << curr->GetID() << endl
            << "Song Name: " << curr->GetSongName() << endl
            << "Artist Name: " << curr->GetArtistName() << endl
            << "Song Length (in seconds): " << curr->GetSongLength() << endl << endl;
    }
  }
}
    
void Playlist::OutputTotalTime() const {
  // checks that playlist is not empty, otherwise return to main
  if (empty()) { return; }

  int totalTime = 0;
  // uses for loop to get song length from each node, summing into variable 'totalTime'
  for(const PlaylistNode* curr = head; curr != nullptr; curr = curr->GetNext()) { 
    totalTime += curr->GetSongLength(); 
  }
  cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;
  cout << "Total time: " << totalTime << " seconds" << endl << endl;
}

void Playlist::OutputFullPlaylist() const {
  // checks that playlist is not empty, otherwise output empty message
  if (empty()) { cout << "Playlist is empty" << endl << endl; }
  else {
    int i = 0;
    // uses for loop and iterator variable 'i' to output and number the node's position
    for(const PlaylistNode* curr = head; curr != nullptr; curr = curr->GetNext()) {
      cout << ++i << "." << endl
           << "Unique ID: " << curr->GetID() << endl
           << "Song Name: " << curr->GetSongName() << endl
           << "Artist Name: " << curr->GetArtistName() << endl
           << "Song Length (in seconds): " << curr->GetSongLength() << endl << endl;
    } 
  }
}
    

