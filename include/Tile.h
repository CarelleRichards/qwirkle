#ifndef TILE_H
#define TILE_H

#include <iostream>
#include <utility>

#include "TileCodes.h"

typedef char Colour;
typedef int Shape;

class Tile {

   public:
   
    // Constructor for making a tile. Takes a colour
    // and shape, see TileCodes.h for more info.
    Tile(Colour colour, Shape shape);

    Tile(const Tile& other);
    Tile(Tile&& other);
    ~Tile();

    // Returns the tile colour and shape as a string.
    std::string getAsStr();
    
    Colour colour;
    Shape shape;

   private:
};

#endif  // TILE_H