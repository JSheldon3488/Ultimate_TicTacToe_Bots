#include "board.h"

Board::Board() {
    currentWinner = State::Empty;
    isActive = true;
    //Set up a empty board
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            grid.emplace_back(Tile(row,col));
        }
    }
}

Tile::Tile(const int row, const int col) : row(row), col(col) {
    currentState = State::Empty;
    isOccupied = false;
}

bool Tile::setState(State state) {
    if (!isOccupied) {
        currentState = state;
        isOccupied = true;
        return true;
    }
    return false;
}

State Tile::getState() { return currentState; }