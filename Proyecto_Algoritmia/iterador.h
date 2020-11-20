#ifndef ITERADOR_H
#define ITERADOR_H
#include "nodo.h"

class Iterador
{
private:
    Nodo *pActual;
    void setNodo(Nodo *pNodo);

public:  
    Iterador();
    void insertarAdelante(const Ciudad &f);
    Ciudad eliminarSiguiente();
    void operator = (const Iterador &otro);
    bool operator == (const Iterador &otro);
    bool operator != (const Iterador &otro);
    void operator ++ ();
    void operator -- ();
    Ciudad & operator *();
    void operator ++(int);
    void operator --(int);
    friend class Lista_Doblemente_Ligada;
};

#endif // ITERADOR_H
