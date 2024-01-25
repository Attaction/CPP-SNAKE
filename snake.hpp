#ifndef SNAKE_HPP
#define SNAKE_HPP

#include "game_end.hpp"
#include "node.hpp"
#include "food.hpp"

class Game;
class Food;

enum class Dir {
    Up,
    Down,
    Left,
    Right
};

class Snake{
    Node *head; 
    Node *tail;
    int len;
    Dir direction;
public:
    Snake(int x, int y);
    Snake(int x, int y, bool testing);

    Node* getHead() const {return head;}
    Node* getTail() const {return tail;}
    Dir getDir() const {return direction;}
    int getLen() const {return len;}

    Node* setHead(Node* newHead) {return head = newHead;}
    Node* setTail(Node* newTail) {return tail = newTail;}
    int setLen(int newLen) {return len = newLen;}
    Dir setDir(Dir newDir) {return direction = newDir;}

    static void snakeUpdate(Game* game, Snake* snake, Food* food, bool &game_over);
    static void snakeUpdate(Game* game, Snake* snake, Food* food, bool &game_over, bool& testing, bool& uonce, bool& donce, bool& lonce, bool& ronce, bool& testedhitfood, bool& testednothitfood);
    
    static bool hitWall(Snake* snake, Game* game);
    
    static bool hitTail(Snake* snake, bool& game_over);
    
    static bool hitFood(Node* node, Food* food);
    
    static void clearSnake(Snake* snake) {
        while (snake->getTail()->getPrev() != NULL) {
            Node *temp = snake->getTail()->getPrev();
            Node::clearNode(snake->getTail());
            snake->setTail(temp);
        }
    };
    ~Snake();
};

#endif