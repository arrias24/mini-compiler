#pragma once
#include "../node/node.h"
template <typename T>
class ArrayList {
    private:
        Node<T>* head = NULL;
        Node<T>* tail = NULL;
        int size;
    public:
        ArrayList<T>();
        void add(Node<T> node);
        Node<T> get();
        void remove(int index);
        Node<T>* next();
        Node<T>* previous();
        Node<T>* firts();
        Node<T>* last();
        int getSize();
        bool isEmpty();
};