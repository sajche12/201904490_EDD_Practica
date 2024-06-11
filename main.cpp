// Definicion de librerias
#include <iostream>
#include <fstream>
#include <string>
#include "listaCircularDoble.h"
#include "cola.h"
#include "pila.h"
#include "listaDobleEnlazada.h"
#include "avion.h"
#include "pasajero.h"
#include "jsoncpp.cpp"
#include "json/json.h"
#include <cstdlib>

using namespace std;

// Prototipos de funciones
void cargar_aviones();
void cargar_pasajeros();
void cargar_movimientos();
void consultar_pasajero();
void reportes();
void reporte_aviones_disponibles();
void reporte_aviones_mantenimiento();
void reporte_cola_pasajeros();

// Variables globales
ListaCircularDoble<Avion> listaAvionesDisponible;
ListaCircularDoble<Avion> listaAvionesMantenimiento;
Cola<Pasajero> colaPasajeros;
Pila<Pasajero> equipajePasajeros;
ListaDobleEnlazada<Pasajero> listaEquipaje;

// Función principal
int main() {
    int opcion_reporte;

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
        cin >> opcion_reporte;
        
        switch (opcion_reporte) {
            case 1:
                cargar_aviones();
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

    } while (opcion_reporte != 6);

    return 0;
}

// Definición de funciones
void cargar_aviones() {
    // Nombre del archivo JSON avionNuevo leer
    string filename = "aviones.json";

    // Crear un objeto ifstream para leer el archivo
    ifstream ifs(filename, ifstream::binary);

    // Verificar si el archivo se abrió correctamente
    if (!ifs.is_open()) {
        cerr << "No se pudo abrir el archivo: " << filename << endl;
        //return 1;
    }

    // Crear un objeto Json::Value para almacenar los datos JSON
    Json::Value root;

    // Crear un objeto Json::CharReaderBuilder para parsear el JSON
    Json::CharReaderBuilder builder;
    string errs;

    // Parsear el archivo JSON
    bool parsingSuccessful = Json::parseFromStream(builder, ifs, &root, &errs);
    if (!parsingSuccessful) {
        cerr << "Error al parsear el archivo JSON: " << errs << endl;
        //return 1;
    }

    // Cerrar el archivo
    ifs.close();

    for (const auto& avion : root) {
        // Crear un objeto Avion utilizando setters
        Avion avionNuevo(avion["vuelo"].asString(), avion["numero_de_registro"].asString(), avion["modelo"].asString(),
                avion["fabricante"].asString(), avion["ano_fabricacion"].asInt(), avion["capacidad"].asInt(),
                avion["peso_max_despegue"].asInt(), avion["aerolinea"].asString(), avion["estado"].asString());

        // Agregar el avión avionNuevo a la lista de aviones verificando su estado
        if (avionNuevo.getEstado() == "Disponible") {
            listaAvionesDisponible.insertar(avionNuevo);
        } else if (avionNuevo.getEstado() == "Mantenimiento") {
            listaAvionesMantenimiento.insertar(avionNuevo);
        }
    }
    cout << "\nAviones cargados exitosamente.\n" << endl;
}

void cargar_pasajeros() {
    // Nombre del archivo JSON avionNuevo leer
    string filename = "pasajeros.json";

    // Crear un objeto ifstream para leer el archivo
    ifstream ifs(filename, ifstream::binary);

    // Verificar si el archivo se abrió correctamente
    if (!ifs.is_open()) {
        cerr << "No se pudo abrir el archivo: " << filename << endl;
        //return 1;
    }

    // Crear un objeto Json::Value para almacenar los datos JSON
    Json::Value root;

    // Crear un objeto Json::CharReaderBuilder para parsear el JSON
    Json::CharReaderBuilder builder;
    string errs;

    // Parsear el archivo JSON
    bool parsingSuccessful = Json::parseFromStream(builder, ifs, &root, &errs);
    if (!parsingSuccessful) {
        cerr << "Error al parsear el archivo JSON: " << errs << endl;
        //return 1;
    }

    // Cerrar el archivo
    ifs.close();

    // Recorrer el arreglo de pasajeros
    for (const auto& pasajero : root) {
        // Verificar si el pasajero contiene el atributo pasajero["equipaje_facturado"].asInt()
        if (!pasajero.isMember("equipaje_facturado")) {
            // Crear el objeto pasajero sin el atributo equipaje_facturado
            Pasajero pasajeroNuevo(pasajero["nombre"].asString(), pasajero["nacionalidad"].asString(),
                    pasajero["numero_de_pasaporte"].asString(), pasajero["vuelo"].asString(),
                    pasajero["asiento"].asString(), pasajero["destino"].asString(),
                    pasajero["origen"].asString(), 0);
            colaPasajeros.encolar(pasajeroNuevo);
        } else {
            // Crear el objeto pasajero con el atributo equipaje_facturado
            Pasajero pasajeroNuevo(pasajero["nombre"].asString(), pasajero["nacionalidad"].asString(),
                    pasajero["numero_de_pasaporte"].asString(), pasajero["vuelo"].asString(),
                    pasajero["asiento"].asString(), pasajero["destino"].asString(),
                    pasajero["origen"].asString(), pasajero["equipaje_facturado"].asInt());
            colaPasajeros.encolar(pasajeroNuevo);
        }
    }
    cout << "\nPasajeros cargados exitosamente.\n" << endl;
}

void cargar_movimientos() {
    ifstream file("movimientos.txt");
    string linea;

    if (file.is_open()) {
        cout << "\nMovimientos realizados:" << endl;
        while (getline(file, linea)) {
            if (linea == "IngresoEquipajes;") {
                // El primer pasajero de la cola agregarlo a la pila y la listaEquipaje y equipajePasajeros
                Pasajero pasajero = colaPasajeros.desencolar();
                // verificar si el pasajero contiene el atributo equipaje_facturado
                if (pasajero.getEquipajeFacturado() > 0) {
                    equipajePasajeros.apilar(pasajero);
                    listaEquipaje.insertarAlInicio(pasajero);
                    cout << "El pasajero " << pasajero.getNombre() << " con número de pasaporte " << pasajero.getNumeroDePasaporte() << " tiene equipaje facturado." << endl;
                } else if (pasajero.getEquipajeFacturado() == 0){
                    listaEquipaje.insertarAlInicio(pasajero);
                    cout << "El pasajero " << pasajero.getNombre() << " con número de pasaporte " << pasajero.getNumeroDePasaporte() << " no tiene equipaje facturado." << endl;
                    // Ordenar los pasajeros por orden de vuelo y asiento

                }
            } else if (linea.find("MantenimientoAviones,Ingreso,") == 0) {
                string cambioEstado = "Mantenimiento";
                // Extraer el texto después de la coma y antes del punto y coma
                string texto = linea.substr(29, linea.find(";") - 29);
                // Buscar el avión en la listaAvionesDisponible a travez del metodo buscarPorNumeroDeRegistro
                Avion* avion = listaAvionesDisponible.buscarPorNumeroDeRegistro(texto);
                // Verificar si se encontró el avión
                if (avion != nullptr) {
                    // Cambiar el estado del avión a "Mantenimiento"
                    Avion avionMantenimiento(avion->getVuelo(), avion->getNumeroRegistro(), avion->getModelo(),
                    avion->getFabricante(), avion->getAnoFabricacion(), avion->getCapacidad(),
                    avion->getPesoMaxDespegue(), avion->getAerolinea(), cambioEstado);
                    // Agregarlo a la listaAvionesMantenimiento
                    listaAvionesMantenimiento.insertar(avionMantenimiento);
                    // Eliminarlo de la listaAvionesDisponible
                    listaAvionesDisponible.eliminarPorNumeroDeRegistro(texto);
                    cout << "El avión con número de registro " << texto << " ha ingresado a mantenimiento." << endl;
                } else {
                    std::cout << "No se encontró el avión con número de registro: " << texto << std::endl;
                }
            } else if (linea.find("MantenimientoAviones,Salida,") == 0) {
                string cambioEstado = "Disponible";
                // Extraer el texto después de la coma y antes del punto y coma
                string texto = linea.substr(28, linea.find(";") - 28);
                // Buscar el avión en la listaAvionesDisponible a travez del metodo buscarPorNumeroDeRegistro
                Avion* avion = listaAvionesMantenimiento.buscarPorNumeroDeRegistro(texto);
                // Verificar si se encontró el avión
                if (avion != nullptr) {
                    // Cambiar el estado del avión a "Mantenimiento"
                    Avion avionMantenimiento(avion->getVuelo(), avion->getNumeroRegistro(), avion->getModelo(),
                    avion->getFabricante(), avion->getAnoFabricacion(), avion->getCapacidad(),
                    avion->getPesoMaxDespegue(), avion->getAerolinea(), cambioEstado);
                    // Agregarlo a la listaAvionesMantenimiento
                    listaAvionesDisponible.insertar(avionMantenimiento);
                    // Eliminarlo de la listaAvionesDisponible
                    listaAvionesMantenimiento.eliminarPorNumeroDeRegistro(texto);
                    cout << "El avión con número de registro " << texto << " ha salido de mantenimiento." << endl;
                } else {
                    std::cout << "No se encontró el avión con número de registro: " << texto << std::endl;
                }
            } else {
                cout << "La línea no cumple con ninguna de las condiciones" << endl;
            }
        }
        cout << endl;
        file.close();
    } else {
        cout << "No se pudo abrir el archivo " << endl;
    }
}

void consultar_pasajero() {
    cout << "Ingrese el numero de pasaporte del pasajero: ";
    string numeroPasaporte;
    cin >> numeroPasaporte;
    // Buscar el pasajero en la listaEquipaje a travez del metodo buscarPorNumeroDePasaporte
    try {
        Pasajero pasajero = listaEquipaje.buscarPorNumeroDePasaporte(numeroPasaporte);
        cout << "\nInformación del pasajero: " << endl;
        cout << "Nombre: " << pasajero.getNombre() << endl;
        cout << "Nacionalidad: " << pasajero.getNacionalidad() << endl;
        cout << "Numero de pasaporte: " << pasajero.getNumeroDePasaporte() << endl;
        cout << "Vuelo: " << pasajero.getVuelo() << endl;
        cout << "Asiento: " << pasajero.getAsiento() << endl;
        cout << "Destino: " << pasajero.getDestino() << endl;
        cout << "Origen: " << pasajero.getOrigen() << endl;
        cout << "Equipaje facturado: " << pasajero.getEquipajeFacturado() << endl;
        cout << endl;
    } catch (const std::runtime_error& e) {
        cerr << e.what() << endl;
    }

}

void reportes() {
    int opcion_reporte;

    cout << endl;
    cout << "*******************************" << endl;
    cout << "*        MENU REPORTES        *" << endl;
    cout << "*  1. Aviones Disponibles     *" << endl;
    cout << "*  2. Aviones en Mantenimiento*" << endl;
    cout << "*  3. Cola de Registro        *" << endl;
    cout << "*  4. Pila de Equipaje        *" << endl;
    cout << "*  5. Lista de Pasajeros      *" << endl;
    cout << "*  6. Regresar                *" << endl;
    cout << "*******************************" << endl;
    cout << endl;

    do {
        cout << "Selecciona una opción: ";
        cin >> opcion_reporte;

        switch (opcion_reporte) {
            case 1:
                reporte_aviones_disponibles();
                break;
            case 2:
                reporte_aviones_mantenimiento();
                break;
            case 3:
                reporte_cola_pasajeros();
                break;
            case 4:
                cout << "\nEquipaje de Pasajeros:" << endl;
                
                cout << endl;
                break;
            case 5:
                cout << "Saliendo..." << endl;
                break;
            case 6:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opción no válida. Inténtalo de nuevo." << endl;
        }

    } while (opcion_reporte != 6);
}

void reporte_aviones_disponibles() {
    ofstream file("aviones_disponibles.dot");
    file << "digraph AvionesDisponibles {" << endl;
    // Recorre la lista de aviones disponibles y los imprime en el archivo .dot utiliza un for para recorrer la lista, agrega todos los atributos
    for (int i = 0; i < listaAvionesDisponible.obtenerTamano(); i++) {
        Avion avion = listaAvionesDisponible.obtenerElemento(i);
        file << "    " << avion.getNumeroRegistro() << " [label=\"" << avion.getNumeroRegistro() << "\\n" << avion.getModelo() << "\\n" << avion.getFabricante() << "\\n" << avion.getAnoFabricacion() << "\\n" << avion.getCapacidad() << "\\n" << avion.getPesoMaxDespegue() << "\\n" << avion.getAerolinea() << "\"];" << endl;
    }
    file << "}" << endl;
    file.close();

    // Genera la imagen utilizando Graphviz
    system("dot -Tpng aviones_disponibles.dot -o aviones_disponibles.png");
}

void reporte_aviones_mantenimiento() {
    ofstream file("aviones_mantenimiento.dot");
    file << "digraph AvionesMantenimiento {" << endl;
    // Recorre la lista de aviones en mantenimiento y los imprime en el archivo .dot utiliza un for para recorrer la lista, agrega todos los atributos
    for (int i = 0; i < listaAvionesMantenimiento.obtenerTamano(); i++) {
        Avion avion = listaAvionesMantenimiento.obtenerElemento(i);
        file << "    " << avion.getNumeroRegistro() << " [label=\"" << avion.getNumeroRegistro() << "\\n" << avion.getModelo() << "\\n" << avion.getFabricante() << "\\n" << avion.getAnoFabricacion() << "\\n" << avion.getCapacidad() << "\\n" << avion.getPesoMaxDespegue() << "\\n" << avion.getAerolinea() << "\"];" << endl;
    }
    file << "}" << endl;
    file.close();

    // Genera la imagen utilizando Graphviz
    system("dot -Tpng aviones_mantenimiento.dot -o aviones_mantenimiento.png");
}

void reporte_cola_pasajeros() {
    ofstream file("cola_pasajeros.dot");
    file << "digraph ColaPasajeros {" << endl;
    // Recorre la cola de pasajeros y los imprime en el archivo .dot utiliza un for para recorrer la cola, agrega todos los atributos
    file << "    node [shape=record];" << endl;
    file << "    cola [label=\"{Cola de Pasajeros | ";
    for (int i = 0; i < colaPasajeros.obtenerTamano(); i++) {
        Pasajero pasajero = colaPasajeros.obtenerElemento(i);
        file << "<" << i << "> " << pasajero.getNombre() << " | ";
    }
    file << "}\"];" << endl;
    file << "}" << endl;
    file.close();

    // Genera la imagen utilizando Graphviz
    system("dot -Tpng cola_pasajeros.dot -o cola_pasajeros.png");
}