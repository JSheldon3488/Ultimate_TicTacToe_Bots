#include "gameObjects.h"

UltimateBoard::UltimateBoard() {
    winner = State::Empty;

    //Set up who goes first
    srand(time(NULL));
    currentPlayer = (rand() %2) + 1 == 1 ? State::Player1 : State::Player2;
    
    //Set up board
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            boards.emplace_back(Board(row,col));
        }
    }
}

Board::Board(int row, int col) : row(row), col(col) {
    winner = State::Empty;
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