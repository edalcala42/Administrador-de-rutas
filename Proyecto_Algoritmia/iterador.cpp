#include "iterador.h"

Iterador::Iterador()
{

}

void Iterador::setNodo(Nodo *pNodo)
{
    pActual = pNodo;
}

void Iterador::insertarAdelante(const VisitaDeCiudad &f)
{
    pActual->insertar_adelante(f);
}

VisitaDeCiudad Iterador::eliminarSiguiente()
{
    return pActual->eliminar_adelante();
}

void Iterador::operator =(const Iterador &otro)
{
    this->pActual = otro.pActual;
}

bool Iterador::operator ==(const Iterador &otro)
{
    return this->pActual == otro.pActual;
}

bool Iterador::operator !=(const Iterador &otro)
{
    return this->pActual != otro.pActual;
}

void Iterador::operator ++()
{
    pActual = pActual->pSig;
}

void Iterador::operator --()
{
    pActual = pActual->pAnt;
}

VisitaDeCiudad &Iterador::operator *()
{
    return pActual->Dato;
}

void Iterador::operator ++(int)
{
    pActual = pActual->pSig;
}

void Iterador::operator --(int)
{
    pActual = pActual->pAnt;
}
