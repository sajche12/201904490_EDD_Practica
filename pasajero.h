#include <string>

class Pasajero
{
public:
    Pasajero(const std::string &nombre, const std::string &nacionalidad, const std::string &numero_de_pasaporte,
        const std::string &vuelo, const std::string &asiento, const std::string &destino,
        const std::string &origen, const int &equipaje_facturado)
        : nombre(nombre), nacionalidad(nacionalidad), numero_de_pasaporte(numero_de_pasaporte), vuelo(vuelo),
        asiento(asiento), destino(destino), origen(origen), equipaje_facturado(equipaje_facturado) {}

    std::string getNombre() const { return nombre; }
    std::string getNacionalidad() const { return nacionalidad; }
    std::string getNumeroDePasaporte() const { return numero_de_pasaporte; }
    std::string getVuelo() const { return vuelo; }
    std::string getAsiento() const { return asiento; }
    std::string getDestino() const { return destino; }
    std::string getOrigen() const { return origen; }
    int getEquipajeFacturado() const { return equipaje_facturado; }

    // Destructor
    ~Pasajero() {}

private:
    std::string nombre;
    std::string nacionalidad;
    std::string numero_de_pasaporte;
    std::string vuelo;
    std::string asiento;
    std::string destino;
    std::string origen;
    int equipaje_facturado;
};