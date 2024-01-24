#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <utility>

#include "Tile.h"

class Node {

   public:
   
    Node(Tile* tile);

    // Deep copies node, including it's next and prev nodes.
    // This is used for the linked list copy constructor.
    Node(const Node& other);

    Node(Node&& other);
    ~Node();

    Tile* tile;
    Node* next;
    Node* prev;

   private:
};

#endif  // NODE_H