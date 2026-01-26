#ifndef STACK_H
#define STACK_H
#include "../node/node.cpp"
template <typename T>
class Stack {
    private:
        Node<T>* head;
        int size;
    public:
        Stack();
        void push(T data);
        T pop();
        T top();
        int getSize();
        void printStack();
        bool has(T data);
        bool isEmpty();
        ~Stack();
};
#endif