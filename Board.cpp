#include "Board.h"
#include <map>

// this function checks if that grid square is stepping on a snake or ladder.
// Return new pos if so, otherwise return same.
const int Board::returnGrid(int currentGrid) {
	// check if on a Snake
	int newGrid{ searchDictionaries(currentGrid) };	// will evaluate to 0 if none found
	if (newGrid)
		return newGrid;
	return currentGrid;

}
const int Board::searchDictionaries(int numToFind) {
	auto value{ Snakes.find(numToFind) };
	if (value == Snakes.end()) {		// not on a snake
		value = Ladders.find(numToFind);	// check for ladders
		if (value == Ladders.end())	// not on a ladder
			return 0;	// 0 is not a valid board Position in my game.
	}

	// updates the steppedOnInfo with snake = true if this value is less
	// than numToFind, which means player went backwards.
	steppedOnInfo.snake = value->second < numToFind;
	if (steppedOnInfo.snake){
		steppedOnInfo.index = KeyToIndexSnakes[value->first];
	}
	return value->second;
}

