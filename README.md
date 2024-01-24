# Qwirkle console program
## Overview
- A 2-player text-based version of the board game [Qwirkle](https://www.ultraboardgames.com/qwirkle/game-rules.php).
- Developed as part of a team. 
- Written in C++14 and makes use of:
  - ADTs
  - Linked lists (coded from scratch)
  - Pointers
  - Dynamic memory management
  - File processing
  - Program state management
  - Exception handling
- Tests were performed using diff to compare the actual vs. expected output.

## Running the program (CLI)
Clone the repo and navigate to the root directory. Compile using:
```
make
```
Run using:
```
./qwirkle
```
There is an enhanced version of the game that includes a 3-4 player mode, player vs. computer and help prompts when the "Help!" command is entered. Run the enhanced version using:
```
./qwirkle -E
```
Tests were completed using a diff. To run these tests, use: 
```
./tests/run-tests.sh  
```
## Gameplay screenshot

<img src="https://github.com/CarelleRichards/qwirkle/assets/137973963/75cd637f-eee8-4d9d-8335-c212eb69bf57" width=500px>
