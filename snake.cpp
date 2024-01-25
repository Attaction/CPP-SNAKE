#ifndef SNAKE_CPP
#define SNAKE_CPP

#include "gtest_lite.h"

#include "snake.hpp"

Snake::Snake(int w, int h) {
    head = new Node();
    head->setX(w / 2);
    head->setY(h / 2);
    head->setSize(10);
    len = 1;
    direction = Dir::Up;
    tail = head;
};

Snake::Snake(int w, int h, bool testing) {
    head = new Node();
    head->setX(w/2);
    head->setY(0);
    head->setSize(10);
    len = 1;
    direction = Dir::Right;
    tail = head;
}

void Snake::snakeUpdate(Game* game, Snake* snake, Food* food, bool& game_over, bool& testing, bool& uonce, bool& donce, bool& lonce, bool& ronce, bool& testedhitfood, bool& testednothitfood) {
    Node *newstart = new Node();
    snake->getHead()->setPrev(newstart);
    newstart->setNext(snake->getHead());
    newstart->setX(snake->getHead()->getX());
    newstart->setY(snake->getHead()->getY());
    snake->setHead(newstart);
    
    int test_y = newstart->getY();
    int test_x = newstart->getX();

    switch (snake->getDir()) {
        case Dir::Up:
            newstart->setY(newstart->getY() - 10);
            if (testing && !uonce) { 
                TEST(Felfele, SnakeMove) {
                    EXPECT_EQ(newstart->getY(), test_y - 10); // A kigyo feje felfele megy es mivel a kepernyo bal felso sarka a 0,0 pont es felfele novekedik az y koordinata a kigyo feje az elozo koordinatahoz kepest -10 kell legyen.
                END };
                uonce = true;
            }
            break;
        case Dir::Down:
            newstart->setY(newstart->getY() + 10);
            if (testing && !donce) {
                TEST(Lefele, SnakeMove) {
                    EXPECT_EQ(newstart->getY(), test_y + 10); // A kigyo feje lefele megy es mivel a kepernyo bal felso sarka a 0,0 pont es lefele novekedik az y koordinata a kigyo feje az elozo koordinatahoz kepest +10 kell legyen.
                END };
                donce = true;
            }
            break;
        case Dir::Left:
            newstart->setX(newstart->getX() - 10);
            if (testing && !lonce) {
                TEST(Balra, SnakeMove) {
                    EXPECT_EQ(newstart->getX(), test_x - 10); // A kigyo feje balra megy es mivel a kepernyo bal felso sarka a 0,0 pont es jobbra novekedik az x koordinata a kigyo feje az elozo koordinatahoz kepest -10 kell legyen.
                END };
                lonce = true;
            }
            break;
        case Dir::Right:
            newstart->setX(newstart->getX() + 10);
            if (testing && !ronce) {
                TEST(Jobbra, SnakeMove) {
                    EXPECT_EQ(newstart->getX(), test_x + 10); // A kigyo feje jobbra megy es mivel a kepernyo bal felso sarka a 0,0 pont es jobbra novekedik az x koordinata a kigyo feje az elozo koordinatahoz kepest +10 kell legyen.
                END };
                ronce = true;
            }
            break;
    }
    boxRGBA(game->getRenderer(), newstart->getX(), newstart->getY(), newstart->getX() + newstart->getSize(), newstart->getY() + newstart->getSize(), 0, 255, 0, 255);

    if (!hitFood(snake->getHead()->getNext(), food)) {
        if (testing && !testednothitfood) {
            TEST(NemTalalt, FoodHit) {
                EXPECT_FALSE(hitFood(snake->getHead()->getNext(), food));
            END };
            testednothitfood = true;
        }
        Node* oldtail = snake->getTail();
        snake->getTail()->getPrev()->setNext(NULL);
        snake->setTail(oldtail->getPrev());
        boxRGBA(game->getRenderer(), oldtail->getX(), oldtail->getY(), oldtail->getX() + oldtail->getSize(), oldtail->getY() + oldtail->getSize(), 0, 0, 0, 255);
        Node::clearNode(oldtail);
    } else {
        if (testing && !testedhitfood) {
            TEST(Eltalalt, FoodHit) {
                EXPECT_TRUE(hitFood(snake->getHead()->getNext(), food));
            END };
            testedhitfood = true;
        }
        Food::newFood(game, snake, food);
        snake->setLen(snake->getLen() + 1);
    }
};

bool Snake::hitWall(Snake* snake, Game* game) {
    if (snake->getHead()->getX() < 0) {
        return true;
    }
    else if(snake->getHead()->getX() > game->getW() + 5) {
        return true;
    }
    else if(snake->getHead()->getY() < 0) {
        return true;
    }
    else if(snake->getHead()->getY() > game->getH() + 5) {
        return true;
    }
    return false;
}

bool Snake::hitTail(Snake* snake, bool& game_over) {
    Node* node = snake->getTail();
    while(node->getPrev()->getPrev() != nullptr) {
        if(snake->getHead()->getX() == node->getX() && snake->getHead()->getY() == node->getY()) {
            return true;
        }
        node = node->getPrev();
    }
    return false;
}

bool Snake::hitFood(Node* node, Food* food) {
    return (node->getX() == food->getX()) && (node->getY() == food->getY());
}

Snake::~Snake() {
    Node *current = tail;
    while (current != NULL) {
        Node *prev = current->getPrev();
        delete current;
        current = prev;
    }
}

#endif