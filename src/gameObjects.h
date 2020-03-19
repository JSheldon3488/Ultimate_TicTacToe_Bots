#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

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
    bool isOccupied;
    const int row;
    const int col;

private:
    State currentState;
};

/* Borad and UltimateBoard Vector Index Layout
    -------------
    | 0 | 1 | 2 |
    | 3 | 4 | 5 |
    | 6 | 7 | 8 |
    -------------
*/

class Board {
public:
    Board(int row, int col);
    std::vector<Tile> grid;
    State currentWinner;
    bool isActive;
    const int row;
    const int col;
};

class UltimateBoard {
public:
    UltimateBoard();
    std::vector<Board> boards;
    State winner;
    bool gameOver;
};

#endif