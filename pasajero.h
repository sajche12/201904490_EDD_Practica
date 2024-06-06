#include <string>

class Pasajero {
private:
    std::string nombre;
    std::string nacionalidad;
    std::string numero_de_pasaporte;
    std::string vuelo;
    std::string asiento;
    std::string destino;
    std::string origen;
    int equipaje_facturado;

public:
    // Setters
    void setNombre(const std::string& nombre) {
        this->nombre = nombre;
    }

    void setNacionalidad(const std::string& nacionalidad) {
        this->nacionalidad = nacionalidad;
    }

    void setNumeroDePasaporte(const std::string& numero_de_pasaporte) {
        this->numero_de_pasaporte = numero_de_pasaporte;
    }

    void setVuelo(const std::string& vuelo) {
        this->vuelo = vuelo;
    }

    void setAsiento(const std::string& asiento) {
        this->asiento = asiento;
    }

    void setDestino(const std::string& destino) {
        this->destino = destino;
    }

    void setOrigen(const std::string& origen) {
        this->origen = origen;
    }

    void setEquipajeFacturado(int equipaje_facturado) {
        this->equipaje_facturado = equipaje_facturado;
    }

    // Getters
    std::string getNombre() const {
        return nombre;
    }

    std::string getNacionalidad() const {
        return nacionalidad;
    }

    std::string getNumeroDePasaporte() const {
        return numero_de_pasaporte;
    }

    std::string getVuelo() const {
        return vuelo;
    }

    std::string getAsiento() const {
        return asiento;
    }

    std::string getDestino() const {
        return destino;
    }

    std::string getOrigen() const {
        return origen;
    }

    int getEquipajeFacturado() const {
        return equipaje_facturado;
    }
};