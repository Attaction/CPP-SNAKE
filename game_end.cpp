#ifndef GAME_END_CPP
#define GAME_END_CPP

#include <iostream>
#include <fstream>
#include <chrono>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>

#include "game_end.hpp"
#include "gtest_lite.h"

void Game::sdl_init(const char* title, int w, int h) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cerr << "Hiba az elejen: " << SDL_GetError() << std::endl;
        exit(1);
    };

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        std::cerr << "Hiba az ablaknal: " << SDL_GetError() << std::endl;
        exit(1);
    };

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL) {
        std::cerr << "Hiba a megjelenitonel: " << SDL_GetError() << std::endl;
        exit(1);
    };

    TTF_Init();
};

void Game::IntoFile(int score) {
    std::ofstream of("max.txt");

    if (!of) {
        std::cerr << "Opening file error" << std::endl;
        exit(1);
    }

    auto now = std::chrono::system_clock::now();
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);

    if (of.is_open()) {
        of << std::ctime(&now_time_t) << "SCORE : " << score << std::endl;
    };

    of.close();
}

void Game::gameLoop(Game* game, bool& game_over, bool& game_close, int &highscore, bool& testing) {
    SDL_Window* window = game->getWindow();
    SDL_Renderer* renderer = game->getRenderer();

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    SDL_Event event;

    bool uonce = false;
    bool donce = false;
    bool lonce = false;
    bool ronce = false;

    bool testedhitfood = false;
    bool testednothitfood = false;

    bool testedHitWall = false;
    bool testedNotHitWall = false;

    bool testedHitTail = false;
    bool testedNotHitTail = false;

    if (testing) {
        Snake testsnake(game->getW(), game->getH(), testing);
        Food testfood(testing);
        Game::startup(game, &testsnake, &testfood, testing);
        SDL_RenderPresent(renderer);

        while (!game_over && !game_close) {
            //Bekerunk egy eventet az event valtozonkba.
            SDL_PollEvent(&event);

            //Ameddig nem kapunk egy keyboard eventet, addig a kigyonk folyamatosan mozog az elore megadott iranyba.
            while (event.key.type != SDL_KEYDOWN && !game_over) {
                Snake::snakeUpdate(game, &testsnake, &testfood, game_over, testing, uonce, donce, lonce, ronce, testedhitfood, testednothitfood);
                if(Snake::hitWall(&testsnake, game)) {
                    if (!testedHitWall) {
                        TEST(Eltalalta, SnakeHitWall) {
                            EXPECT_TRUE(Snake::hitWall(&testsnake, game));
                        END };
                        testedHitWall = true;
                    }
                    game_over = true;
                }
                if (!testedNotHitWall) {
                    TEST(NemTalaltaEl, SnakeHitWall) {
                        EXPECT_FALSE(Snake::hitWall(&testsnake, game));
                    END };
                    testedNotHitWall = true;
                }
                if(testsnake.getLen() > 1) {
                    if (Snake::hitTail(&testsnake, game_over)) {
                        if(!testedHitTail) {
                            TEST(Eltalalta, SnakeHitTail) {
                                EXPECT_TRUE(Snake::hitTail(&testsnake, game_over));
                            END};
                            testedHitTail = true;
                        }
                        game_over = true;
                    }
                    if (!testedNotHitTail) {
                        TEST(NemTalaltaEl, SnakeHitTail) {
                            EXPECT_FALSE(Snake::hitTail(&testsnake, game_over));
                        END};
                        testedNotHitTail = true;
                    }
                }
                std::string windowTitle = "SNAKE | SCORE: " + std::to_string(testsnake.getLen()) + " HIGHSCORE: " + std::to_string(highscore);
                SDL_SetWindowTitle(window, windowTitle.c_str());
                SDL_RenderPresent(renderer);
                SDL_PollEvent(&event);
                SDL_Delay(150);
            }

            //Amennyiben kapunk keyboardeventet, megnezzuk melyik az.
            switch (event.key.keysym.sym) {
                //Q megnyomasara kilepunk a jatekbol.
                case SDLK_q:
                    if (testsnake.getLen() > highscore) {highscore = testsnake.getLen();}
                    IntoFile(highscore);
                    game_close = true;
                    break;
                //A nyilak megnyomasara megnezzuk, hogy nem az ellenkezo iranyba megy-e a kigyonk. Ha arra megy, akkor a kigyonk meghal es a jatek veget er.
                //Ha nem az ellenkezo iranyba megy, akkor megvaltoztatjuk az iranyat a kigyonknak.
                case SDLK_UP:
                    if (testsnake.getDir() == Dir::Down) {game_over = true;}
                    testsnake.setDir(Dir::Up);
                    break;
                case SDLK_DOWN:
                    if (testsnake.getDir() == Dir::Up) {game_over = true;}
                    testsnake.setDir(Dir::Down);
                    break;
                case SDLK_LEFT:
                    if (testsnake.getDir() == Dir::Right) {game_over = true;}
                    testsnake.setDir(Dir::Left);
                    break;
                case SDLK_RIGHT:
                    if (testsnake.getDir() == Dir::Left) {game_over = true;}
                    testsnake.setDir(Dir::Right);
                    break;
            }
        }
        if (testsnake.getLen() > highscore) {highscore = testsnake.getLen();}
        if (game_close && !game_over) {
            Snake::clearSnake(&testsnake);
            return;
        }
        SDL_SetWindowTitle(window, "SNAKE");
        if (game_over) {
            //Halal eseten beszinezzuk a teljes kepernyot.
            SDL_RenderClear(renderer);
            boxRGBA(renderer, 0, 0, 800, 600, 49, 1, 112, 255);

            //Letrehozzuk a nagyobb, illetve a kisebb betutipust es meretet nekik.
            TTF_Font *endbigfont = TTF_OpenFont("comic.ttf", 70);
            TTF_Font *scorefont = TTF_OpenFont("comic.ttf", 35);
            TTF_Font *endsmallfont = TTF_OpenFont("comic.ttf", 15);

            //Kiirjuk a halaluzenetet
            SDL_Surface *deathmsg;
            SDL_Texture *deathmsg_t;
            SDL_Rect deathmsgpos = {0, 0, 0, 0};
            deathmsg = TTF_RenderUTF8_Blended(endbigfont, "YOU DIED", {255, 255, 255});
            deathmsg_t = SDL_CreateTextureFromSurface(renderer, deathmsg);
            deathmsgpos.x = (game->getW() - deathmsg->w) / 2;
            deathmsgpos.y = (game->getH() - deathmsg->h) / 2;
            deathmsgpos.w = deathmsg->w;
            deathmsgpos.h = deathmsg->h;
            SDL_RenderCopy(renderer, deathmsg_t, NULL, &deathmsgpos);

            std::string end = "YOUR SCORE: " + std::to_string(testsnake.getLen());
            SDL_Surface *score;
            SDL_Texture *score_t;
            SDL_Rect scorepos = {0, 0, 0, 0};
            score = TTF_RenderUTF8_Blended(scorefont, end.c_str(), {255, 255, 255});
            score_t = SDL_CreateTextureFromSurface(renderer, score);
            scorepos.x = (game->getW() - score->w) / 2;
            scorepos.y = (game->getH() - deathmsg->h + 150) / 2;
            scorepos.w = score->w;
            scorepos.h = score->h;
            SDL_RenderCopy(renderer, score_t, NULL, &scorepos);

            //A vegso kepernyon megjelenitjuk a tovabblepesi lehetosegeket (Q kilepes, P uj jatek).
            SDL_Surface *endcontrols;
            SDL_Texture *endcontrols_t;
            SDL_Rect endcontrolspos = {0, 0, 0, 0};
            endcontrols = TTF_RenderUTF8_Blended(endsmallfont, "PRESS (P) TO PLAY AGAIN. PRESS (Q) TO QUIT.", {255, 255, 255});
            endcontrols_t = SDL_CreateTextureFromSurface(renderer, endcontrols);
            endcontrolspos.x = (game->getW() - endcontrols->w) / 2;
            endcontrolspos.y = game->getH() - endcontrols->h;
            endcontrolspos.w = endcontrols->w;
            endcontrolspos.h = endcontrols->h;
            SDL_RenderCopy(renderer, endcontrols_t, NULL, &endcontrolspos);

            //Varjuk a billentyu bemenetet, hogy eldontsuk mi legyen a kovetkezo event.
            SDL_RenderPresent(renderer);
            SDL_WaitEvent(&event);
            while (event.type != SDL_KEYDOWN) {
                SDL_WaitEvent(&event);
            }
            if (event.key.keysym.sym == SDLK_q) {
                IntoFile(highscore);
                game_close = true;
            }
            if (event.key.keysym.sym == SDLK_p) {
                game_over = false;
            }
        }
    }
    else {
        Snake snake(game->getW(), game->getH());
        Food food(&snake, game->getW(), game->getH());
        Game::startup(game, &snake, &food);
        SDL_RenderPresent(renderer);

        while (!game_over && !game_close) {
            //Bekerunk egy eventet az event valtozonkba.
            SDL_PollEvent(&event);

            //Ameddig nem kapunk egy keyboard eventet, addig a kigyonk folyamatosan mozog az elore megadott iranyba.
            while (event.key.type != SDL_KEYDOWN && !game_over) {
                Snake::snakeUpdate(game, &snake, &food, game_over, testing, uonce, donce, lonce, ronce, testedhitfood, testednothitfood);
                if(Snake::hitWall(&snake, game)) {game_over = true;}
                if(snake.getLen() > 1) {
                    if (Snake::hitTail(&snake, game_over)) {
                        game_over = true;
                    }
                }
                std::string windowTitle = "SNAKE | SCORE: " + std::to_string(snake.getLen()) + " HIGHSCORE: " + std::to_string(highscore);
                SDL_SetWindowTitle(window, windowTitle.c_str());
                SDL_RenderPresent(renderer);
                SDL_PollEvent(&event);
                SDL_Delay(150);
            }

            //Amennyiben kapunk keyboardeventet, megnezzuk melyik az.
            switch (event.key.keysym.sym) {
                //Q megnyomasara kilepunk a jatekbol.
                case SDLK_q:
                    if (snake.getLen() > highscore) {highscore = snake.getLen();}
                    IntoFile(highscore);
                    game_close = true;
                    break;
                //A nyilak megnyomasara megnezzuk, hogy nem az ellenkezo iranyba megy-e a kigyonk. Ha arra megy, akkor a kigyonk meghal es a jatek veget er.
                //Ha nem az ellenkezo iranyba megy, akkor megvaltoztatjuk az iranyat a kigyonknak.
                case SDLK_UP:
                    if (snake.getDir() == Dir::Down) {game_over = true;}
                    snake.setDir(Dir::Up);
                    break;
                case SDLK_DOWN:
                    if (snake.getDir() == Dir::Up) {game_over = true;}
                    snake.setDir(Dir::Down);
                    break;
                case SDLK_LEFT:
                    if (snake.getDir() == Dir::Right) {game_over = true;}
                    snake.setDir(Dir::Left);
                    break;
                case SDLK_RIGHT:
                    if (snake.getDir() == Dir::Left) {game_over = true;}
                    snake.setDir(Dir::Right);
                    break;
            }
        }
        if (snake.getLen() > highscore) {highscore = snake.getLen();}
        if (game_close && !game_over) {
            Snake::clearSnake(&snake);
            return;
        }
        //Halalkor visszavaltoztatjuk az ablak nevet.
        SDL_SetWindowTitle(window, "SNAKE");
        if (game_over) {
            //Halal eseten beszinezzuk a teljes kepernyot.
            SDL_RenderClear(renderer);
            boxRGBA(renderer, 0, 0, 800, 600, 49, 1, 112, 255);

            //Letrehozzuk a nagyobb, illetve a kisebb betutipust es meretet nekik.
            TTF_Font *endbigfont = TTF_OpenFont("comic.ttf", 70);
            TTF_Font *scorefont = TTF_OpenFont("comic.ttf", 35);
            TTF_Font *endsmallfont = TTF_OpenFont("comic.ttf", 15);

            //Kiirjuk a halaluzenetet
            SDL_Surface *deathmsg;
            SDL_Texture *deathmsg_t;
            SDL_Rect deathmsgpos = {0, 0, 0, 0};
            deathmsg = TTF_RenderUTF8_Blended(endbigfont, "YOU DIED", {255, 255, 255});
            deathmsg_t = SDL_CreateTextureFromSurface(renderer, deathmsg);
            deathmsgpos.x = (game->getW() - deathmsg->w) / 2;
            deathmsgpos.y = (game->getH() - deathmsg->h) / 2;
            deathmsgpos.w = deathmsg->w;
            deathmsgpos.h = deathmsg->h;
            SDL_RenderCopy(renderer, deathmsg_t, NULL, &deathmsgpos);

            std::string end = "YOUR SCORE: " + std::to_string(snake.getLen());
            SDL_Surface *score;
            SDL_Texture *score_t;
            SDL_Rect scorepos = {0, 0, 0, 0};
            score = TTF_RenderUTF8_Blended(scorefont, end.c_str(), {255, 255, 255});
            score_t = SDL_CreateTextureFromSurface(renderer, score);
            scorepos.x = (game->getW() - score->w) / 2;
            scorepos.y = (game->getH() - deathmsg->h + 150) / 2;
            scorepos.w = score->w;
            scorepos.h = score->h;
            SDL_RenderCopy(renderer, score_t, NULL, &scorepos);

            //A vegso kepernyon megjelenitjuk a tovabblepesi lehetosegeket (Q kilepes, P uj jatek).
            SDL_Surface *endcontrols;
            SDL_Texture *endcontrols_t;
            SDL_Rect endcontrolspos = {0, 0, 0, 0};
            endcontrols = TTF_RenderUTF8_Blended(endsmallfont, "PRESS (P) TO PLAY AGAIN. PRESS (Q) TO QUIT.", {255, 255, 255});
            endcontrols_t = SDL_CreateTextureFromSurface(renderer, endcontrols);
            endcontrolspos.x = (game->getW() - endcontrols->w) / 2;
            endcontrolspos.y = game->getH() - endcontrols->h;
            endcontrolspos.w = endcontrols->w;
            endcontrolspos.h = endcontrols->h;
            SDL_RenderCopy(renderer, endcontrols_t, NULL, &endcontrolspos);

            //Varjuk a billentyu bemenetet, hogy eldontsuk mi legyen a kovetkezo event.
            SDL_RenderPresent(renderer);
            SDL_WaitEvent(&event);
            while (event.type != SDL_KEYDOWN) {
                SDL_WaitEvent(&event);
            }
            if (event.key.keysym.sym == SDLK_q) {
                IntoFile(highscore);
                game_close = true;
            }
            if (event.key.keysym.sym == SDLK_p) {
                game_over = false;
            }
        }
    }
}

void Game::startup(Game* game, Snake *snake, Food* food) {
    Food::newFood(game, snake, food);
    boxRGBA(game->getRenderer(), snake->getHead()->getX(), snake->getHead()->getY(), snake->getHead()->getX() + snake->getHead()->getSize(), snake->getHead()->getY() + snake->getHead()->getSize(), 0, 255, 0, 255);
};

void Game::startup(Game* game, Snake *snake, Food* food, bool testing) {
    Food::newFood(game, snake, food, testing);
    boxRGBA(game->getRenderer(), snake->getHead()->getX(), snake->getHead()->getY(), snake->getHead()->getX() + snake->getHead()->getSize(), snake->getHead()->getY() + snake->getHead()->getSize(), 0, 255, 0, 255);
};

void Game::clearGame() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    TTF_Quit();
    SDL_Quit();
};

#endif