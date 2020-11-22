#include "ciudad.h"

Ciudad::Ciudad()
{

}

Ciudad::Ciudad(const std::string &name, const unsigned int &stars, const double &cost)
{
    Nombre = name;
    NumeroDeEstrellas = stars;
    Costo = cost;
}

void Ciudad::setNombre(const std::string &name)
{
    Nombre = name;
}

std::string Ciudad::getNombre()
{
    return Nombre;
}

void Ciudad::setNumeroDeEstrellas(const unsigned int &stars)
{
    NumeroDeEstrellas = stars;
}

unsigned int Ciudad::getNumeroDeEstrellas()
{
    return NumeroDeEstrellas;
}

void Ciudad::setCosto(const double &cost)
{
    Costo = cost;
}

double Ciudad::getCosto()
{
    return Costo;
}

void Ciudad::SetNodo(int &n)
{
    Nodo = n;
}

int Ciudad::GetNodo()
{
    return Nodo;
}
