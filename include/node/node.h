#ifndef NODE_H
#define NODE_H

template <typename T>
class Node {
    private:
        T data;
        Node<T>* next = nullptr;
        Node<T>* previous = nullptr;
        void printPrimitive();
        void printStruct();
    public:
        Node(T data);
        void setData(T data);
        T getData();
        Node<T>* getNextNode();
        void setNextNode(Node<T>* nextNode);
        Node<T>* getPreviousNode();
        void setPreviousNode(Node<T>* previousNode);
        void print(bool isPrimitive);
};
#endif