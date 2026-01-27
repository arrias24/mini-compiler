#include "array_list.h"
#include <iostream>

/**
 * @brief Constructor por defecto de la clase ArrayList.
 * Inicializa la lista vacía con punteros nulos y tamaño cero.
 */
template<typename T>
ArrayList<T>::ArrayList() {
    this->head = nullptr;
    this->tail = nullptr;
    this->current = nullptr;
    this->size = 0;
}

/**
 * @brief Verifica si la lista está vacía.
 * @return true si la lista no tiene elementos, false en caso contrario.
 */
template<typename T>
bool ArrayList<T>::isEmpty() {
    return this->head == nullptr;
}

/**
 * @brief Caso especial para añadir un nodo cuando la lista está vacía.
 * @param node Puntero al nodo que se convertirá en el único elemento.
 */
template<typename T>
void ArrayList<T>::addEmpty(Node<T> *node) {
    this->head = node;
    this->tail = node;
    this->current = node;
    ++this->size;
}

/**
 * @brief Añade un nodo al principio de la lista.
 * @param node Puntero al nodo a insertar.
 */
template<typename T>
void ArrayList<T>::addFirst(Node<T> *node) {
    Node<T> *temp = this->head;
    this->head = node;
    node->setNextNode(temp);
    if (temp != nullptr) {
        temp->setPreviousNode(node);
    }
    ++this->size;
}

/**
 * @brief Añade un nodo al final de la lista.
 * @param node Puntero al nodo a insertar.
 */
template<typename T>
void ArrayList<T>::addLast(Node<T> *node) {
    Node<T> *temp = this->tail;
    this->tail = node;
    node->setPreviousNode(temp);
    if (temp != nullptr) {
        temp->setNextNode(node);
    }
    ++this->size;
}

/**
 * @brief Crea un nuevo nodo con el dato proporcionado y lo inserta en la lista.
 * @param data El valor de tipo T a almacenar.
 * @param isInsertFirst Si es true, inserta al inicio; si es false, al final.
 */
template<typename T>
void ArrayList<T>::add(T data, bool isInsertFirst) {
    Node<T> *node = new Node<T>(data);
    if (this->isEmpty()) { this->addEmpty(node); return; }
    isInsertFirst ? this->addFirst(node) : this->addLast(node);
}

/**
 * @brief Obtiene el nodo en una posición específica.
 * @param index Índice del nodo (basado en 1).
 * @return Puntero al nodo encontrado o nullptr si el índice es inválido.
 */
template<typename T>
Node<T>* ArrayList<T>::get(int index) {
    Node<T> *temp = this->head;
    if (index <= 0 || index > this->size) return nullptr;
    for (int i = 0; i < this->size; i++) {
        if (i == index - 1) return temp;
        temp = temp->getNextNode();
    }
    return nullptr;
}

/**
 * @brief Obtiene el nodo apuntado por el cursor actual.
 * @return Puntero al nodo actual (current).
 */
template<typename T>
Node<T> *ArrayList<T>::get() {
    return this->current;
}

/**
 * @brief Desplaza el cursor 'current' al siguiente nodo de la lista.
 */
template<typename T>
void ArrayList<T>::next() {
    if (this->current != nullptr && this->current->getNextNode() != nullptr) this->current = this->current->getNextNode();
}

/**
 * @brief Desplaza el cursor 'current' al nodo anterior de la lista.
 */
template<typename T>
void ArrayList<T>::previous() {
    if (this->current != nullptr && this->current->getPreviousNode() != nullptr) this->current = this->current->getPreviousNode();
}

/**
 * @brief Reinicia el cursor 'current' a la cabeza de la lista.
 */
template<typename T>
void ArrayList<T>::reset() {
    this->current = this->head;
}

/**
 * @brief Obtiene el primer nodo de la lista.
 * @return Puntero al nodo head.
 */
template<typename T>
Node<T> *ArrayList<T>::getFirst() {
    return this->get(1);
}

/**
 * @brief Obtiene el último nodo de la lista.
 * @return Puntero al nodo tail.
 */
template<typename T>
Node<T> *ArrayList<T>::getLast() {
    return this->get(this->size);
}

/**
 * @brief Limpia las referencias de la lista cuando queda vacía.
 */
template<typename T>
void ArrayList<T>::removeEmpty() {
    this->head = nullptr;
    this->tail = nullptr;
    this->current = nullptr;
    this->size = 0;
}

/**
 * @brief Elimina el primer elemento de la lista (similar a pop_front).
 */
template<typename T>
void ArrayList<T>::shift() {
    if (this->isEmpty()) return;

    if (this->size == 1) {
        this->removeEmpty();
    } else {
        this->head = this->head->getNextNode();
        if (this->current == this->head->getPreviousNode()) this->current = this->head;
        this->head->setPreviousNode(nullptr);
        --this->size;
    }
}

/**
 * @brief Elimina el último elemento de la lista (similar a pop_back).
 */
template<typename T>
void ArrayList<T>::pop() {
    if (this->isEmpty()) return;

    if (this->size == 1) {
        this->removeEmpty();
    } else {
        this->tail = this->tail->getPreviousNode();
        if (this->current == this->tail->getPreviousNode()) this->current = this->tail ;
        this->tail->setNextNode(nullptr);
        --this->size;
    }
}

/**
 * @brief Lógica interna para desconectar un nodo que no es ni cabeza ni cola.
 * @param node Puntero al nodo que se desea remover.
 */
template<typename T>
void ArrayList<T>::removeMiddle(Node<T> *node) {
    Node<T> *tempNext = node->getNextNode();
    Node<T> *tempPrevious = node->getPreviousNode();
    tempPrevious->setNextNode(tempNext);
    tempNext->setPreviousNode(tempPrevious);
    if (this->current == node) this->current = tempNext;
    --this->size;
}

/**
 * @brief Elimina y retorna un nodo en un índice específico.
 * @param index Posición del elemento a eliminar.
 * @return El puntero al nodo eliminado (el usuario es responsable de su memoria).
 */
template<typename T>
Node<T>* ArrayList<T>::remove(int index) {
    Node<T> *temp = this->get(index);
    if (temp == nullptr) return nullptr;
    if (index == 1) this->shift();
    else if (index == this->size) this->pop();
    else this->removeMiddle(temp);

    temp->setNextNode(nullptr);
    temp->setPreviousNode(nullptr);
    return temp;
}

/**
 * @brief Elimina y retorna el nodo apuntado por el cursor actual.
 * Actualiza el cursor al siguiente nodo disponible.
 * @return El puntero al nodo eliminado o nullptr si el cursor es nulo.
 */
template<typename T>
Node<T> *ArrayList<T>::remove() {
    if (this->current == nullptr) return nullptr;
    Node<T>* temp = this->current;
    if (this->current != this->head && this->current != this->tail) {
        Node<T> *tempNext = this->current->getNextNode();
        Node<T> *tempPrevious = this->current->getPreviousNode();
        tempPrevious->setNextNode(tempNext);
        tempNext->setPreviousNode(tempPrevious);
        this->current = tempNext;
        --this->size;
        return temp;
    }
    if (this->current == this->head) this->shift();
    else if (this->current == this->tail) this->pop();
    return temp;
}

/**
 * @brief Elimina y retorna el primer nodo.
 * @return Puntero al nodo eliminado.
 */
template<typename T>
Node<T> *ArrayList<T>::removeFirst() {
    return this->remove(1);
}

/**
 * @brief Elimina y retorna el último nodo.
 * @return Puntero al nodo eliminado.
 */
template<typename T>
Node<T> *ArrayList<T>::removeLast() {
    return this->remove(this->size);
}

/**
 * @brief Imprime los datos de todos los nodos en la consola.
 */
template<typename T>
void ArrayList<T>::printList() {
    if (this->isEmpty()) { std::cout << "List is empty" << std::endl; return; }
    Node<T> *temp = this->head;
    while (temp != nullptr) {
        temp->print(true);
        temp = temp->getNextNode();
    }
}

/**
 * @brief Obtiene el tamaño actual de la lista.
 * @return Cantidad de elementos.
 */
template<typename T>
int ArrayList<T>::getSize() const {
    return this->size;
}

/**
 * @brief Busca si un dato existe en la lista.
 * @param data Valor a buscar.
 * @return true si el dato se encuentra en la lista, false en caso contrario.
 */
template<typename T>
bool ArrayList<T>::has(T data) {
    Node<T>* tempNode = this->head;
    for (int i = 0; i < this->size; i++) {
        if (data == tempNode->getData()) return true;
        tempNode = tempNode->getNextNode();
    }
    return false;
}

/**
 * @brief Destructor de la clase ArrayList.
 * Se encarga de liberar la memoria de todos los nodos de la lista.
 */
template<typename T>
ArrayList<T>::~ArrayList() {
    Node<T> *temp = this->head;
    while (temp != nullptr) {
        Node<T> *next = temp->getNextNode();
        delete temp;
        temp = next;
    }
    this->head = nullptr;
    this->tail = nullptr;
    this->current = nullptr;
    this->size = 0;
}