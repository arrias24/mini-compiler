#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include "../node/node.cpp"

template <typename T>
class ArrayList {
    private:
        Node<T>* head;
        Node<T>* tail;
        Node<T>* current;
        int size;
        void addWhenEmpty(Node<T>* node);
        void removeWhenEmpty();
        void shift();
        void unshift();
        void removeMiddle(Node<T>* node);

    public:
        ArrayList<T>();
        void addFirst(T data);
        void addLast(T data);
        Node<T>* get();
        Node<T>* get(int index);
        Node<T>* getFirst();
        Node<T>* getLast();
        Node<T>* remove(int index);
        Node<T>* removeFirst();
        Node<T>* removeLast();
        bool currentNext();
        bool currentPrevious();
        void currentReset();
        Node<T>* currentPeek();
        bool has(T data);
        int getSize() const;
        void printList();
        bool isEmpty();
        ~ArrayList();
};
#endif