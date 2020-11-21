#ifndef CIUDAD_H
#define CIUDAD_H
#include <iostream>

class Ciudad
{
private:
    std::string Nombre;
    unsigned int NumeroDeEstrellas;
    double Costo;

public:
    Ciudad();
    Ciudad(const std::string &name, const unsigned int &stars, const double &cost);
    void setNombre(const std::string &name);
    std::string getNombre();
    void setNumeroDeEstrellas(const unsigned int &stars);
    unsigned int getNumeroDeEstrellas();
    void setCosto(const double &cost);
    double getCosto();
    friend std::istream &operator >> (std::istream &lee, Ciudad &ciudad){
        std::cout << "\nIngrese el nombre de la ciudad: \n";
        lee >> ciudad.Nombre;
        std::cout << "Ingrese el numero de estrellas: \n";
        lee >> ciudad.NumeroDeEstrellas;
        std::cout << "Ingrese el costo de hospedaje: \n";
        lee >> ciudad.Costo;
        return lee;
    }
    friend std::ostream &operator << (std::ostream &escribe, Ciudad ciudad){
        escribe << "\nNombre: " << ciudad.Nombre;
        escribe << "\nEstrellas: " << ciudad.NumeroDeEstrellas;
        escribe << "\nCosto de hospedaje: " << ciudad.Costo;
        return escribe;
    }
};

#endif // CIUDAD_H
