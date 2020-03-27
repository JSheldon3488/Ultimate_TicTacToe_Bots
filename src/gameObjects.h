#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

#include <vector>
#include <stdlib.h>
#include <iostream>
#include <time.h>

/* States are used by Tiles, Boards, and UltimateBoards to signify the status of an object member */
enum State {
    Empty,
    Draw,
    Player1,
    Player2,
};

/* Move class is used for communicating CPU and player moves to other objects */
class Move {
public:
    Move();
    Move(int ultimate_row, int ultimate_col, int boad_row, int board_col);
    bool operator==(const Move& rhs);
    int ultimate_row;
    int ultimate_col;
    int board_row;
    int board_col;
};

/* Tiles are the individual objects stored in boards that players can make moves in.
   Each tile can only be set once, and each tile is referred to by a row and col in its board */
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

/* Boards are just like individual Tic-Tac-Toe games. Each one is referred to by its row and col inside the ultimate board.*/
class Board {
public:
    Board(int row, int col);
    const int row;
    const int col;
    std::vector<Tile> tiles;
    State winner;
    bool isActive;
    int moveCounter; //Used for Checking Draw
    // Tile pointers are used to know where to Render the Win line
    Tile* winTile_start;
    Tile* winTile_end;
};

/* UltimateBoard is the container for all the individual boards. There is only one per game. */
class UltimateBoard {
public:
    UltimateBoard();
    std::vector<Board> boards;
    State winner;
    State currentPlayer;
    Move last_CPU_move;
};

#endif