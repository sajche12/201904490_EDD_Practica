// lista_circular_doble.h
#ifndef LISTA_CIRCULAR_DOBLE_H
#define LISTA_CIRCULAR_DOBLE_H

#include <iostream>

template <typename T>
class Nodo {
public:
    T dato;
    Nodo<T>* siguiente;
    Nodo<T>* anterior;

    Nodo(T _dato) : dato(_dato), siguiente(nullptr), anterior(nullptr) {}
};

template <typename T>
class ListaCircularDoble {
private:
    Nodo<T>* cabeza;
    Nodo<T>* cola;

public:
    ListaCircularDoble() : cabeza(nullptr), cola(nullptr) {}
    ~ListaCircularDoble();

    void insertarInicio(T dato);
    void insertarFinal(T dato);
    void eliminar(T dato);
    void mostrar();
    bool estaVacia() const;
};

template <typename T>
ListaCircularDoble<T>::~ListaCircularDoble() {
    if (!estaVacia()) {
        Nodo<T>* actual = cabeza;
        do {
            Nodo<T>* siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        } while (actual != cabeza);
    }
}

template <typename T>
bool ListaCircularDoble<T>::estaVacia() const {
    return cabeza == nullptr;
}

template <typename T>
void ListaCircularDoble<T>::insertarInicio(T dato) {
    Nodo<T>* nuevoNodo = new Nodo<T>(dato);
    if (estaVacia()) {
        cabeza = cola = nuevoNodo;
        cabeza->siguiente = cabeza;
        cabeza->anterior = cabeza;
    } else {
        nuevoNodo->siguiente = cabeza;
        nuevoNodo->anterior = cola;
        cabeza->anterior = nuevoNodo;
        cola->siguiente = nuevoNodo;
        cabeza = nuevoNodo;
    }
}

template <typename T>
void ListaCircularDoble<T>::insertarFinal(T dato) {
    Nodo<T>* nuevoNodo = new Nodo<T>(dato);
    if (estaVacia()) {
        cabeza = cola = nuevoNodo;
        cabeza->siguiente = cabeza;
        cabeza->anterior = cabeza;
    } else {
        nuevoNodo->siguiente = cabeza;
        nuevoNodo->anterior = cola;
        cola->siguiente = nuevoNodo;
        cabeza->anterior = nuevoNodo;
        cola = nuevoNodo;
    }
}

template <typename T>
void ListaCircularDoble<T>::eliminar(T dato) {
    if (estaVacia()) return;

    Nodo<T>* actual = cabeza;
    do {
        if (actual->dato == dato) {
            if (actual == cabeza && actual == cola) {
                delete actual;
                cabeza = cola = nullptr;
            } else {
                actual->anterior->siguiente = actual->siguiente;
                actual->siguiente->anterior = actual->anterior;
                if (actual == cabeza) {
                    cabeza = actual->siguiente;
                }
                if (actual == cola) {
                    cola = actual->anterior;
                }
                delete actual;
            }
            return;
        }
        actual = actual->siguiente;
    } while (actual != cabeza);
}

template <typename T>
void ListaCircularDoble<T>::mostrar() {
    if (estaVacia()) {
        std::cout << "La lista está vacía." << std::endl;
        return;
    }

    Nodo<T>* actual = cabeza;
    do {
        std::cout << actual->dato << " ";
        actual = actual->siguiente;
    } while (actual != cabeza);
    std::cout << std::endl;
}

#endif // LISTA_CIRCULAR_DOBLE_H
