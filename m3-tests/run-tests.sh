# Milestone 1: Test cases for individual component

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

echo "Program testing for Milestone 3"

# Enhanced menu for new game test.

TEST_NAME="Testing: Menu, select new game - newGameMenu.input"
./qwirkle -T -E < m3-tests/newGameMenu.input > m3-tests/newGameMenu.gameout 
TEST=$(diff -w -B m3-tests/newGameMenu.output m3-tests/newGameMenu.gameout)
echo $TEST_NAME
print_result $TEST

# Reserved name for COMPUTER test.

TEST_NAME="Testing: Reserved name for COMPUTER - computerReservedName.input"
./qwirkle -T -E < m3-tests/computerReservedName.input > m3-tests/computerReservedName.gameout 
TEST=$(diff -w -B m3-tests/computerReservedName.output m3-tests/computerReservedName.gameout)
echo $TEST_NAME
print_result $TEST

# Single game mode round test.
#   Game should function the same as Milestone 2 but 
#   turns should alternate between player 1 and COMPUTER.

TEST_NAME="Testing: Single game mode, round - singleRound.input"
./qwirkle -T -E < m3-tests/singleRound.input > m3-tests/singleRound.gameout 
TEST=$(diff -w -B m3-tests/singleRound.output m3-tests/singleRound.gameout)
echo $TEST_NAME
print_result $TEST

# Dual game mode round test.
#   Game should function the same as Milestone 2.
TEST_NAME="Testing: Dual game mode, round - dualRound.input"
./qwirkle -T -E < m3-tests/dualRound.input > m3-tests/dualRound.gameout 
TEST=$(diff -w -B m3-tests/dualRound.output m3-tests/dualRound.gameout)
echo $TEST_NAME
print_result $TEST

# Triple game mode round test.
#   Game should function the same as Milestone 2 but 
#   turns should alternate between player 1, 2 and 3.

TEST_NAME="Testing: Triple game mode, round - tripleRound.input"
./qwirkle -T -E < m3-tests/tripleRound.input > m3-tests/tripleRound.gameout 
TEST=$(diff -w -B m3-tests/tripleRound.output m3-tests/tripleRound.gameout)
echo $TEST_NAME
print_result $TEST

# Quad game mode round test.
#   Game should function the same as Milestone 2 but 
#   turns should alternate between player 1, 2, 3 and 4.

TEST_NAME="Testing: Quad game mode, round - quadRound.input"
./qwirkle -T -E < m3-tests/quadRound.input > m3-tests/quadRound.gameout 
TEST=$(diff -w -B m3-tests/quadRound.output m3-tests/quadRound.gameout)
echo $TEST_NAME
print_result $TEST

# Help! from main menu test.

TEST_NAME="Testing: Help from main menu - helpMainMenu.input"
./qwirkle -T -E < m3-tests/helpMainMenu.input > m3-tests/helpMainMenu.gameout 
TEST=$(diff -w -B m3-tests/helpMainMenu.output m3-tests/helpMainMenu.gameout)
echo $TEST_NAME
print_result $TEST

# Help! from new game menu test.

TEST_NAME="Testing: Help from new game menu - helpNewGameMenu.input"
./qwirkle -T -E < m3-tests/helpNewGameMenu.input > m3-tests/helpNewGameMenu.gameout 
TEST=$(diff -w -B m3-tests/helpNewGameMenu.output m3-tests/helpNewGameMenu.gameout)
echo $TEST_NAME
print_result $TEST

# Help! from name input test.

TEST_NAME="Testing: Help from from name input - helpNameInput.input"
./qwirkle -T -E < m3-tests/helpNameInput.input > m3-tests/helpNameInput.gameout 
TEST=$(diff -w -B m3-tests/helpNameInput.output m3-tests/helpNameInput.gameout)
echo $TEST_NAME
print_result $TEST

# Help! during turn test.

TEST_NAME="Testing: Help during turn - helpTurn.input"
./qwirkle -T -E < m3-tests/helpTurn.input > m3-tests/helpTurn.gameout 
TEST=$(diff -w -B m3-tests/helpTurn.output m3-tests/helpTurn.gameout)
echo $TEST_NAME
print_result $TEST

# Help! during load game test.

TEST_NAME="Testing: Help during load game - helpLoadGame.input"
./qwirkle -E < m3-tests/helpLoadGame.input > m3-tests/helpLoadGame.gameout 
TEST=$(diff -w -B m3-tests/helpLoadGame.output m3-tests/helpLoadGame.gameout)
echo $TEST_NAME
print_result $TEST

# Help! during load game test (test flag).

TEST_NAME="Testing: Help during load game - helpLoadGameTest.input"
./qwirkle -T -E < m3-tests/helpLoadGameTest.input > m3-tests/helpLoadGameTest.gameout 
TEST=$(diff -w -B m3-tests/helpLoadGameTest.output m3-tests/helpLoadGameTest.gameout)
echo $TEST_NAME
print_result $TEST

# Three way tie test.

TEST_NAME="Testing: Three way tie - threeWayTie.input"
./qwirkle -T -E < m3-tests/threeWayTie.input > m3-tests/threeWayTie.gameout 
TEST=$(diff -w -B m3-tests/threeWayTie.output m3-tests/threeWayTie.gameout)
echo $TEST_NAME
print_result $TEST

# Four way tie test.

TEST_NAME="Testing: Four way tie - fourWayTie.input"
./qwirkle -T -E < m3-tests/fourWayTie.input > m3-tests/fourWayTie.gameout 
TEST=$(diff -w -B m3-tests/fourWayTie.output m3-tests/fourWayTie.gameout)
echo $TEST_NAME
print_result $TEST

# Save game single mode test.

TEST_NAME="Testing: Save game single mode - saveSingle.input"
./qwirkle -T -E < m3-tests/saveSingle.input > m3-tests/saveSingle.gameout 
TEST=$(diff -w -B m3-tests/saveSingle.output m3-tests/saveSingle.gameout)
echo $TEST_NAME
print_result $TEST
TEST_NAME="Testing: Save game single mode (save file) - saveSingle.expsave"
TEST=$(diff -w -B m3-tests/saveSingle.expsave m3-tests/saveSingle.save)
echo $TEST_NAME
print_result $TEST

# Save game dual mode test.

TEST_NAME="Testing: Save game dual mode - saveDual.input"
./qwirkle -T -E < m3-tests/saveDual.input > m3-tests/saveDual.gameout 
TEST=$(diff -w -B m3-tests/saveDual.output m3-tests/saveDual.gameout)
echo $TEST_NAME
print_result $TEST
TEST_NAME="Testing: Save game dual mode (save file) - saveDual.expsave"
TEST=$(diff -w -B m3-tests/saveDual.expsave m3-tests/saveDual.save)
echo $TEST_NAME
print_result $TEST

# Save game triple mode test.

TEST_NAME="Testing: Save game triple mode - saveTriple.input"
./qwirkle -T -E < m3-tests/saveTriple.input > m3-tests/saveTriple.gameout 
TEST=$(diff -w -B m3-tests/saveTriple.output m3-tests/saveTriple.gameout)
echo $TEST_NAME
print_result $TEST
TEST_NAME="Testing: Save game triple mode (save file) - saveTriple.expsave"
TEST=$(diff -w -B m3-tests/saveTriple.expsave m3-tests/saveTriple.save)
echo $TEST_NAME
print_result $TEST

# Save game quad mode test.

TEST_NAME="Testing: Save game quad mode - saveQuad.input"
./qwirkle -T -E < m3-tests/saveQuad.input > m3-tests/saveQuad.gameout 
TEST=$(diff -w -B m3-tests/saveQuad.output m3-tests/saveQuad.gameout)
echo $TEST_NAME
print_result $TEST
TEST_NAME="Testing: Save game quad mode (save file) - saveQuad.expsave"
TEST=$(diff -w -B m3-tests/saveQuad.expsave m3-tests/saveQuad.save)
echo $TEST_NAME
print_result $TEST

# Load game single mode test.

TEST_NAME="Testing: Load game single mode - loadSingle.input"
./qwirkle -T -E < m3-tests/loadSingle.input > m3-tests/loadSingle.gameout 
TEST=$(diff -w -B m3-tests/loadSingle.output m3-tests/loadSingle.gameout)
echo $TEST_NAME
print_result $TEST

# Load game dual mode test.

TEST_NAME="Testing: Load game dual mode - loadDual.input"
./qwirkle -T -E < m3-tests/loadDual.input > m3-tests/loadDual.gameout 
TEST=$(diff -w -B m3-tests/loadDual.output m3-tests/loadDual.gameout)
echo $TEST_NAME
print_result $TEST

# Load game triple mode test.

TEST_NAME="Testing: Load game triple mode - loadTriple.input"
./qwirkle -T -E < m3-tests/loadTriple.input > m3-tests/loadTriple.gameout 
TEST=$(diff -w -B m3-tests/loadTriple.output m3-tests/loadTriple.gameout)
echo $TEST_NAME
print_result $TEST

# Load game quad mode test.

TEST_NAME="Testing: Load game quad mode - loadQuad.input"
./qwirkle -T -E < m3-tests/loadQuad.input > m3-tests/loadQuad.gameout 
TEST=$(diff -w -B m3-tests/loadQuad.output m3-tests/loadQuad.gameout)
echo $TEST_NAME
print_result $TEST

# Computer places highest scoring tile test.

TEST_NAME="Testing: Computer places highest scoring tile - computerPlaceTile.input"
./qwirkle -T -E < m3-tests/computerPlaceTile.input > m3-tests/computerPlaceTile.gameout 
TEST=$(diff -w -B m3-tests/computerPlaceTile.output m3-tests/computerPlaceTile.gameout)
echo $TEST_NAME
print_result $TEST

# Computer will replace if no tiles to play test.

TEST_NAME="Testing: Computer replaces if no tiles to play - computerReplace.input"
./qwirkle -T -E < m3-tests/computerReplace.input > m3-tests/computerReplace.gameout 
TEST=$(diff -w -B m3-tests/computerReplace.output m3-tests/computerReplace.gameout)
echo $TEST_NAME
print_result $TEST

# Computer will skip if no tiles to play or replace test.

TEST_NAME="Testing: Computer skips if no tiles to play - computerSkip.input"
./qwirkle -T -E < m3-tests/computerSkip.input > m3-tests/computerSkip.gameout 
TEST=$(diff -w -B m3-tests/computerSkip.output m3-tests/computerSkip.gameout)
echo $TEST_NAME
print_result $TEST