#ifndef PILA_H
#define PILA_H

#include <iostream>

template <typename T>
class Pila {
private:
    struct Nodo {
        T dato;
        Nodo* siguiente;
    };

    Nodo* cima;

public:
    Pila() : cima(nullptr) {}
    ~Pila();

    void apilar(const T& valor);
    void desapilar();
    T cimaPila() const;
    bool estaVacia() const;
    void limpiar();
};

template <typename T>
Pila<T>::~Pila() {
    limpiar();
}

template <typename T>
void Pila<T>::apilar(const T& valor) {
    Nodo* nuevoNodo = new Nodo{valor, cima};
    cima = nuevoNodo;
}

template <typename T>
void Pila<T>::desapilar() {
    if (cima != nullptr) {
        Nodo* nodoAEliminar = cima;
        cima = cima->siguiente;
        delete nodoAEliminar;
    } else {
        std::cerr << "Error: La pila está vacía, no se puede desapilar." << std::endl;
    }
}

template <typename T>
T Pila<T>::cimaPila() const {
    if (cima != nullptr) {
        return cima->dato;
    } else {
        std::cerr << "Error: La pila está vacía, no se puede obtener la cima." << std::endl;
        return T(); // Devuelve un valor por defecto
    }
}

template <typename T>
bool Pila<T>::estaVacia() const {
    return cima == nullptr;
}

template <typename T>
void Pila<T>::limpiar() {
    while (!estaVacia()) {
        desapilar();
    }
}

#endif // PILA_H
