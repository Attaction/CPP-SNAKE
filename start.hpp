#ifndef START_HPP
#define START_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>

class Start {
    TTF_Font *font;
public:
    static void startMenu(SDL_Renderer *renderer, bool& game_close, bool& start, int HEIGHT, int WIDTH);
};


#endif