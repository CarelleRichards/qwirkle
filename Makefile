.default: all

all: qwirkle

clean:
	rm -rf qwirkle src/*.o *.dSYM

qwirkle: src/Tile.o src/qwirkle.o src/FileHandler.o src/Hand.o src/PlaceChecker.o src/TileBag.o src/Node.o src/LinkedList.o src/Board.o src/Player.o src/Game.o src/Controller.o src/Validator.o src/ScoreCalculator.o src/FileHandler.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

src/%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^

# disable all warnings
CXXFLAGS += -w
