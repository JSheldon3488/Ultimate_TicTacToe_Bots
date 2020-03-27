#include "game.h"
#include <iostream>
#include <thread>

Game::Game() {
    gameOver = false;
    vsCPU = true;
}


void Game::Run(Renderer &renderer, Controller &controller) {
    // Render Original Board
    renderer.Render(ultimateBoard, gameOver, ultimateBoard.winner);
    Move move;

    // Game Loop
    while(!gameOver) {
        // CPU turn path
        if (vsCPU && ultimateBoard.currentPlayer == State::Player2) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            move = bot.makeMove(ultimateBoard);
            ultimateBoard.last_CPU_move = move;
            update(ultimateBoard, move);
            renderer.Render(ultimateBoard, gameOver, ultimateBoard.winner);
        }

        // User turn path
        else {
            // Get User Input
            controller.hasMoved = false;
            move = controller.HandleInput(ultimateBoard);

            if (move.ultimate_row == -1 && move.ultimate_col == -1 && move.board_row == -1 && move.board_col == -1){
                gameOver = true;
            }
            else {
                // Update Game State
                update(ultimateBoard, move);
                // Render new board
                renderer.Render(ultimateBoard, gameOver, ultimateBoard.winner);
            }
        }
    }

    // Let the player see the end of game state (replace with Menu)
    if (move.ultimate_row != -1 && move.ultimate_col != -1 && move.board_row != -1 && move.board_col != -1) {
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}

void Game::update(UltimateBoard &ultimateBoard, Move &move) {
    // Make move
    ultimateBoard.boards[move.ultimate_row*3 + move.ultimate_col].tiles[(move.board_row*3 + move.board_col)].setState(ultimateBoard.currentPlayer);
    ultimateBoard.boards[move.ultimate_row*3 + move.ultimate_col].moveCounter += 1;
    
    // check for winners and draw
    checkforBoardWinner(ultimateBoard.boards[move.ultimate_row*3 + move.ultimate_col]);
    checkforUltimateWinner(ultimateBoard);
    
    // Update active boards
    int activeBoard = move.board_row*3 + move.board_col;
    setActiveBoards(ultimateBoard,activeBoard);
    
    // Change Player
    ultimateBoard.currentPlayer = ultimateBoard.currentPlayer == State::Player1 ? State::Player2 : State::Player1;
}

void Game::checkforBoardWinner(Board &board) {
    //Check all three rows
    for (int r = 0; r < 3; r++) {
        if (board.tiles[r*3].getState() == board.tiles[r*3+1].getState() &&
            board.tiles[r*3].getState() == board.tiles[r*3+2].getState() &&
            board.tiles[r*3].getState() != State::Empty) {
                board.winner = board.tiles[r*3].getState();
                board.winTile_start = &(board.tiles[r*3]);
                board.winTile_end = &(board.tiles[r*3+2]);
                return;
        }
    }
    //Check all three columns
    for (int r = 0; r < 3; r++) {
        if (board.tiles[r].getState() == board.tiles[r+3].getState() &&
            board.tiles[r].getState() == board.tiles[r+6].getState() &&
            board.tiles[r].getState() != State::Empty) {
                board.winner = board.tiles[r].getState();
                board.winTile_start = &(board.tiles[r]);
                board.winTile_end = &(board.tiles[r+6]);
                return;
        }
    }
    //Check two diagonals
    if (board.tiles[0].getState() == board.tiles[4].getState() &&
        board.tiles[0].getState() == board.tiles[8].getState() &&
        board.tiles[0].getState() != State::Empty) {
            board.winner = board.tiles[0].getState();
            board.winTile_start = &(board.tiles[0]);
            board.winTile_end = &(board.tiles[8]);
            return;
    }
    else if (board.tiles[6].getState() == board.tiles[4].getState() &&
        board.tiles[6].getState() == board.tiles[2].getState() &&
        board.tiles[6].getState() != State::Empty) {
            board.winner = board.tiles[6].getState();
            board.winTile_start = &(board.tiles[6]);
            board.winTile_end = &(board.tiles[2]);
            return;
    }

    // No Winner - Check for Draw
    if (board.moveCounter == 9) {
        board.winner = State::Draw;
    }
}

void Game::checkforUltimateWinner(UltimateBoard &ultimateBoard) {
    //Check all three rows
    for (int r = 0; r < 3; r++) {
        if (ultimateBoard.boards[r*3].winner == ultimateBoard.boards[r*3+1].winner &&
            ultimateBoard.boards[r*3].winner == ultimateBoard.boards[r*3+2].winner &&
            ultimateBoard.boards[r*3].winner != State::Empty) {
                ultimateBoard.winner = ultimateBoard.boards[r*3].winner;
                gameOver = true;
                return;
        }
    }
    //Check all three columns
    for (int r = 0; r < 3; r++) {
        if (ultimateBoard.boards[r].winner == ultimateBoard.boards[r+3].winner &&
            ultimateBoard.boards[r].winner == ultimateBoard.boards[r+6].winner &&
            ultimateBoard.boards[r].winner != State::Empty) {
                ultimateBoard.winner = ultimateBoard.boards[r].winner;
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
            return;
    }
    else if (ultimateBoard.boards[6].winner == ultimateBoard.boards[4].winner &&
        ultimateBoard.boards[6].winner == ultimateBoard.boards[2].winner &&
        ultimateBoard.boards[6].winner != State::Empty) {
            ultimateBoard.winner = ultimateBoard.boards[6].winner;
            gameOver = true;
            return;
    }

    //No Winner - Check for Draws
    bool allFinished = true;
    for (Board board : ultimateBoard.boards) {
        if (board.winner == State::Empty) {
            allFinished = false;
            break;
        }
    }
    if (allFinished) {
        ultimateBoard.winner == State::Draw;
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