#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include "game.h"
#include "gameObjects.h"


class Renderer {
public:
    Renderer(const std::size_t screen_width, const std::size_t screen_height, const std::size_t tile_width, const std::size_t tile_height);
    ~Renderer();
    void Render(UltimateBoard boards);
    void UpdateWindowTitle();

private:
    SDL_Window *_window;
    SDL_Renderer *_renderer;
    const std::size_t screen_width;
    const std::size_t screen_height;
    const std::size_t tile_width;
    const std::size_t tile_height;

    void drawX(SDL_Renderer *renderer, const int board_row, const int board_col, const int row, const int col);
    void drawO(SDL_Renderer *renderer, const int board_row, const int board_col, const bool active, const int row, const int col);
};

#endif