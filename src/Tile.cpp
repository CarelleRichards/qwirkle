#include "../include/Tile.h"

Tile::Tile(Colour colour, Shape shape) {
    this->shape = Shape(shape);
    this->colour = Colour(colour);
}

Tile::Tile(const Tile& other) {
    this->shape = other.shape;
    this->colour = other.colour;
}

Tile::Tile(Tile&& other) {
    this->shape = other.shape;
    this->colour = other.colour;
    other.shape = 0;
    other.colour = '\0';
}

Tile::~Tile() {}

std::string Tile::getAsStr() {
    std::string tileStr = this->colour + std::to_string(this->shape);
    return tileStr;
}