#include "array_list.h"
#include <iostream>

/**
 * @brief Constructor por defecto de la clase ArrayList.
 * Inicializa una lista doblemente enlazada vacía, estableciendo los punteros
 * de control (head, tail, current) a nullptr y el contador de tamaño a cero.
 */
template<typename T>
ArrayList<T>::ArrayList() {
    this->head = nullptr;
    this->tail = nullptr;
    this->current = nullptr;
    this->size = 0;
}

/**
 * @brief Verifica el estado de vacuidad de la lista.
 * @return true si la lista no contiene elementos (head es nulo), false en caso contrario.
 */
template<typename T>
bool ArrayList<T>::isEmpty() {
    return this->head == nullptr;
}

/**
 * @brief Gestiona la inserción del primer elemento en una lista vacía.
 * @note Este es un método privado de soporte técnico para unificar la lógica de inserción.
 * @param node Puntero al nuevo nodo que actuará simultáneamente como cabeza, cola y cursor.
 */
template<typename T>
void ArrayList<T>::addWhenEmpty(Node<T> *node) {
    this->head = node;
    this->tail = node;
    this->current = node;
    ++this->size;
}

/**
 * @brief Inserta un nuevo elemento al inicio de la lista.
 * Crea un nuevo nodo y reestructura los punteros para desplazar la antigua cabeza.
 * @param data Valor de tipo T a almacenar en el nuevo nodo.
 */
template<typename T>
void ArrayList<T>::addFirst(T data) {
    Node<T> *node = new Node<T>(data);
    if (this->isEmpty()) {
        this->addWhenEmpty(node);
        return;
    }

    Node<T> *temp = this->head;
    this->head = node;
    node->setNextNode(temp);
    if (temp != nullptr) {
        temp->setPreviousNode(node);
    }
    ++this->size;
}

/**
 * @brief Inserta un nuevo elemento al final de la lista.
 * Extiende la lista desde el nodo 'tail' actual y actualiza la referencia de la cola.
 * @param data Valor de tipo T a almacenar en el nuevo nodo.
 */
template<typename T>
void ArrayList<T>::addLast(T data) {
    Node<T> *node = new Node<T>(data);
    if (this->isEmpty()) {
        this->addWhenEmpty(node);
        return;
    }
    Node<T> *temp = this->tail;
    this->tail = node;
    node->setPreviousNode(temp);
    if (temp != nullptr) {
        temp->setNextNode(node);
    }
    ++this->size;
}

/**
 * @brief Localiza un nodo basado en su posición secuencial.
 * @param index Índice entero del nodo (rango válido: 1 a n).
 * @return Puntero al Node<T> encontrado; nullptr si el índice está fuera de rango.
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
 * @brief Accede al nodo apuntado por el cursor de navegación.
 * @return Puntero al nodo 'current' actual. Puede ser nullptr si la lista está vacía.
 */
template<typename T>
Node<T> *ArrayList<T>::get() {
    return this->current;
}

/**
 * @brief Avanza el cursor de navegación al siguiente nodo.
 * @return true si el desplazamiento fue exitoso; false si el cursor es nulo o ya se encuentra en la cola.
 */
template<typename T>
bool ArrayList<T>::currentNext() {
    if (this->current != nullptr && this->current->getNextNode() != nullptr) {
        this->current = this->current->getNextNode();
        return true;
    }
    return false;
}

/**
 * @brief Retrocede el cursor de navegación al nodo anterior.
 * @return true si el desplazamiento fue exitoso; false si el cursor es nulo o ya se encuentra en la cabeza.
 */
template<typename T>
bool ArrayList<T>::currentPrevious() {
    if (this->current != nullptr && this->current->getPreviousNode() != nullptr) {
        this->current = this->current->getPreviousNode();
        return true;
    }
    return false;
}

/**
 * @brief Reposiciona el cursor de navegación al inicio de la lista.
 */
template<typename T>
void ArrayList<T>::currentReset() {
    this->current = this->head;
}

/**
 * @brief Consulta el nodo posterior al cursor sin modificar la posición de este.
 * @return Puntero al nodo siguiente; nullptr si no existe un nodo posterior.
 */
template<typename T>
Node<T>* ArrayList<T>::currentPeek() {
    if (this->current == nullptr || this->current == this->tail) return nullptr;
    return this->current->getNextNode();
}

/**
 * @brief Recupera la referencia al primer elemento.
 * @return Puntero al nodo cabeza (head).
 */
template<typename T>
Node<T> *ArrayList<T>::getFirst() {
    return this->get(1);
}

/**
 * @brief Recupera la referencia al último elemento.
 * @return Puntero al nodo cola (tail).
 */
template<typename T>
Node<T> *ArrayList<T>::getLast() {
    return this->get(this->size);
}

/**
 * @brief Reinicia las propiedades de control de la lista.
 * Método interno invocado cuando la eliminación de un nodo deja la lista sin elementos.
 */
template<typename T>
void ArrayList<T>::removeWhenEmpty() {
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
        this->removeWhenEmpty();
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
void ArrayList<T>::unshift() {
    if (this->isEmpty()) return;

    if (this->size == 1) {
        this->removeWhenEmpty();
    } else {
        this->tail = this->tail->getPreviousNode();
        if (this->current == this->tail->getPreviousNode()) this->current = this->tail ;
        this->tail->setNextNode(nullptr);
        --this->size;
    }
}

/**
 * @brief Desvincula un nodo intermedio mediante la reestructuración de enlaces adyacentes.
 * @param node Puntero al nodo que se desea extraer. Debe ser un nodo intermedio (no head ni tail).
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
    else if (index == this->size) this->unshift();
    else this->removeMiddle(temp);

    temp->setNextNode(nullptr);
    temp->setPreviousNode(nullptr);
    return temp;
}

/**
 * @brief Desvincula y retorna el primer elemento de la lista.
 * @return Puntero al nodo que ocupaba la posición 1.
 */
template<typename T>
Node<T> *ArrayList<T>::removeFirst() {
    return this->remove(1);
}

/**
 * @brief Desvincula y retorna el último elemento de la lista.
 * @return Puntero al nodo que ocupaba la posición n.
 */
template<typename T>
Node<T> *ArrayList<T>::removeLast() {
    return this->remove(this->size);
}

/**
 * @brief Serializa y muestra el contenido de la lista en la salida estándar.
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
 * @brief Consulta la dimensión actual de la lista.
 * @return Entero con el número total de nodos.
 */
template<typename T>
int ArrayList<T>::getSize() const {
    return this->size;
}

/**
 * @brief Realiza una búsqueda lineal para determinar la existencia de un valor.
 * @param data Valor de tipo T a comparar con el contenido de cada nodo.
 * @return true si existe al menos una coincidencia; false si se recorre toda la lista sin éxito.
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
 * Recorre la estructura de forma iterativa eliminando cada nodo para asegurar
 * una liberación completa de la memoria dinámica (Heap).
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