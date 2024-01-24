#include "../include/TileBag.h"

TileBag::TileBag() {
    this->tileBagList = new LinkedList();
}

TileBag::TileBag(const TileBag& other) {
    this->tileBagList = new LinkedList(*other.tileBagList);
}

TileBag::TileBag(TileBag&& other) {
    this->tileBagList = other.tileBagList;
    other.tileBagList = nullptr;
}

TileBag::~TileBag() {
    delete this->tileBagList;
    this->tileBagList = nullptr;
}

int TileBag::getLength() const {
    return this->tileBagList->getLength();
}

bool TileBag::isEmpty() {
    bool isEmpty = false;
    if (getLength() < 1) {
        isEmpty = true;
    }
    return isEmpty;
}

void TileBag::newGameTileBag(bool testFlag) {
    fillTileBag();
    shuffleTileBag(testFlag);
}

void TileBag::fillTileBag() {

    // Add shapes and colours to array for iteration.
    Colour colours[] = { COLOURS };           
    Shape shapes[] = { SHAPES };  

    // Add 2 of each colour and shape combination to the tile bag.
    for (int i = 0; i < sizeof(colours) / sizeof(Colour); i++) {
        for (int j = 0; j < sizeof(shapes) / sizeof(Shape); j++) {
            this->tileBagList->addEnd(new Tile(colours[i], shapes[j]));
            this->tileBagList->addEnd(new Tile(colours[i], shapes[j]));
        }
    }
}

void TileBag::shuffleTileBag(bool testFlag) {

    // Check if there are tiles in the tile bag.
    if (this->tileBagList->getLength() > 0) {
        LinkedList* tempTileList= new LinkedList();
        int totalTiles = this->tileBagList->getLength();

        // Shuffle tiles and put in temporary tile bag.
        for (int i = 0; i < totalTiles; i++) {

            // Generate a random number between min and max.
            int min = 1;
            int max = this->tileBagList->getLength();
            int randomVal = 0;
            std::uniform_int_distribution<int> uniform_dist(min, max);

            // If test flag is true, set seed for consistent randomness.
            if (testFlag) {
                std::default_random_engine engine(2);
                randomVal = uniform_dist(engine);
            } else {
                std::random_device engine;
                randomVal = uniform_dist(engine);
            }

            try {
                // Get a tile from tile bag at random pos.
                Tile* randomTile = this->tileBagList->getAtPos(randomVal);

                // Add tile to the temp tile bag.
                tempTileList->addEnd(new Tile(*randomTile));
                randomTile = nullptr;

                // Delete tile from original tile bag.
                this->tileBagList->deleteAtPos(randomVal);

            // If error happens while copying tiles.
            } catch (std::out_of_range& e) {
                throw std::out_of_range("Program error, can't make tile bag!");
            }
        }
        // Clean up and point to new tile bag. 
        delete this->tileBagList;
        this->tileBagList = tempTileList;
        tempTileList= nullptr;
    }
}

void TileBag::addTile(Tile* tile) {
    this->tileBagList->addEnd(tile);
}

void TileBag::fillHand(Hand* hand) {

    while ((hand->getLength() < hand->getMaxTilesInHand()) && !isEmpty()) {

        // Draw a tile from the front of the tile bag. 
        Tile* tileDrawn = this->tileBagList->getFront();

        // Add it to the end of the player's hand. 
        hand->addTile(new Tile(*tileDrawn));
        tileDrawn = nullptr;

        // Remove the tile from the tile bag.
        tileBagList->deleteFront();
    }
}

void TileBag::addToArray(std::string tilesArray[], int* i) {
    this->tileBagList->addToArray(tilesArray, i);
}

std::string TileBag::getAsStr() {
    return this->tileBagList->getAsStr();
}