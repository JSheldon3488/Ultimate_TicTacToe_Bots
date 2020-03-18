#ifndef BOARD_H
#define BOARD_H

#include <vector>

enum State {
    Empty,
    Player1,
    Player2,
};


class Tile {
public:
    Tile(const int row, const int col);
    bool setState(State state);
    State getState();
    const int row;
    const int col;
    bool isOccupied;

private:
    State currentState;
};


class Board {
public:
    Board();
    std::vector<Tile> grid;
    State currentWinner;
    bool isActive;
};

#endif