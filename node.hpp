#ifndef NODE_HPP
#define NODE_HPP

class Node {
    int x, y;
    int size;
    Node* prev;
    Node* next;
public:
    Node(): x(0), y(0), size(10), prev(nullptr), next(nullptr) {};

    Node* getNext() const {return next;}
    Node* getPrev() const {return prev;}

    int getX() const {return x;}
    int getY() const {return y;}

    void setX(int newX) {x = newX;};
    void setY(int newY) {y = newY;}
    void setSize(int newSize) {size = newSize;}
    Node* setPrev(Node* newPrev) {return prev = newPrev;}
    Node* setNext(Node* newNext) {return next = newNext;}

    int getSize() const {return size;}

    static void clearNode(Node* node) {
        node->next = nullptr;
        node->prev = nullptr;
        node->x = 0;
        node->y = 0;
        node->size = 0;
        delete node;
    };

    ~Node() {
        this->setNext(NULL);
        this->setPrev(NULL);
        this->setX(0);
        this->setY(0);
        this->setSize(0);
    };
};

#endif