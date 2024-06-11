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

    // Metodo para obtener el tamaño de la lista
    int obtenerTamano() const {
        int tamano = 0;
        Node<T>* actual = cabeza;
        while (actual != nullptr) {
            tamano++;
            actual = actual->siguiente;
        }
        return tamano;
    }

    // Metodo para obtener un elemento de la lista
    T obtenerElemento(int pos) const {
        if (pos < 0 || pos >= obtenerTamano()) {
            throw std::out_of_range("Posición inválida");
        }
        Node<T>* actual = cabeza;
        for (int i = 0; i < pos; i++) {
            actual = actual->siguiente;
        }
        return actual->dato;
    }

    // Metodo para ordenar ascendentemente por numero de vuelo
    void ordenarPorNumeroDeVuelo() {
        if (cabeza == nullptr) {
            return;
        }

        Node<T>* actual = cabeza;
        while (actual->siguiente != nullptr) {
            Node<T>* siguiente = actual->siguiente;
            while (siguiente != nullptr) {
                if (actual->dato.getVuelo() > siguiente->dato.getVuelo()) {
                    T temp = actual->dato;
                    actual->dato = siguiente->dato;
                    siguiente->dato = temp;
                }
                siguiente = siguiente->siguiente;
            }
            actual = actual->siguiente;
        }
    }

    // Metodo para ordenar ascendentemente por numero de asiento
    void ordenarPorNumeroDeAsiento() {
        if (cabeza == nullptr) {
            return;
        }

        Node<T>* actual = cabeza;
        while (actual->siguiente != nullptr) {
            Node<T>* siguiente = actual->siguiente;
            while (siguiente != nullptr) {
                if (actual->dato.getAsiento() > siguiente->dato.getAsiento()) {
                    T temp = actual->dato;
                    actual->dato = siguiente->dato;
                    siguiente->dato = temp;
                }
                siguiente = siguiente->siguiente;
            }
            actual = actual->siguiente;
        }
    }
};

#endif // LISTA_DOBLE_ENLAZADA_H
