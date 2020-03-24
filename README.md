# Ultimate Tic-Tac-Toe Bots Final Project for Udacity C++ Nanodegree

<p align="center">
    <img src="/images/ultimate_TTT.gif" width="360" height="360">
</p>

## Game Rules
**Goal:** Win 3 local boards to create a Tic-Tac-Toe (3 in a row) on the global board. 
* Each small 3 × 3 tic-tac-toe board is referred to as a local board, and the larger 3 × 3 board is referred to as the global board.
* The game randomly selects who goes first.
* When a player makes a move on the local board, the opposing player is "sent" to the corresponding local board on the global board.
  * Example: If "X" moves in the middle cell on an active local board, player "O" will be sent to the middle local board on the global board.
* If a player is sent to a local board that is already finished then all unfinished baords will become active and playable.
* Also when a player wins a local board all unfinished boards will become active for the next player.

## Program Code Structure


## Ruberic Highlights
**Ruberic Requirement:** The project demonstrates an understanding of C++ functions and control structures. 

**Location Addressed:** Game.cpp file Game::Run function lines 11-49.


## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
  * Helpful Tutorial can be found [here](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/index.php)
* SDL2_gfx >= 1.0.4
  * Already set up in dependencies folder
  * Full Library can be found [here](https://www.ferzkopp.net/wordpress/2016/01/02/sdl_gfx-sdl2_gfx/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./HelloWorld`.
