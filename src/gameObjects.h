#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

#include <vector>
#include <stdlib.h>
#include <iostream>
#include <time.h>

enum State {
    Empty,
    Draw,
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
    State winner;
    bool isActive;
    int moveCounter;
    const int row;
    const int col;
    Tile* winTile_start;
    Tile* winTile_end;
};


class UltimateBoard {
public:
    UltimateBoard();
    std::vector<Board> boards;
    State winner;
    State currentPlayer;
    int last_boardRow;
    int last_boardCol;
    int last_row;
    int last_col;
};

#endif