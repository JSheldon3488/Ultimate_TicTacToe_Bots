#include "gameObjects.h"
#include <iostream>

/***                Ultimate Board implementations                  ***/
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

bool UltimateBoard::checkforWinner() {
    //Check all three rows
    for (int r = 0; r < 3; r++) {
        if (boards[r*3].winner == boards[r*3+1].winner &&
            boards[r*3].winner == boards[r*3+2].winner &&
            boards[r*3].winner != State::Empty) {
                winner = boards[r*3].winner;
                return true;
        }
    }
    //Check all three columns
    for (int r = 0; r < 3; r++) {
        if (boards[r].winner == boards[r+3].winner &&
            boards[r].winner == boards[r+6].winner &&
            boards[r].winner != State::Empty) {
                winner = boards[r].winner;
                return true;
        }
    }
    //Check two diagonals
    if (boards[0].winner == boards[4].winner &&
        boards[0].winner == boards[8].winner &&
        boards[0].winner != State::Empty) {
            winner = boards[0].winner;
            return true;
    }
    else if (boards[6].winner == boards[4].winner &&
            boards[6].winner == boards[2].winner &&
            boards[6].winner != State::Empty) {
                winner = boards[6].winner;
                return true;
    }

    //No Winner - Check for Draws
    bool allFinished = true;
    for (Board board : boards) {
        if (board.winner == State::Empty) {
            allFinished = false;
            break;
        }
    }
    if (allFinished) {
        winner = State::Draw;
        return true;
    }
    return false;
}


/***                Board implementations               ***/
Board::Board(int row, int col) : row(row), col(col) {
    winner = State::Empty;
    isActive = true;
    winTile_start = nullptr;
    winTile_end = nullptr;

    //Set up a empty board
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            tiles.emplace_back(Tile(row,col));
        }
    }
}

State Board::checkforWinner() {
    //Check all three rows
    for (int r = 0; r < 3; r++) {
        if (tiles[r*3].getState() == tiles[r*3+1].getState() &&
            tiles[r*3].getState() == tiles[r*3+2].getState() &&
            tiles[r*3].getState() != State::Empty) {
                winTile_start = &(tiles[r*3]);
                winTile_end =  &(tiles[r*3+2]);
                return tiles[r*3].getState();
        }
    }
    //Check all three columns
    for (int r = 0; r < 3; r++) {
        if (tiles[r].getState() == tiles[r+3].getState() &&
            tiles[r].getState() == tiles[r+6].getState() &&
            tiles[r].getState() != State::Empty) {
                winTile_start = &(tiles[r]);
                winTile_end =  &(tiles[r+6]);
                return tiles[r].getState();
        }
    }
    //Check two diagonals
    if (tiles[0].getState() == tiles[4].getState() &&
        tiles[0].getState() == tiles[8].getState() &&
        tiles[0].getState() != State::Empty) {
            winTile_start = &(tiles[0]);
            winTile_end =  &(tiles[8]);
            return tiles[0].getState();
    }
    else if (tiles[6].getState() == tiles[4].getState() &&
            tiles[6].getState() == tiles[2].getState() &&
            tiles[6].getState() != State::Empty) {
                winTile_start = &(tiles[6]);
                winTile_end =  &(tiles[2]);
                return tiles[6].getState();
    }

    //No Winner - Check for Draws
    bool allFinished = true;
    for (Tile tile : tiles) {
        if (tile.getState() == State::Empty) {
            allFinished = false;
            break;
        }
    }
    if (allFinished) {
        return State::Draw;
    }
    return State::Empty;
}


/***             Tile implementations                ***/
Tile::Tile(const int row, const int col) : row(row), col(col) {
    currentState = State::Empty;
    isOccupied = false;
}

bool Tile::setState(State state) {
    if (currentState == Empty) {
        currentState = state;
        isOccupied = true;
        return true;
    }
    else if (state == Empty) {
        currentState = state;
        isOccupied = false;
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


/***             Move implementations                ***/
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

