#include "../include/Game.h"

Game::Game(bool testFlag, bool enhancedFlag) {
    this->testFlag = testFlag;
    this->enhancedFlag = enhancedFlag;
    this->mode = dual;
    this->currPlayer = 0;
    this->gameComplete = false;
    this->tileBag = nullptr;
    this->board = nullptr;
    this->scoreCalculator = new ScoreCalculator();
    this->placeChecker = new PlaceChecker();
    this->skipsInRow = 0;
}

Game::Game(const Game& other) {
    for (Player* player : other.players) {
        this->players.push_back(new Player(*player));
    }
    this->tileBag = new TileBag(*other.tileBag);
    this->board = new Board(*other.board);
    this->scoreCalculator = new ScoreCalculator(*other.scoreCalculator);
    this->placeChecker = new PlaceChecker(*other.placeChecker);
    this->currPlayer = other.currPlayer;
    this->mode = other.mode;
    this->testFlag = other.testFlag;
    this->enhancedFlag = other.enhancedFlag;
    this->skipsInRow = other.skipsInRow;
}

Game::Game(Game&& other) {
    this->players = other.players;
    other.players.clear();
    this->currPlayer = other.currPlayer; 
    other.currPlayer = 0; 
    this->scoreCalculator = other.scoreCalculator;
    other.scoreCalculator = nullptr;
    this->placeChecker = other.placeChecker;
    other.placeChecker = nullptr;
    this->board = other.board;
    other.board = nullptr;
    this->tileBag = other.tileBag;
    other.tileBag = nullptr;
    this->mode = other.mode;
    other.mode = dual;
    this->testFlag = other.testFlag;
    other.testFlag = false;
    this->enhancedFlag = other.enhancedFlag;
    other.enhancedFlag = false;
    this->skipsInRow = other.skipsInRow;
    other.skipsInRow = 0;
}

Game::~Game() {
    if (this->board != nullptr) {
        delete this->board;
        this->board = nullptr;
    }
    if (this->tileBag != nullptr) {
        delete this->tileBag;
        this->tileBag = nullptr;
    }
    for (Player* player : this->players) {
        delete player;
        player = nullptr;
    }
    this->players.clear();
    delete this->scoreCalculator;
    this->scoreCalculator = nullptr;
    delete this->placeChecker;
    this->placeChecker = nullptr;
}

void Game::newGame(std::vector<Player*> players, Mode mode) {

    // Set the mode. 
    this->mode = mode;

    // Create the tile bag and board.
    this->tileBag = new TileBag();
    this->tileBag->newGameTileBag(this->testFlag);

    // Set up the players and their hands.
    this->players = players;
    for (Player* player : this->players) {
        this->tileBag->fillHand(player->getHand());
    }

    // Start with empty board and player 1 starts.
    this->board = new Board();
}

bool Game::loadGame(std::vector<Player*> players, Board* board, 
    TileBag* tileBag, int currPlayer, Mode mode) {

    // Check that given data contains a full set of tiles.
    bool correctTiles = checkTiles(players, board, tileBag);

    // Create game and load data if tiles are correct.
    if (correctTiles) {
        this->tileBag = tileBag;
        this->board = board;
        this->currPlayer = currPlayer;
        this->players = players;
        this->mode = mode;
    } 
    return correctTiles;
}

Player* Game::getCurrPlayer() const {
    return this->players[this->currPlayer];
}

Board* Game::getBoard() const {
    return this->board;
}

std::vector<std::string> Game::getWinners() {

    // Vector to store winner names.
    std::vector<std::string> winners;

    // High score tracker.
    int highestScore = 0;
    
    for (Player* player : this->players) {

        // Clear vector and add player if score > highest score.
        if (player->getScore() > highestScore) {
            winners.clear();
            winners.push_back(player->getName());
            highestScore = player->getScore();

        // Add to vector with other winners score if high score tie. 
        } else if (player->getScore() == highestScore) {
            winners.push_back(player->getName());
        }
    }
    return winners;
}

void Game::nextPlayerTurn() {
    if (this->currPlayer == this->players.size() - 1) {
        this->currPlayer = 0;
    } else {
        this->currPlayer = this->currPlayer + 1;
    }
}

TileBag* Game::getTileBag() const {
    return this->tileBag;
}

bool Game::isComplete() {
    if (!this->gameComplete && this->tileBag->isEmpty()) {
        for (Player* player : players) {
            if (player->getHand()->isEmpty()) {
                this->gameComplete = true;
            }
        }
    }
    return this->gameComplete;
}

bool Game::isReplaceLegal(Tile* tile) const {
    bool isLegal = getCurrPlayer()->getHand()->containsTile(tile) && 
        !this->tileBag->isEmpty();
    return isLegal;
}

bool Game::isPlaceLegal(Tile* tile, char row, int col) const {
    bool isLegal = this->placeChecker->checkPlace(this->board, 
        getCurrPlayer(), tile, row, col);
    return isLegal;
}

void Game::skipTurn() {
    if (isSkipAvailable()) {
        nextPlayerTurn();
        int maxSkips = 0;
        if (this->mode == single || this->mode == dual) {
            maxSkips = 2;
        } else if (this->mode == triple) {
            maxSkips = 3;
        } else if (this->mode == quad) {
            maxSkips = 4;
        }
        this->skipsInRow++;
        if (this->skipsInRow == maxSkips) {
            this->gameComplete = true;
        } 
    }
}

bool Game::isSkipAvailable() {
    bool skipAvailable = this->tileBag->isEmpty(); 
    return skipAvailable;
}

bool Game::replaceTile(Tile *tile) {

    // Check if replace is legal according to the rules.
    bool isLegal = isReplaceLegal(tile);

    if (isLegal) {
        // Remove the given tile from hand and place it in the tile bag.
        getCurrPlayer()->getHand()->removeTile(tile);
        this->tileBag->addTile(tile);

        // Draw a new tile from the tile bag and add it to the hand.
        this->tileBag->fillHand(getCurrPlayer()->getHand()); 

        // Continue with the other player’s turn.
        nextPlayerTurn();
        this->skipsInRow = 0;
    }
    return isLegal;
}

bool Game::placeTile(Tile *tile, char row, int col) {

    // Check if the placement is legal according to the rules.
    bool isLegal = isPlaceLegal(tile, row, col);
    
    // Place the tile if legal and go to next player's turn. 
    if (isLegal) {
        commitPlaceTile(tile, row, col);
    }
    return isLegal;
}

void Game::commitPlaceTile(Tile* tile, char row, int col) {

    // Place the tile on the board.
    this->board->addTileAtPos(tile, row, col);
    getCurrPlayer()->getHand()->removeTile(tile);

    // Update the player’s score.
    getCurrPlayer()->addScore(getScore(row, col));

    // If the tile bag isn't empty, draw replacement and add to hand. 
    this->tileBag->fillHand(getCurrPlayer()->getHand()); 

    // Continue with the other player’s turn.
    nextPlayerTurn();
    this->skipsInRow = 0;
}

int Game::getScore(char row, int col) {
    int score = scoreCalculator->calculateScore(this->board, row, col);
    return score;
}

bool Game::checkTiles(std::vector<Player*> players, 
    Board* board, TileBag* tileBag) {
                      
    // Find total tiles across board, tile bag and players.
    int totalTiles = board->getLength() + tileBag->getLength();
    for (Player* player : players) {
        totalTiles = totalTiles + player->getHand()->getLength();
    }

    // Check if there are the right number of tiles.
    bool correctTiles = true;
    if (totalTiles != this->maxTilesInGame) {
        correctTiles = false;

    // If right number, check for 2 of each type of tile.
    } else {
  
        // Add all given tiles to a single array.
        std::string tilesArray[this->maxTilesInGame];
        int i = 0;
        for (Player* player : players) {
            player->getHand()->addToArray(tilesArray, &i);
        }
        tileBag->addToArray(tilesArray, &i);
        board->addToArray(tilesArray, &i);

        // Make array with all expected tiles.
        std::string expectedTilesArray[this->maxTilesInGame];
        addToArray(expectedTilesArray);

        // Compare the two arrays.
        correctTiles = arraysEqual(expectedTilesArray, tilesArray);
    }
    return correctTiles;
}

void Game::addToArray(std::string expectedTilesArray[]) { 

    // Add shapes and colours to array for iteration.
    Colour colours[] = { COLOURS };           
    Shape shapes[] = { SHAPES };     

    // Track array index.
    int i = 0;

    // Add 2 of each colour and shape combination to the array.
    for (int j = 0; j < sizeof(colours) / sizeof(Colour); j++) {
        for (int k = 0; k < sizeof(shapes) / sizeof(Shape); k++) {
            expectedTilesArray[i] = colours[j] + std::to_string(shapes[k]);
            i++;
            expectedTilesArray[i] = colours[j] + std::to_string(shapes[k]);        
            i++;
        }
    }
}

bool Game::arraysEqual(std::string array1[], std::string array2[]) {  

    // Make sure both array are in same order.
    std::sort(array1, array1 + this->maxTilesInGame);
    std::sort(array2, array2 + this->maxTilesInGame);

    bool isEqual = true;
    int i = 0;

    // Linearly compare elements of both arrays.
    while (isEqual && i != this->maxTilesInGame) {
        if (array1[i] != array2[i]) {
            isEqual = false;
        }
        i++;
    }
    return isEqual;
}

std::vector<Player*> Game::getPlayers() const {
    return this->players;
}

Mode Game::getMode() const {
    return this->mode;
}

void Game::takeTurnForPlayer() {
    bool tilePlaced = placeForPlayer();
    if (!tilePlaced) {
        bool tileReplaced = replaceForPlayer();
        if (!tileReplaced) {
            skipTurn();
        }
    }
}

bool Game::placeForPlayer() {
    char bestRow = '\0';
    int bestCol = -1;
    Tile* bestTile = nullptr;
    int bestScore = 0;

    // Check every position on the board. 
    for (char row = this->board->getMinRowChar(); 
        row <= this->board->getMaxRowChar(); row++) {
        for (int col = this->board->getMinCol(); 
            col <= this->board->getMaxCol(); col++) { 

            // Check if a tile can be placed from the player's hand.
            for (int i = 1; i <= getCurrPlayer()->getHand()->getLength(); i++) {  
                Tile* tile = getCurrPlayer()->getHand()->getAtPos(i);
                bool result = isPlaceLegal(tile, row, col);

                // Calculate score of placement, record if > best score.
                if (result) {
                    this->board->addTileAtPos(new Tile(*tile), row, col);
                    int score = getScore(row, col);
                    this->board->deleteAtPos(row, col);
                    if (score > bestScore) {
                        bestRow = row;
                        bestCol = col;
                        bestScore = score;
                        bestTile = tile;
                    }
                }
                tile = nullptr;
            }   
        }
    }
    
    // Try to place the best tile. 
    bool tilePlaced = false;
    if (bestTile != nullptr) {
        commitPlaceTile(new Tile(*bestTile), bestRow, bestCol);
        bestTile = nullptr;
        tilePlaced = true;
    }
    return tilePlaced;
}

bool Game::replaceForPlayer() {
    Tile* bestTile = nullptr;

    // Check for duplicate tiles in current player's hand. 
    for (int i = 1; i <= getCurrPlayer()->getHand()->getLength(); i++) {
        int count = 0;
        for (int j = 1; i <= getCurrPlayer()->getHand()->getLength(); i++) {
            if (getCurrPlayer()->getHand()->getAtPos(i)->getAsStr() == 
                getCurrPlayer()->getHand()->getAtPos(j)->getAsStr()) {
                count++;
                if (count > 1) {
                    bestTile = getCurrPlayer()->getHand()->getAtPos(i);
                }
            }
        }
    }

    // If no duplicates, pick random tile from hand. 
    if (bestTile == nullptr) {
        int min = 1;
        int max = getCurrPlayer()->getHand()->getLength();
        std::uniform_int_distribution<int> uniform_dist(min, max);
        std::random_device engine;
        int randomVal = uniform_dist(engine);
        bestTile = getCurrPlayer()->getHand()->getAtPos(randomVal);
    }

    // Try to replace the best tile. 
    bool tileReplaced = replaceTile(new Tile(*bestTile));
    bestTile = nullptr;
    return tileReplaced;   
}