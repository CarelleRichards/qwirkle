#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <utility>

#include "Hand.h"

class Player {

   public:

    // Constructor for adding a new player.
    Player(std::string name);

    // Constructor for loading a player.
    Player(std::string name, int score, Hand* hand);

    Player(const Player& other);
    Player(Player&& other);
    ~Player();

    // Returns the player's name.
    std::string getName() const;

    // Returns the player's score.
    int getScore() const;

    // Returns the player's hand.
    Hand* getHand() const;

    // Takes a number >= 0 and adds it to the score.
    void addScore(int score);

   private:
   
    std::string name;
    int score;
    Hand* hand;
};

#endif  // PLAYER_H