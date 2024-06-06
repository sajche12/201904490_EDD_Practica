// cola.h
#ifndef COLA_H
#define COLA_H

#include <iostream>
#include <stdexcept>

template <typename T>
class Cola {
private:
    // Definición de la clase Nodo como una clase anidada dentro de Cola
    class Nodo {
    public:
        T valor;
        Nodo* siguiente;

        Nodo(T val) : valor(val), siguiente(nullptr) {}
    };

    Nodo* frente;
    Nodo* fin;
    int tamano;

public:
    // Constructor
    Cola() : frente(nullptr), fin(nullptr), tamano(0) {}

    // Destructor
    ~Cola() {
        while (!estaVacia()) {
            desencolar();
        }
    }

    // Método para verificar si la cola está vacía
    bool estaVacia() const {
        return tamano == 0;
    }

    // Método para obtener el tamaño de la cola
    int obtenerTamano() const {
        return tamano;
    }

    // Método para agregar un elemento a la cola
    void encolar(const T& valor) {
        Nodo* nuevoNodo = new Nodo(valor);
        if (estaVacia()) {
            frente = fin = nuevoNodo;
        } else {
            fin->siguiente = nuevoNodo;
            fin = nuevoNodo;
        }
        tamano++;
    }

    // Método para remover y devolver el primer elemento de la cola
    T desencolar() {
        if (estaVacia()) {
            throw std::out_of_range("La cola está vacía");
        }
        Nodo* nodoAEliminar = frente;
        T valor = nodoAEliminar->valor;
        frente = frente->siguiente;
        if (frente == nullptr) {
            fin = nullptr;
        }
        delete nodoAEliminar;
        tamano--;
        return valor;
    }

    // Método para obtener el primer elemento de la cola sin removerlo
    T obtenerFrente() const {
        if (estaVacia()) {
            throw std::out_of_range("La cola está vacía");
        }
        return frente->valor;
    }
};

#endif // COLA_H
