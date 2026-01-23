#pragma once
#include "../node/node.h"
template <typename T>
class Stack {
    private:
        T data;
        Node<T>* head = NULL;
    public:
        void put(Node<T> node);
        T pop();
        T getter();
};