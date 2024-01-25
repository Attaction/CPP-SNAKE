#ifndef FOOD_CPP
#define FOOD_CPP

#include "food.hpp"

#include <cstdlib>
#include <ctime>

#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>

Food::Food(Snake* snake, int w, int h) {
    srand(time(0));

    int x = rand() % (w / 10) * 10;
    int y = rand() % (h / 10) * 10;
    this->setX(x);
    this->setY(y);

    while(foodOnSnake(snake, this)) {
        this->setX(rand() % (w / 10) * 10);
        this->setY(rand() % (h / 10) * 10);
    }
}

Food::Food(bool testing) {
    int x = 30;
    int y = 30;
    this->setX(x);
    this->setY(y);
}

void Food::newFood(Game* game, Snake* snake, Food* food) {
    srand(time(0));

    food->setX(rand() % (game->getW() / 10) * 10);
    food->setY(rand() % (game->getH() / 10) * 10);

    while(foodOnSnake(snake, food)) {
        food->setX(rand() % (game->getW() / 10) * 10);
        food->setY(rand() % (game->getH() / 10) * 10);
    }

    boxRGBA(game->getRenderer(), food->x, food->y, food->x + 10, food->y + 10, 255, 0, 0, 255);
};

void Food::newFood(Game* game, Snake* snake, Food* food, bool testing) {

    while(foodOnSnake(snake, food)) {
        food->setX(food->getX() + 10);
        food->setY(food->getY() + 10);
    }
    boxRGBA(game->getRenderer(), food->x, food->y, food->x + 10, food->y + 10, 255, 0, 0, 255);
};

bool Food::foodOnSnake(Snake* snake, Food* food) {
    Node *node = snake->getTail();
    while (node->getPrev() != NULL) {
        if (food->x == node->getX() && food->y == node->getY()) {
            return true;
        }
        node = node->getPrev();
    }
    return false;
}

#endif