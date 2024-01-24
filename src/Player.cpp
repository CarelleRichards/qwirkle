#include "../include/Player.h"

Player::Player(std::string name) {
    this->name = name;
    this->score = 0;
    this->hand = new Hand();
}

Player::Player(std::string name, int score, Hand* hand) {
    this->name = name;
    this->score = score;
    this->hand = hand;
}

Player::Player(const Player& other) {
    this->name = other.name;
    this->score = other.score;
    this->hand = new Hand(*other.hand);
}

Player::Player(Player&& other) {
    this->name = other.name;
    this->score = other.score;
    this->hand = other.hand;
    other.name = "";
    other.score = 0;
    other.hand = nullptr;
}

Player::~Player() {
    delete this->hand;
    this->hand = nullptr;
}

std::string Player::getName() const {
    return this->name;
}

int Player::getScore() const {
    return this->score;
}

Hand* Player::getHand() const { 
    return this->hand;
}

void Player::addScore(int score) {
    this->score = this->score + score;
}
