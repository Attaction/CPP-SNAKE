#ifndef GAME_END_HPP
#define GAME_END_HPP

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>

#include "node.hpp"
#include "snake.hpp"
#include "food.hpp"

class Node;
class Snake;
class Food;

class Game{
    SDL_Window* window;
    SDL_Renderer* renderer;
    int w;
    int h;
    void sdl_init(const char* title, int w, int h);
public:
    Game(const char* title, int w, int h): w(w), h(h) {
        sdl_init(title, w, h);
    }

    SDL_Window *getWindow() const {return window;}
    SDL_Renderer *getRenderer() const {return renderer;}
    int getW() const {return w;}
    int getH() const {return h;}

    static void startup(Game* game, Snake *snake, Food* food);
    static void startup(Game* game, Snake *snake, Food* food, bool testing);

    static void gameLoop(Game* game, bool& game_over, bool& game_close, int& highscore, bool& testing);

    static void IntoFile(int score);

    void clearGame();

    ~Game() {
        clearGame();
    }
};

#endif