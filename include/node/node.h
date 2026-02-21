#ifndef NODE_H
#define NODE_H

#include <iostream>

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

/**
 * @file node.cpp
 * @brief Implementación de la clase Node para listas doblemente enlazadas
 * @tparam T Tipo de dato almacenado en el nodo
 */

/**
 * @brief Constructor de la clase Node
 * @tparam T Tipo de dato almacenado en el nodo
 * @param data Dato a almacenar en el nodo
 *
 * @details Crea un nuevo nodo con el dato proporcionado y punteros next/previous
 *          inicializados a nullptr.
 */
template <typename T>
Node<T>::Node(T data) {
    this->data = data;
}

/**
 * @brief Establece el dato almacenado en el nodo
 * @tparam T Tipo de dato almacenado en el nodo
 * @param data Nuevo dato a almacenar
 *
 * @note Este método sobrescribe cualquier dato previamente almacenado
 */
template <typename T>
void Node<T>::setData(T data) {
    this->data = data;
}

/**
 * @brief Obtiene el dato almacenado en el nodo
 * @tparam T Tipo de dato almacenado en el nodo
 * @return El dato almacenado en el nodo
 *
 * @warning Retorna una copia del dato, no una referencia.
 */
template <typename T>
T Node<T>::getData() {
    return this->data;
}

/**
 * @brief Obtiene el siguiente nodo en la lista
 * @tparam T Tipo de dato almacenado en el nodo
 * @return Puntero al siguiente nodo, o nullptr si es el último
 */
template <typename T>
Node<T>* Node<T>::getNextNode() {
    return this->next;
}

/**
 * @brief Establece el siguiente nodo en la lista
 * @tparam T Tipo de dato almacenado en el nodo
 * @param nextNode Puntero al nuevo nodo siguiente
 *
 * @note Si se establece a nullptr, este nodo se convierte en el último
 */
template <typename T>
void Node<T>::setNextNode(Node<T>* nextNode) {
    this->next = nextNode;
}

/**
 * @brief Obtiene el nodo anterior en la lista
 * @tparam T Tipo de dato almacenado en el nodo
 * @return Puntero al nodo anterior, o nullptr si es el primero
 */
template <typename T>
Node<T>* Node<T>::getPreviousNode() {
    return this->previous;
}

/**
 * @brief Establece el nodo anterior en la lista
 * @tparam T Tipo de dato almacenado en el nodo
 * @param previousNode Puntero al nuevo nodo anterior
 *
 * @note Si se establece a nullptr, este nodo se convierte en el primero
 */
template <typename T>
void Node<T>::setPreviousNode(Node<T>* previousNode) {
    this->previous = previousNode;
}

/**
 * @brief Imprime datos primitivos (tipos básicos con operator<<)
 * @tparam T Tipo de dato almacenado en el nodo
 *
 * @details Imprime el dato usando std::cout. Solo funciona para tipos
 *          que tienen definido operator<< (int, float, string, etc.)
 *
 * @pre T debe tener operator<< definido
 * @throw No lanza excepciones directamente, pero operator<< de T podría
 */
template <typename T>
void Node<T>::printPrimitive() {
    std::cout << this->data << std::endl;
}

/**
 * @brief Método para imprimir estructuras (implementación vacía)
 * @tparam T Tipo de dato almacenado en el nodo
 *
 * @details Esta función debe ser especializada para cada tipo de estructura
 *          que se desee imprimir. Por defecto no hace nada.
 *
 * @see Para usar con estructuras, crear especializaciones:
 * @code{.cpp}
 * template <>
 * void Node<Persona>::printStruct() {
 *     std::cout << nombre << " - " << edad << std::endl;
 * }
 * @endcode
 */
template <typename T>
void Node<T>::printStruct() {
    // Implementación por defecto vacía
    // Debe ser especializada para tipos específicos
}

/**
 * @brief Método principal para imprimir el contenido del nodo
 * @tparam T Tipo de dato almacenado en el nodo
 * @param isPrimitive true para tipos primitivos, false para estructuras
 *
 * @details Decide automáticamente qué método de impresión usar según
 *          el parámetro isPrimitive:
 *          - true: usa printPrimitive() (tipos básicos)
 *          - false: usa printStruct() (estructuras personalizadas)
 *
 * @note Para estructuras, se debe crear una especialización de printStruct()
 *
 * @example
 * @code{.cpp}
 * // Para tipos primitivos
 * Node<int> nodeInt(42);
 * nodeInt.print(true);  // Imprime: 42
 *
 * // Para estructuras (requiere especialización)
 * Node<Persona> nodePersona(Persona{"Juan", 25});
 * nodePersona.print(false);  // Requiere Node<Persona>::printStruct()
 * @endcode
 */
template <typename T>
void Node<T>::print(bool isPrimitive) {
    if (isPrimitive) {
        printPrimitive();
    } else {
        printStruct();
    }
}
#endif