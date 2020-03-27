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
    moveCounter = 0;
    winTile_start = nullptr;
    winTile_end = nullptr;

    //Set up a empty board
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            tiles.emplace_back(Tile(row,col));
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

// Default Move Constructor
Move::Move() {
    ultimate_row = -2;
    ultimate_col = -2;
    board_row = -2;
    board_col = -2;
}

// Simple Move object constructor that initializes all the variables for this Move
Move::Move(int ultimate_row, int ultimate_col, int board_row, int board_col) :
            ultimate_row(ultimate_row), ultimate_col(ultimate_col), board_row(board_row), board_col(board_col) {}

bool Move::operator==(const Move& rhs) {
    if (this->ultimate_row == rhs.ultimate_row &&
        this->ultimate_col == rhs.ultimate_col &&
        this->board_row == rhs.board_row &&
        this->board_col == rhs.board_col) {
            return true;
        }
    return false;
}