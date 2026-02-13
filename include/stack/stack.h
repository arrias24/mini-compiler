#ifndef STACK_H
#define STACK_H
#include "../node/node.h"
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

#include "./stack.h"

/**
 * @brief Constructor por defecto.
 * Inicializa una pila vacía con tamaño cero.
 */
template <typename T>
Stack<T>::Stack() {
    this->head = nullptr;
    this->size = 0;
};

/**
 * @brief Comprueba si la pila está vacía.
 * @return true si la pila no contiene elementos, false en caso contrario.
 */
template <typename T>
bool Stack<T>::isEmpty() {
    return (this->size == 0 && this->head == nullptr);
};

/**
 * @brief Inserta un nuevo elemento en la parte superior de la pila.
 * @param data El valor de tipo T que se desea almacenar.
 */
template <typename T>
void Stack<T>::push(T data){
    Node<T>* node = new Node<T>(data);

    if(this->isEmpty()){this->head = node;}
    else{
        node->setNextNode(this->head);
        this->head = node;
    }
    ++this->size;
};

/**
 * @brief Elimina y devuelve el elemento en la parte superior de la pila.
 * @throw std::out_of_range Si la pila está vacía.
 * @return T El dato almacenado en el nodo superior.
 */
template <typename T>
T Stack<T>::pop(){
    this->isEmpty() ? throw std::out_of_range("Stack is empty") : nullptr;
    Node<T>* temp = this->head;
    T data = temp->getData();
    this->head = this->head->getNextNode();
    delete temp;
    --this->size;
    return data;
}

/**
 * @brief Devuelve el elemento superior sin eliminarlo de la pila.
 * @throw std::out_of_range Si la pila está vacía.
 * @return T El dato en la cima de la pila.
 */
template <typename T>
T Stack<T>::top(){
    this->isEmpty() ? throw std::out_of_range("Stack is empty") : nullptr;
    return this->head->getData();
};

/**
 * @brief Obtiene el número actual de elementos en la pila.
 * @return int Cantidad de elementos.
 */
template <typename T>
int Stack<T>::getSize(){
    return this->size;
};

/**
 * @brief Imprime todos los elementos de la pila en la consola.
 * Si la pila está vacía, muestra un mensaje informativo.
 */
template <typename T>
void Stack<T>::printStack(){
    if(this->isEmpty()){std::cout << "Stack is empty" << std::endl; return;}
    Node<T>* temp = this->head;
    while(temp != nullptr){
        temp->print(true);
        temp = temp->getNextNode();
    }
};

/**
 * @brief Busca si un elemento específico existe en la pila.
 * @param data Valor de tipo T a buscar.
 * @throw std::out_of_range Si la pila está vacía.
 * @return true si el elemento se encuentra, false de lo contrario.
 */
template <typename T>
bool Stack<T>::has(T data){
    if(this->isEmpty()){
        std::cout << "Stack is empty" << std::endl;
        throw std::out_of_range("Stack is empty") ;
    }
    Node<T>* temp = this->head;
    while(temp != nullptr){
        if (temp->getData() == data){return true;}
        temp = temp->getNextNode();
    }
    return false;
}

/**
 * @brief Destructor de la clase Stack.
 * Libera de forma iterativa la memoria de todos los nodos en la pila
 * para prevenir fugas de memoria (memory leaks).
 */
template <typename T>
Stack<T>::~Stack() {
    while (this->head != nullptr) {
        Node<T>* temp = this->head;
        this->head = this->head->getNextNode();
        delete temp;
    }
    this->size = 0;
};