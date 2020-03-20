#include "game.h"


Game::Game() {
    UltimateBoard boards;
    gameOver = false;
    currentPlayer = State::Player1;
    bot = false;
}

// Add Controller once its ready
void Game::Run(Renderer &renderer) {
    //Test Run
    boards.boards[0].grid[0].setState(State::Player1);
    boards.boards[0].grid[1].setState(State::Player2);
    boards.boards[1].grid[0].setState(State::Player1);
    boards.boards[1].grid[1].setState(State::Player2);
    boards.boards[7].grid[5].setState(State::Player1);
    boards.boards[7].grid[6].setState(State::Player2);
    boards.boards[7].isActive = false;
    renderer.Render(boards);

    // Render Original Board
    // Loop until game is over
        // Loop waiting for valid move
        // Update Game State
        // Render new board
}

void update(UltimateBoard &boards, int board, int row, int col) {
    // Update boards
    // check for winners
    // update winner variables
    return;
}

bool isValidMove(UltimateBoard &boards, int board, int row, int col) {
    return true;
}

bool checkforBoardWinner(Board &board) {
    return true;
}

bool checkforUltimateWinner(UltimateBoard &boards) {
    return true;
}