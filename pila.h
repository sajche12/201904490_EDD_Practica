#ifndef PILA_H
#define PILA_H

#include <iostream>

template <typename T>
class Pila
{
private:
    struct Nodo
    {
        T dato;
        Nodo *siguiente;
    };

    Nodo *cima;

public:
    Pila() : cima(nullptr) {}
    ~Pila();

    void apilar(const T &valor);
    void desapilar();
    T cimaPila() const;
    bool estaVacia() const;
    void limpiar();
    int obtenerTamanoPila(const Pila<T> &pila);
    T obtenerElementoPila(const Pila<T> &pila, int posicion);
};

template <typename T>
Pila<T>::~Pila()
{
    limpiar();
}

template <typename T>
void Pila<T>::apilar(const T &valor)
{
    Nodo *nuevoNodo = new Nodo{valor, cima};
    cima = nuevoNodo;
}

template <typename T>
void Pila<T>::desapilar()
{
    if (cima != nullptr)
    {
        Nodo *nodoAEliminar = cima;
        cima = cima->siguiente;
        delete nodoAEliminar;
    }
    else
    {
        std::cerr << "Error: La pila está vacía, no se puede desapilar." << std::endl;
    }
}

template <typename T>
T Pila<T>::cimaPila() const {
    if (cima != nullptr) {
        return cima->dato;
    } else {
        std::cerr << "Error: La pila está vacía, no se puede obtener la cima." << std::endl;
        throw std::runtime_error("La pila está vacía"); // Lanza una excepción en lugar de devolver un valor por defecto
    }
}

template <typename T>
bool Pila<T>::estaVacia() const
{
    return cima == nullptr;
}

template <typename T>
void Pila<T>::limpiar()
{
    while (!estaVacia())
    {
        desapilar();
    }
}

// Metodo para obtener el tamaño de la pila sin que reciba parametros
template <typename T>
int obtenerTamanoPila(const Pila<T> &pila)
{
    int tamano = 0;
    typename Pila<T>::Nodo *nodoActual = pila.cima;
    while (nodoActual != nullptr)
    {
        tamano++;
        nodoActual = nodoActual->siguiente;
    }
    return tamano;
}



// Metodo para obtener un elemento de la pila
template <typename T>
T obtenerElementoPila(const Pila<T> &pila, int posicion)
{
    if (posicion < 0)
    {
        std::cerr << "Error: La posición no puede ser negativa." << std::endl;
        return T(); // Devuelve un valor por defecto
    }

    typename Pila<T>::Nodo *nodoActual = pila.cima;
    for (int i = 0; i < posicion && nodoActual != nullptr; i++)
    {
        nodoActual = nodoActual->siguiente;
    }

    if (nodoActual != nullptr)
    {
        return nodoActual->dato;
    }
    else
    {
        std::cerr << "Error: La posición está fuera de rango." << std::endl;
        return T(); // Devuelve un valor por defecto
    }
}

#endif // PILA_H
