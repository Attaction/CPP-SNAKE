#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>

#include "gtest_lite.h"

#include "start.hpp"
#include "game_end.hpp"
#include "food.hpp"
#include "snake.hpp"
#include "node.hpp"


int main(int argc, char ** args) {

    Game test("Test", 800, 600);

    bool testing = true;
    bool test_close = false;
    bool test_over = false;
    int test_highscore = 1;

    while(!test_close){ 
        Game::gameLoop(&test, test_over, test_close, test_highscore, testing);
    }

    testing = false;
    test.clearGame();

    Game game("SNAKE", 800, 600);

    bool start = true;
    bool game_close = false;
    bool game_over = false;
    int highscore = 1;
    
    while (!game_close) {
        while (start) {
            Start::startMenu(game.getRenderer(), game_close, start, game.getW(), game.getH());
            if(game_close) break;
        };
        Game::gameLoop(&game, game_over, game_close, highscore, testing);
    }

    return 0;
};