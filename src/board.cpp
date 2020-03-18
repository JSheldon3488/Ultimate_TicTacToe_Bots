#include "board.h"

Board::Board() {
    currentWinner = State::Empty;
    isActive = true;
    //Set up a empty board
    for (int i = 0; i < 9; i++) {
        grid.emplace_back(Tile());
    }
}

Tile::Tile() {
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