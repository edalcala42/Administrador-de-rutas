#ifndef LISTA_DOBLEMENTE_LIGADA_H
#define LISTA_DOBLEMENTE_LIGADA_H
#include <iostream>
#include "nodo.h"
#include "iterador.h"
#include "ciudad.h"
#include <fstream>

#define CLSID_LISTA_DOBLEMENTE_LIGADA 1000

class Lista_Doblemente_Ligada
{
private:
    Nodo inicio;
    Nodo final;
    Iterador m_itBegin;
    Iterador m_itEnd;

public:
    typedef Nodo node;
    Lista_Doblemente_Ligada();
    int GETCLSID();
    void insertarAlInicio(Ciudad &d);
    void insertarAlFinal(Ciudad &d);
    Ciudad eliminarAlInicio();
    Ciudad eliminarAlFinal();
    Ciudad *Buscar(const std::string &ciudad);
    Ciudad Eliminar(const std::string &ciudad);

    int size();
    bool isEmpty();
    bool isFull();
    void Imprimir();
    Iterador &Begin();
    Iterador &End();
    Iterador &rBegin();
    Iterador &rEnd();
    ~Lista_Doblemente_Ligada();
    friend class TablaHash;

};




#endif // LISTA_DOBLEMENTE_LIGADA_H
