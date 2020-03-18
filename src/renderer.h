#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include "game.h"
#include "board.h"


class Renderer {
public:
    Renderer(const std::size_t screen_width, const std::size_t screen_height, const std::size_t tile_width, const std::size_t tile_height);
    ~Renderer();
    void Render(Board board);
    void UpdateWindowTitle();

private:
    SDL_Window *_window;
    SDL_Renderer *_renderer;
    const std::size_t screen_width;
    const std::size_t screen_height;
    const std::size_t tile_width;
    const std::size_t tile_height;

    void drawX(SDL_Renderer *renderer, const int row, const int col);
    void drawY(SDL_Renderer *renderer, const int row, const int col);
};

#endif