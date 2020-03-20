#include "game.h"
#include <iostream>

Game::Game() {
    UltimateBoard boards;
    gameOver = false;
    currentPlayer = State::Player1;
    bot = false;
}

// Add Controller once its ready
void Game::Run(Renderer &renderer, Controller &controller) {
    //Test Run
    boards.boards[0].grid[0].setState(State::Player1);
    boards.boards[0].grid[1].setState(State::Player2);
    boards.boards[1].grid[0].setState(State::Player1);
    boards.boards[1].grid[1].setState(State::Player2);
    boards.boards[7].grid[5].setState(State::Player1);
    boards.boards[7].grid[6].setState(State::Player2);
    boards.boards[7].isActive = false;
    renderer.Render(boards);

    //Test Controller
    while (true) {
        std::map<std::string, int> click = controller.HandleInput();
        if (click["board"] != -2 || click["row"] != -2 || click["col"] != -2) {
            std::cout << "Board: " << click["board"] << ", Row: " << click["row"] << ", Col: " << click["col"] << std::endl;
            std::cout << "X: " << click["x"] << ", Y: " << click["y"] << std::endl;
        }
    }
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