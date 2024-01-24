#ifndef SCORECALCULATOR_H
#define SCORECALCULATOR_H

#include <iostream>

#include "Board.h"

class ScoreCalculator {

   public:

    ScoreCalculator();
    ScoreCalculator(const ScoreCalculator& other);
    ScoreCalculator(ScoreCalculator&& other);
    ~ScoreCalculator();

    // Takes the board, row (A-Z) and col (0-25) position 
    // and returns the total score for the tile placement. 
    int calculateScore(Board* board, char row, int col);

   private:
   
    // Displays a message when a Qwirkle is scored. 
    // This is used in checkQwirklePoints().
    void printQwirkle() const;

    // Takes the board, row (A-Z) and col (0-25) tile placement and returns  
    // the score for the row the tile was placed in. Used by calculateScore().
    int getRowScore(Board* board, char row, int col);

    // Takes the board, row (A-Z) and col (0-25) tile placement and returns the 
    // score for the col the tile was placed in. Used by calculateScore().
    int getColScore(Board* board, char row, int col);

    // Takes the board, row (A-Z) and col (0-25) tile placement and returns 
    // the start col number for a row. Used by getRowScore().
    int getRowStart(Board* board, char row, int col);

    // Takes the board, row (A-Z) and col (0-25) tile placement and returns 
    // the end column number for a row. Used by getRowScore().
    int getRowEnd(Board* board, char row, int col);

    // Takes the board, row (A-Z) and col (0-25) tile placement and returns 
    // the start row number for a column. This is a char returned as int and
    // would assume both are in the same case. Used by getColScore().
    int getColStart(Board* board, char row, int col);

    // Takes the board, row (A-Z) and col (0-25) tile placement and returns 
    // the end row number for a column. This is a char returned as int and 
    // would assume both are in the same case. Used by getColScore().
    int getColEnd(Board* board, char row, int col);

    // If the score is 6, then a Qwirkle has been scored. This will 
    // call the printQwirkle() function and return  a bonus 6 points. 
    // Used by getColScore() and getRowScore().
    int checkQwirklePoints(int score);
};

#endif  // SCORECALCULATOR_H