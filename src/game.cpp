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
    // check for winners
    checkforBoardWinner(ultimateBoard.boards[board]);
    checkforUltimateWinner(ultimateBoard);
    // Update active boards
    int activeBoard = row*3 + col;
    setActiveBoards(ultimateBoard,activeBoard);
    // Change Player
    ultimateBoard.currentPlayer = ultimateBoard.currentPlayer == State::Player1 ? State::Player2 : State::Player1;
}

void Game::checkforBoardWinner(Board &board) {
    //Check all three rows
    for (int r = 0; r < 3; r++) {
        if (board.grid[r*3].getState() == board.grid[r*3+1].getState() &&
            board.grid[r*3].getState() == board.grid[r*3+2].getState() &&
            board.grid[r*3].getState() != State::Empty) {
                board.winner = board.grid[r*3].getState();
                return;
        }
    }
    //Check all three columns
    for (int r = 0; r < 3; r++) {
        if (board.grid[r].getState() == board.grid[r+3].getState() &&
            board.grid[r].getState() == board.grid[r+6].getState() &&
            board.grid[r].getState() != State::Empty) {
                board.winner = board.grid[r*3].getState();
                std::cout << "Winner in a column" << std::endl;
                return;
        }
    }
    //Check two diagonals
    if (board.grid[0].getState() == board.grid[4].getState() &&
        board.grid[0].getState() == board.grid[8].getState() &&
        board.grid[0].getState() != State::Empty) {
            board.winner = board.grid[0].getState();
    }
    else if (board.grid[6].getState() == board.grid[4].getState() &&
        board.grid[6].getState() == board.grid[2].getState() &&
        board.grid[6].getState() != State::Empty) {
            board.winner = board.grid[6].getState();
    }
}

void Game::checkforUltimateWinner(UltimateBoard &ultimateBoard) {
        //Check all three rows
    for (int r = 0; r < 3; r++) {
        if (ultimateBoard.boards[r*3].winner == ultimateBoard.boards[r*3+1].winner &&
            ultimateBoard.boards[r*3].winner == ultimateBoard.boards[r*3+2].winner &&
            ultimateBoard.boards[r*3].winner != State::Empty) {
                ultimateBoard.winner = ultimateBoard.boards[r*3].winner;
                std::cout << "Main winner in row" << std::endl;
                gameOver = true;
                return;
        }
    }
    //Check all three columns
    for (int r = 0; r < 3; r++) {
        if (ultimateBoard.boards[r].winner == ultimateBoard.boards[r+3].winner &&
            ultimateBoard.boards[r].winner == ultimateBoard.boards[r*6].winner &&
            ultimateBoard.boards[r].winner != State::Empty) {
                ultimateBoard.winner = ultimateBoard.boards[r].winner;
                std::cout << "Main winner in col" << std::endl;
                gameOver = true;
                return;
        }
    }
    //Check two diagonals
    if (ultimateBoard.boards[0].winner == ultimateBoard.boards[4].winner &&
        ultimateBoard.boards[0].winner == ultimateBoard.boards[8].winner &&
        ultimateBoard.boards[0].winner != State::Empty) {
            ultimateBoard.winner = ultimateBoard.boards[0].winner;
            gameOver = true;
    }
    else if (ultimateBoard.boards[6].winner == ultimateBoard.boards[4].winner &&
        ultimateBoard.boards[6].winner == ultimateBoard.boards[2].winner &&
        ultimateBoard.boards[6].winner != State::Empty) {
            ultimateBoard.winner = ultimateBoard.boards[6].winner;
            gameOver = true;
    }
}

void Game::setActiveBoards(UltimateBoard &ultimateBoard, int activeBoard) {
    // If board sent to is already complete set all unfinished boards to active
    if (ultimateBoard.boards[activeBoard].winner != State::Empty) {
        for (int i = 0; i < 9; i++) {
            if (ultimateBoard.boards[i].winner == State::Empty) {
                ultimateBoard.boards[i].isActive = true;
            }
            else { ultimateBoard.boards[i].isActive = false; }
        }
    }
    // If board sent to is not complete set it to active and all other inactive
    else {
        for (int i = 0; i < 9; i++) {
            ultimateBoard.boards[i].isActive = i == activeBoard ? true : false;
        }
    }
}