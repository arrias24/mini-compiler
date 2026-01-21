#pragma once
template <typename T>
class Node {
    private:
        T data;
        Node<T>* next = NULL;
        Node<T>* previous = NULL;
    public:
        Node(T data, Node<T>* next, Node<T>* previous);
        void setData(T data);
        T getData();
        Node<T>* getNextNode();
        void setNextNode(Node<T>* nextNode);
        Node<T>* getPreviousNode();
        void setPreviousNode(Node<T>* previousNode);
        void print();
        ~Node();
};