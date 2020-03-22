#include "game.h"
#include <iostream>
#include <thread>

Game::Game() {
    UltimateBoard ultimateBoard;
    gameOver = false;
    bot = false;
}


void Game::Run(Renderer &renderer, Controller &controller) {
    // Render Original Board
    renderer.Render(ultimateBoard);

    // Game Loop
    while(!gameOver) {
        // Get User Input
        controller.hasMoved = false;
        auto click = controller.HandleInput(ultimateBoard);

        // Update Game State
        update(ultimateBoard, click["board"], click["row"], click["col"]);


        // Render new board
        renderer.Render(ultimateBoard);
    }
}

void Game::update(UltimateBoard &ultimateBoard, int board, int row, int col) {
    int lastPlayed = (row*3 + col);
    // check for winners
    bool win = checkforBoardWinner(ultimateBoard.boards[lastPlayed]);
    bool overallWinner = checkforUltimateWinner(ultimateBoard);
    // update winner variables
    if (win) {
        ultimateBoard.boards[lastPlayed].winner = ultimateBoard.currentPlayer;
    }
    // if overall winer set game Over else update active boards and change player
    if (overallWinner) {
        gameOver = true;
    }
    else {
        setActiveBoards();
    }

    return;
}

bool Game::checkforBoardWinner(Board &board) {
    //Check all three rows
    //Check all three columns
    //Check two diagonals
    return true;
}

bool Game::checkforUltimateWinner(UltimateBoard &ultimateBoard) {
    //Check all three rows
    //Check all three columns
    //Check two diagonals
    return false;
}