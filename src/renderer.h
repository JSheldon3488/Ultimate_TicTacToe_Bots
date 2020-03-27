#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include "gameObjects.h"


class Color {
public:
    Color(int r, int g, int b);
    int r;
    int g;
    int b;
};


class Renderer {
public:
    Renderer(const std::size_t screen_width, const std::size_t screen_height, const std::size_t tile_width, const std::size_t tile_height);
    ~Renderer();
    void Render(const UltimateBoard &ultimateBoard, bool gameOver, State winner);
    void UpdateWindowTitle(State player, bool gameOver, State winner);

private:
    SDL_Window *_window;
    SDL_Renderer *_renderer;
    const std::size_t screen_width;
    const std::size_t screen_height;
    const std::size_t tile_width;
    const std::size_t tile_height;
    Color x_color{255,0,0};
    Color o_color{0,165,0};
    Color background_color{162,181,205};
    Color tile_color{255,255,255};
    Color tile_border{0,0,0};
    Color inValid_color{105,105,105};
    Color xWin_color{255,102,102};
    Color oWin_color{102,255,102};

    void drawX(SDL_Renderer *renderer, Board &board, Tile &tile);
    void drawO(SDL_Renderer *renderer,  Board &board, Tile &tile, Move lastMove);
    void drawBoardWinners(SDL_Renderer *renderer, const UltimateBoard &ultimateBoard);
};

#endif