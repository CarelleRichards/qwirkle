#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <exception>
#include <iostream>
#include <utility>

#include "Node.h"

class LinkedList {

   public:

    LinkedList();
    LinkedList(const LinkedList& other);
    LinkedList(LinkedList&& other);
    ~LinkedList();

    // Delete every tile.
    void clear();

    // Print every tile.
    void printList();

    // Returns the head.
    Tile* getFront() const;

    // Takes a pos > 0 and < length and returns tile at the pos.
    Tile* getAtPos(int pos) const;

    // Returns total number of tiles.
    int getLength() const;

    // Takes a tile and returns true if exists in the list.
    bool search(Tile* tile) const;

    // Takes a tile and adds it to the end.
    void addEnd(Tile* tile);

    // Takes tile and adds it to the front.
    void addFront(Tile* tile);

    // Takes a pos > 0 and < length and deletes the tile at that pos.
    void deleteAtPos(int pos);

    // Deletes the tile at the front.
    void deleteFront();

    // Deletes the tile at the end.
    void deleteEnd();

    // Takes a tile and removes the first match tile in list.
    void deleteByNode(Tile* tile);

    // Returns the list as a string.
    std::string getAsStr();

    // Takes a string array and adds the tiles from the list to it.
    // Tiles will be added to the array starting the given index.
    void addToArray(std::string array[], int* i);

   private:
   
    Node* head;
    Node* tail;
    int length;
};

#endif  // LINKEDLIST_H