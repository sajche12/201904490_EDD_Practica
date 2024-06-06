#include <string>

using namespace std;

class Avion {
private:
    string vuelo;
    string numero_de_registro;
    string modelo;
    string fabricante;
    string aerolinea;
    string estado;
    int ano_fabricacion;
    int capacidad;
    int peso_max_despegue;

public:
    // Crear constructor
    Avion(const string& vuelo, const string& numero_de_registro, const string& modelo, const string& fabricante, const string& aerolinea, const string& estado, int ano_fabricacion, int capacidad, int peso_max_despegue);

    // Setters y Getters
    void setVuelo(const string& vuelo);
    string getVuelo() const;

    void setNumeroDeRegistro(const string& numero_de_registro);
    string getNumeroDeRegistro() const;

    void setModelo(const string& modelo);
    string getModelo() const;

    void setFabricante(const string& fabricante);
    string getFabricante() const;

    void setAerolinea(const string& aerolinea);
    string getAerolinea() const;

    void setEstado(const string& estado);
    string getEstado() const;

    void setAnoFabricacion(int ano_fabricacion);
    int getAnoFabricacion() const;

    void setCapacidad(int capacidad);
    int getCapacidad() const;

    void setPesoMaxDespegue(int peso_max_despegue);
    int getPesoMaxDespegue() const;
};