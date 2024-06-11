#include <string>

class Avion
{
public:
    Avion(const std::string &vuelo, const std::string &numeroRegistro, const std::string &modelo,
        const std::string &fabricante, int anoFabricacion, int capacidad, int pesoMaxDespegue,
        const std::string &aerolinea, const std::string &estado)
        : vuelo(vuelo), numeroRegistro(numeroRegistro), modelo(modelo), fabricante(fabricante),
        anoFabricacion(anoFabricacion), capacidad(capacidad), pesoMaxDespegue(pesoMaxDespegue),
        aerolinea(aerolinea), estado(estado) {}

    std::string getVuelo() const { return vuelo; }
    std::string getNumeroRegistro() const { return numeroRegistro; }
    std::string getModelo() const { return modelo; }
    std::string getFabricante() const { return fabricante; }
    int getAnoFabricacion() const { return anoFabricacion; }
    int getCapacidad() const { return capacidad; }
    int getPesoMaxDespegue() const { return pesoMaxDespegue; }
    std::string getAerolinea() const { return aerolinea; }
    std::string getEstado() const { return estado; }

    // Destructor
    ~Avion() {}

private:
    std::string vuelo;
    std::string numeroRegistro;
    std::string modelo;
    std::string fabricante;
    int anoFabricacion;
    int capacidad;
    int pesoMaxDespegue;
    std::string aerolinea;
    std::string estado;
};