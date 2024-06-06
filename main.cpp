// Definicion de librerias
#include <iostream>
#include <fstream>
#include <string>
#include "include/json.hpp"
#include "listaCircularDoble.h"
#include "cola.h"
#include "pila.h"
#include "avion.h"
#include "pasajero.h"

using namespace std;
using json = nlohmann::json;

// Prototipos de funciones
bool cargar_aviones(const string& aviones, json& j);
void cargar_pasajeros();
void cargar_movimientos();
void consultar_pasajero();
void reportes();
int contar_objetos(const json& j);

// Variables globales
ListaCircularDoble<Avion> aviones;


// Función principal
int main() {
    int opcion;

    do {
        cout << "*******************************" << endl;
        cout << "*        MENU PRINCIPAL       *" << endl;
        cout << "*  1. Carga de Aviones        *" << endl;
        cout << "*  2. Carga de Pasajeros      *" << endl;
        cout << "*  3. Carga de Movimientos    *" << endl;
        cout << "*  4. Consultar Pasajero      *" << endl;
        cout << "*  5. Visualizar Reportes     *" << endl;
        cout << "*  6. Salir                   *" << endl;
        cout << "*******************************" << endl;
        cout << "Selecciona una opción: ";
        cin >> opcion;
        
        const string aviones = "aviones.json";
        json j;
        
        switch (opcion) {
            case 1:
                cargar_aviones(aviones, j);
                break;
            case 2:
                cargar_pasajeros();
                break;
            case 3:
                cargar_movimientos();
                break;
            case 4:
                consultar_pasajero();
                break;
            case 5:
                reportes();
                break;
            case 6:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opción no válida. Inténtalo de nuevo." << endl;
        }

    } while (opcion != 6);

    return 0;
}

// Definición de funciones
bool cargar_aviones(const string& aviones, json& j) {
    ifstream file(aviones);
    if (file.is_open()) {
        // Mostrar el contenido del archivo
        cout << "Contenido del archivo " << aviones << ":" << endl;
        cout << file.rdbuf() << endl;
        file.close();
    } else {
        cerr << "Error al abrir el archivo " << aviones << endl;
        return false;


    }

    try {
        file >> j;
    } catch (json::parse_error& e) {
        cerr << "Error al parsear el JSON: " << e.what() << endl;
        return false;
    }

    return true;
}

void cargar_pasajeros() {
    cout << "Has seleccionado la opción 2." << endl;
}

void cargar_movimientos() {
    cout << "Has seleccionado la opción 3." << endl;
}

void consultar_pasajero() {
    cout << "Has seleccionado la opción 4." << endl;
}

void reportes() {
    cout << "Has seleccionado la opción 5." << endl;
}

int contar_objetos(const json& j) {
    if (j.is_object()) {
        return j.size();
    } else {
        return 0;
    }
}