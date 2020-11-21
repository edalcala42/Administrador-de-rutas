#ifndef NODO_H
#define NODO_H
#include "ciudad.h"

class Nodo{
private:
    Nodo *pSig;
    Nodo *pAnt;
    Ciudad Dato;
    void insertar_adelante(const Ciudad &d);
    Ciudad eliminar_adelante();

public:
    Nodo();
    friend class Lista_Doblemente_Ligada;
    friend class Iterador;
};

#endif // NODO_H
