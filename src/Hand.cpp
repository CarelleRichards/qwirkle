#include "../include/Hand.h"

Hand::Hand() {
    this->handList = new LinkedList();
}

Hand::Hand(const Hand& other) {
    this->handList = new LinkedList(*other.handList);
}

Hand::Hand(Hand&& other) {
    this->handList = other.handList;
    other.handList = nullptr;
}

Hand::~Hand() {
    delete this->handList;
    this->handList = nullptr;
}

std::string Hand::getAsStr() {
    return this->handList->getAsStr();
}

bool Hand::isEmpty() {
    bool isEmpty = false;
    if (getLength() < 1) {
        isEmpty = true;
    }
    return isEmpty;
}

int Hand::getLength() const {
    return this->handList->getLength();
}

void Hand::addToArray(std::string tilesArray[], int* i) {
    this->handList->addToArray(tilesArray, i);
}

bool Hand::containsTile(Tile* tile) {
    return this->handList->search(tile);
}

void Hand::removeTile(Tile* tile) {
    this->handList->deleteByNode(tile);
}

void Hand::printHand() {
    this->handList->printList();
}

void Hand::addTile(Tile* tile) {
    this->handList->addEnd(tile);
}

int Hand::getMaxTilesInHand() const {
    return this->maxTilesInHand;
}

Tile* Hand::getAtPos(int pos) {
    return this->handList->getAtPos(pos);
}