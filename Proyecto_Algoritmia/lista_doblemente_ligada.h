#ifndef LISTA_DOBLEMENTE_LIGADA_H
#define LISTA_DOBLEMENTE_LIGADA_H
#include <iostream>
#include "nodo.h"
#include "iterador.h"
#include "cserializable.h"
#include "visitadeciudad.h"
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
    Lista_Doblemente_Ligada();
    int GETCLSID();
    void insertarAlInicio(VisitaDeCiudad &d);
    void insertarAlFinal(VisitaDeCiudad &d);
    VisitaDeCiudad eliminarAlInicio();
    VisitaDeCiudad eliminarAlFinal();
    VisitaDeCiudad *Buscar(const std::string &ciudad);
    VisitaDeCiudad Eliminar(const std::string &ciudad);

    int size();
    bool isEmpty();
    bool isFull();
    void Imprimir();
    void Salvar(std::ofstream &out);
    void Cargar(std::ifstream &in);
    Iterador &Begin();
    Iterador &End();
    Iterador &rBegin();
    Iterador &rEnd();
    ~Lista_Doblemente_Ligada();
    friend class TablaHash;

};




#endif // LISTA_DOBLEMENTE_LIGADA_H
