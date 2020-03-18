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
    Tile();
    bool setState(State state);
    State getState();

private:
    State currentState;
    bool isOccupied;
};


class Board {
public:
    Board();
    std::vector<Tile> grid;
    State currentWinner;
    bool isActive;
};

#endif