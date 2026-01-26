#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include "../node/node.cpp"

template <typename T>
class ArrayList {
    private:
        Node<T>* head;
        Node<T>* tail;
        int size;

        void addEmpty(Node<T>* node);
        void addFirst(Node<T>* node);
        void addLast(Node<T>* node);
        void removeEmpty();
        void shift();
        void pop();
        void removeMiddle(Node<T>* node);

    public:
        ArrayList<T>();
        void add(T data, bool isInsertFirst);
        Node<T>* get(int index);
        Node<T>* remove(int index);
        Node<T>* getFirst();
        Node<T>* getlast();
        Node<T>* removeFirst();
        Node<T>* removerLast();
        bool has(T data);
        int getSize() const;
        void printList();
        bool isEmpty();
        ~ArrayList();
};
#endif