#!/bin/bash

# Milestone 1: Test cases for group component

# Set up function to print results.

print_result() {
    if [ "$1" == "" ]
    then
        echo -e "\033[0,32mPassed!\033[0m"
    else 
        echo -e "\033[0,31mFailed!\033[0m"
    fi
}

# First compile the program.

make

# Execute tests with compiled program.

echo "Program testing"

# Input tests.

TEST_NAME="Testing: Menu, select credits - credits.input"
./qwirkle -T < tests/credits.input > tests/credits.gameout 
TEST=$(diff -w -B tests/credits.output tests/credits.gameout)
echo $TEST_NAME
print_result $TEST

TEST_NAME="Testing: Menu, select new game - newGame.input"
./qwirkle -T < tests/newGame.input > tests/newGame.gameout 
TEST=$(diff -w tests/newGame.output tests/newGame.gameout)
echo $TEST_NAME
print_result $TEST

TEST_NAME="Testing: Menu, select exit game - quit.input"
./qwirkle -T < tests/quit.input > tests/quit.gameout 
TEST=$(diff -w -B tests/quit.output tests/quit.gameout)
echo $TEST_NAME
print_result $TEST

TEST_NAME="Testing: Menu, enter EOF - menuEOF.input"
./qwirkle -T < tests/menuEOF.input > tests/menuEOF.gameout
TEST=$(diff -w -B tests/menuEOF.output tests/menuEOF.gameout)
echo $TEST_NAME
print_result $TEST

TEST_NAME="Testing: During turn, enter EOF - turnEOF.input"
./qwirkle -T < tests/turnEOF.input > tests/turnEOF.gameout
TEST=$(diff -w -B tests/turnEOF.output tests/turnEOF.gameout)
echo $TEST_NAME
print_result $TEST

TEST_NAME="Testing: Invalid player entries - playerError.input"
./qwirkle -T < tests/playerError.input > tests/playerError.gameout
TEST=$(diff -w -B tests/playerError.output tests/playerError.gameout)
echo $TEST_NAME
print_result $TEST

# Tile placement and scoring tests.

TEST_NAME="Testing: Top left corner place tiles - corner1.input"
./qwirkle -T < tests/corner1.input > tests/corner1.gameout 
TEST=$(diff -w -B tests/corner1.output tests/corner1.gameout)
echo $TEST_NAME
print_result $TEST

TEST_NAME="Testing: Top right corner place tiles - corner2.input"
./qwirkle -T < tests/corner2.input > tests/corner2.gameout 
TEST=$(diff -w -B tests/corner2.output tests/corner2.gameout)
echo $TEST_NAME
print_result $TEST

TEST_NAME="Testing: Bottom left corner place tiles - corner3.input"
./qwirkle -T < tests/corner3.input > tests/corner3.gameout 
TEST=$(diff -w -B tests/corner3.output tests/corner3.gameout)
echo $TEST_NAME
print_result $TEST

TEST_NAME="Testing: Bottom right corner place tiles - corner4.input"
./qwirkle -T < tests/corner4.input > tests/corner4.gameout 
TEST=$(diff -w -B tests/corner4.output tests/corner4.gameout)
echo $TEST_NAME
print_result $TEST

TEST_NAME="Testing: Qwirkle row scoring - qwirkleRow.input"
./qwirkle -T < tests/qwirkleRow.input > tests/qwirkleRow.gameout 
TEST=$(diff -w -B tests/qwirkleRow.output tests/qwirkleRow.gameout)
echo $TEST_NAME
print_result $TEST

TEST_NAME="Testing: Qwirkle column scoring - qwirkleColumn.input"
./qwirkle -T < tests/qwirkleColumn.input > tests/qwirkleColumn.gameout 
TEST=$(diff -w -B tests/qwirkleColumn.output tests/qwirkleColumn.gameout) 
echo $TEST_NAME
print_result $TEST

TEST_NAME="Testing: Dual Qwirkle scoring - dualQwirkle.input"
./qwirkle -T < tests/dualQwirkle.input > tests/dualQwirkle.gameout
TEST=$(diff -w -B tests/dualQwirkle.output tests/dualQwirkle.gameout)
echo $TEST_NAME
print_result $TEST

# Validation testing of tile placement.

TEST_NAME="Testing: Qwirkle tile placement - tilePlacement1.input"
./qwirkle -T < tests/tilePlacement1.input > tests/tilePlacement1.gameout
TEST=$(diff -w -B tests/tilePlacement1.output tests/tilePlacement1.gameout)
echo $TEST_NAME
print_result $TEST

TEST_NAME="Testing: Qwirkle tile placement - tilePlacement2.input"
./qwirkle -T < tests/tilePlacement2.input > tests/tilePlacement2.gameout
TEST=$(diff -w -B tests/tilePlacement2.output tests/tilePlacement2.gameout)
echo $TEST_NAME
print_result $TEST

TEST_NAME="Testing: Qwirkle tile placement - tilePlacement3.input"
./qwirkle -T < tests/tilePlacement3.input > tests/tilePlacement3.gameout
TEST=$(diff -w -B tests/tilePlacement3.output tests/tilePlacement3.gameout)
echo $TEST_NAME
print_result $TEST

TEST_NAME="Testing: Qwirkle tile placement - tilePlacement4.input"
./qwirkle -T < tests/tilePlacement4.input > tests/tilePlacement4.gameout
TEST=$(diff -w -B tests/tilePlacement4.output tests/tilePlacement4.gameout)
echo $TEST_NAME
print_result $TEST

# LinkedList testing of Hand and TileBag.

TEST_NAME="Testing: Taking from start of hand - handListStart.input"
./qwirkle -T < tests/handListStart.input > tests/handListStart.gameout
TEST=$(diff -w -B tests/handListStart.output tests/handListStart.gameout)
echo $TEST_NAME
print_result $TEST

TEST_NAME="Testing: Taking from end of hand - handListEnd.input"
./qwirkle -T < tests/handListEnd.input > tests/handListEnd.gameout
TEST=$(diff -w -B tests/handListEnd.output tests/handListEnd.gameout)
echo $TEST_NAME
print_result $TEST

TEST_NAME="Testing: Take first matching tile from hand when duplicates - handListDuplicate.input"
./qwirkle -T < tests/handListDuplicate.input > tests/handListDuplicate.gameout
TEST=$(diff -w -B tests/handListDuplicate.output tests/handListDuplicate.gameout)
echo $TEST_NAME
print_result $TEST

TEST_NAME="Testing: Replace tile when tile bag is empty - replaceEmptyTileBag.input"
./qwirkle -T < tests/replaceEmptyTileBag.input > tests/replaceEmptyTileBag.gameout
TEST=$(diff -w -B tests/replaceEmptyTileBag.output tests/replaceEmptyTileBag.gameout)
echo $TEST_NAME
print_result $TEST

# Full game testing.

TEST_NAME="Testing: Run full game (p1 win) - fullGameP1.input"
./qwirkle -T < tests/fullGameP1.input > tests/fullGameP1.gameout
TEST=$(diff -w -B tests/fullGameP1.output tests/fullGameP1.gameout)
echo $TEST_NAME
print_result $TEST

TEST_NAME="Testing: Run full game (p2 win) - fullGameP2.input"
./qwirkle -T < tests/fullGameP2.input > tests/fullGameP2.gameout
TEST=$(diff -w -B tests/fullGameP2.output tests/fullGameP2.gameout)
echo $TEST_NAME
print_result $TEST

TEST_NAME="Testing: Run full game (Draw) - fullGameDraw.input"
./qwirkle -T < tests/fullGameDraw.input > tests/fullGameDraw.gameout
TEST=$(diff -w -B tests/fullGameDraw.output tests/fullGameDraw.gameout)
echo $TEST_NAME
print_result $TEST

# Skip turn tests.

TEST_NAME="Testing: Skip turn fail when tile bag not empty - skipNotAvailable.input"
./qwirkle -T < tests/skipNotAvailable.input > tests/skipNotAvailable.gameout
TEST=$(diff -w -B tests/skipNotAvailable.output tests/skipNotAvailable.gameout)
echo $TEST_NAME
print_result $TEST

TEST_NAME="Testing: Skip turn success when tile bag empty - skipAvailable.input"
./qwirkle -T < tests/skipAvailable.input > tests/skipAvailable.gameout
TEST=$(diff -w -B tests/skipAvailable.output tests/skipAvailable.gameout)
echo $TEST_NAME
print_result $TEST

TEST_NAME="Testing: Skip turn for both players and game ends - skipGameEnds.input"
./qwirkle -T < tests/skipGameEndsP1Win.input > tests/skipGameEndsP1Win.gameout
TEST=$(diff -w -B tests/skipGameEndsP1Win.output tests/skipGameEndsP1Win.gameout)
echo $TEST_NAME
print_result $TEST

# Save game tests.

TEST_NAME="Testing: Save a blank game - saveGameNew.input"
./qwirkle -T < tests/saveGameNew.input > tests/saveGameNew.gameout
TEST=$(diff -w -B tests/saveGameNew.output tests/saveGameNew.gameout)
echo $TEST_NAME
print_result $TEST
TEST_NAME="Testing: Save a blank game, check the save file - saveGameNew.expsave"
TEST=$(diff -w -B tests/saveGameNew.save tests/saveGameNew.expsave)
echo $TEST_NAME
print_result $TEST

TEST_NAME="Testing: Save a partial game - saveGamePartial.input"
./qwirkle -T < tests/saveGamePartial.input > tests/saveGamePartial.gameout
TEST=$(diff -w -B tests/saveGamePartial.output tests/saveGamePartial.gameout)
echo $TEST_NAME
print_result $TEST
TEST_NAME="Testing: Save a partial game, check the save file - saveGamePartial.expsave"
TEST=$(diff -w -B tests/saveGamePartial.save tests/saveGamePartial.expsave)
echo $TEST_NAME
print_result $TEST

TEST_NAME="Testing: Save a game with an invalid location - saveGameInvalid.input"
./qwirkle -T < tests/saveGameInvalid.input > tests/saveGameInvalid.gameout
TEST=$(diff -w -B tests/saveGameInvalid.output tests/saveGameInvalid.gameout)
echo $TEST_NAME
print_result $TEST

# Load game tests.

TEST_NAME="Testing: Load a game, P1 active player - loadGameValidP1.input"
./qwirkle -T < tests/loadGameValidP1.input > tests/loadGameValidP1.gameout
TEST=$(diff -w -B tests/loadGameValidP1.output tests/loadGameValidP1.gameout)
echo $TEST_NAME
print_result $TEST

TEST_NAME="Testing: Load a game, P2 active player - loadGameValidP2.input"
./qwirkle -T < tests/loadGameValidP2.input > tests/loadGameValidP2.gameout
TEST=$(diff -w -B tests/loadGameValidP2.output tests/loadGameValidP2.gameout)
echo $TEST_NAME
print_result $TEST

TEST_NAME="Testing: Load a game, no save file exists - loadGameNoSave.input"
./qwirkle -T < tests/loadGameNoSave.input > tests/loadGameNoSave.gameout
TEST=$(diff -w -B tests/loadGameNoSave.output tests/loadGameNoSave.gameout)
echo $TEST_NAME
print_result $TEST

TEST_NAME="Testing: Load a game, invalid save file exists - loadGameInvalid.input"
./qwirkle -T < tests/loadGameInvalid.input > tests/loadGameInvalid.gameout
TEST=$(diff -w -B tests/loadGameInvalid.output tests/loadGameInvalid.gameout)
echo $TEST_NAME
print_result $TEST