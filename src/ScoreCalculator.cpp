#include "../include/ScoreCalculator.h"

ScoreCalculator::ScoreCalculator() {}

ScoreCalculator::ScoreCalculator(const ScoreCalculator& other) {}

ScoreCalculator::ScoreCalculator(ScoreCalculator&& other) {}

ScoreCalculator::~ScoreCalculator() {}

int ScoreCalculator::calculateScore(Board* board, char row, int col) {
    int totalPoints = 0;

    // Get scores.
    int rowScore = getRowScore(board, row, col);
    int colScore = getColScore(board, row, col);

    // Catches tiles with no adjacent tiles.
    if (colScore == 1 && rowScore == 1) {
        totalPoints = 1;

    // Catches tiles added to extend a row only.
    } else if (colScore == 1 && rowScore > 1) {
        totalPoints = rowScore;

    // Catches tiles added to extend a column only.
    } else if (colScore > 1 && rowScore == 1) {
        totalPoints = colScore;

    // Catches tiles added which extend both a row and a column.
    } else {
        totalPoints = rowScore + colScore;
    }

    return totalPoints;
}

int ScoreCalculator::getRowScore(Board* board, char row, int col) {
    int rowScore = 0;

    // Get start of row position, which column does it start at?
    int rowStartPos = getRowStart(board, row, col);

    // Get end of row position, which column does it end at?
    int rowEndPos = getRowEnd(board, row, col);

    // Calculate the row score by taking the start from the end position.
    rowScore = rowEndPos - rowStartPos - 1;

    // Check if its Qwirkle and if so add the bonus points.
    rowScore += checkQwirklePoints(rowScore);

    return rowScore;
}

int ScoreCalculator::getColScore(Board* board, char row, int col) {
    int colScore = 0;

    // Get start of col position, which row does it start at?
    int colStartPos = getColStart(board, row, col);

    // Get end of col position, which row does it end at?
    int colEndPos = getColEnd(board, row, col);

    // Calculate the col score by taking the start from the end position.
    colScore = colEndPos - colStartPos - 1;

    // Check if its Qwirkle and if so add the bonus points.
    colScore += checkQwirklePoints(colScore);

    return colScore;
}

int ScoreCalculator::getRowStart(Board* board, char row, int col) {

    // initialise start column as the current column.
    int rowStartCol = col;

    try {
        // Count back from the tile to find which location is not occupied.
        while (rowStartCol >= board->getMinCol() && 
               board->getTileAtPos(row, rowStartCol) != nullptr) {
            rowStartCol--;
        }
    // In case of out of range exception for board.
    } catch (const std::out_of_range &e) {
        throw std::out_of_range("Program error, couldn't calculate score!");
    }

    return rowStartCol;
}

int ScoreCalculator::getRowEnd(Board* board, char row, int col) {

    // Get the number of columns on the board.
    int boardCols = board->getMaxCol();

    // initialise end column as the current column.
    int rowEndCol = col;

    try {
        // Count forward from the tile to find which location is not occupied.
        while (rowEndCol <= boardCols && 
               board->getTileAtPos(row, rowEndCol) != nullptr) {
            rowEndCol++;
        }
    // In case of out of range exception for board.
    } catch (const std::out_of_range &e) {
        throw std::out_of_range("Error, program couldn't calculate score!");
    }

    return rowEndCol;
}

int ScoreCalculator::getColStart(Board* board, char row, int col) {

    // Initialise start row as the current row.
    int colStartRow = row;

    try {
        // Count up from the tile to find which location is not occupied.
        while (colStartRow >= board->getMinRowChar() && 
               board->getTileAtPos(colStartRow, col) != nullptr) {
            colStartRow--;
        }
    // In case of out of range exception for board.
    } catch (const std::out_of_range &e) {
        throw std::out_of_range("Error, program couldn't calculate score!");
    }

    return colStartRow;
}

int ScoreCalculator::getColEnd(Board* board, char row, int col) {

    // Get the number of rows on the board as a char.
    char boardRows = board->getMaxRowChar();

    // Initialise end row as the current row.
    int colEndRow = row;

    try {
        // Count down from the tile to find which location is not occupied.
        while (colEndRow <= boardRows && 
               board->getTileAtPos(colEndRow, col) != nullptr) {
            colEndRow++;
        }
    // In case of out of range exception for board. 
    }
    catch (const std::out_of_range &e) {
        throw std::out_of_range("Error, program couldn't calculate score!");
    }
    return colEndRow;
}

int ScoreCalculator::checkQwirklePoints(int score) {
    int points = 0;
    if (score == 6) {
        printQwirkle();
        points = 6;
    }
    return points;
}

void ScoreCalculator::printQwirkle() const {
    std::cout << "QWIRKLE!!!" << std::endl;
    std::cout << std::endl;
}