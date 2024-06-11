#ifndef LISTA_DOBLE_ENLAZADA_H
#define LISTA_DOBLE_ENLAZADA_H

#include <iostream>
#include <stdexcept> // Para manejar excepciones
#include <string> // Para manejar cadenas de texto

template <typename T>
class Node {
public:
    T dato;
    Node<T>* siguiente;
    Node<T>* anterior;

    Node(T dato) : dato(dato), siguiente(nullptr), anterior(nullptr) {}
};

template <typename T>
class ListaDobleEnlazada {
private:
    Node<T>* cabeza;
    Node<T>* cola;

public:
    ListaDobleEnlazada() : cabeza(nullptr), cola(nullptr) {}

    ~ListaDobleEnlazada() {
        Node<T>* actual = cabeza;
        while (actual != nullptr) {
            Node<T>* siguiente = actual->siguiente;
            delete actual;
            actual = siguiente;
        }
    }

    void insertarAlInicio(T dato) {
        Node<T>* nuevoNodo = new Node<T>(dato);
        if (cabeza == nullptr) {
            cabeza = cola = nuevoNodo;
        } else {
            nuevoNodo->siguiente = cabeza;
            cabeza->anterior = nuevoNodo;
            cabeza = nuevoNodo;
        }
    }

    void insertarAlFinal(T dato) {
        Node<T>* nuevoNodo = new Node<T>(dato);
        if (cola == nullptr) {
            cabeza = cola = nuevoNodo;
        } else {
            nuevoNodo->anterior = cola;
            cola->siguiente = nuevoNodo;
            cola = nuevoNodo;
        }
    }

    void eliminarDelInicio() {
        if (cabeza != nullptr) {
            Node<T>* nodoAEliminar = cabeza;
            cabeza = cabeza->siguiente;
            if (cabeza != nullptr) {
                cabeza->anterior = nullptr;
            } else {
                cola = nullptr;
            }
            delete nodoAEliminar;
        }
    }

    void eliminarDelFinal() {
        if (cola != nullptr) {
            Node<T>* nodoAEliminar = cola;
            cola = cola->anterior;
            if (cola != nullptr) {
                cola->siguiente = nullptr;
            } else {
                cabeza = nullptr;
            }
            delete nodoAEliminar;
        }
    }

    T obtenerPrimero() const {
        if (cabeza == nullptr) {
            throw std::out_of_range("La lista está vacía");
        }
        return cabeza->dato;
    }

    T buscarPorNumeroDePasaporte(const std::string& numeroDePasaporte) const {
        Node<T>* actual = cabeza;
        while (actual != nullptr) {
            if (actual->dato.getNumeroDePasaporte() == numeroDePasaporte) {
                return actual->dato;
            }
            actual = actual->siguiente;
        }
        throw std::runtime_error("No se encontró un objeto con el número de pasaporte proporcionado");
    }

    void imprimirLista() const {
        Node<T>* actual = cabeza;
        while (actual != nullptr) {
            std::cout << actual->dato << " ";
            actual = actual->siguiente;
        }
        std::cout << std::endl;
    }
};

#endif // LISTA_DOBLE_ENLAZADA_H
