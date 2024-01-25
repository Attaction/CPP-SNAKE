#ifndef FOOD_HPP
#define FOOD_HPP

#include "game_end.hpp"
#include "node.hpp"
#include "snake.hpp"

class Game;
class Snake;

class Food {
    int x, y;
public:

    Food(int x, int y): x(x), y(y) {}
    Food(Snake* snake, int w, int h);
    Food(bool testing);

    int getX() const {return x;}
    int getY() const {return y;}

    int setX(int newX) {return x = newX;}
    int setY(int newY) {return y = newY;}

    static void newFood(Game* game, Snake* snake, Food* food);
    static void newFood(Game* game, Snake* snake, Food* food, bool testing);

    static bool foodOnSnake(Snake* snake, Food* food);
};

#endif