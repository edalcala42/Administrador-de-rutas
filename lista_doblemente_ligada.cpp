#include "lista_doblemente_ligada.h"

// Métodos de la lista

Lista_Doblemente_Ligada::Lista_Doblemente_Ligada()
{
    inicio.pSig = &final;
    final.pAnt = &inicio;
}

int Lista_Doblemente_Ligada::GETCLSID()
{
    return CLSID_LISTA_DOBLEMENTE_LIGADA;
}

void Lista_Doblemente_Ligada::insertarAlInicio(Ciudad &d)
{
    std::string nombre = d.getNombre();
    if(Buscar(nombre) != nullptr){
        std::cout << "La ciudad ya existe.\n";
        return;
    }
    else{
        inicio.insertar_adelante(d);
    }
}

void Lista_Doblemente_Ligada::insertarAlFinal(Ciudad &d)
{
    std::string nombre = d.getNombre();
    if(Buscar(nombre) != nullptr){
        std::cout << "La ciudad ya existe.\n";
        return;
    }
    else{
        final.pAnt->insertar_adelante(d);
    }
}

Ciudad Lista_Doblemente_Ligada::eliminarAlInicio()
{
    return inicio.eliminar_adelante();
}

Ciudad Lista_Doblemente_Ligada::eliminarAlFinal()
{
    return final.pAnt->pAnt->eliminar_adelante();
}

Ciudad *Lista_Doblemente_Ligada::Buscar(const std::string &ciudad)
{
    Iterador it;
    Ciudad *aux = nullptr;
    for(it = this->Begin(); it != this->End(); it++){
        if(it.pActual->Dato.getNombre() == ciudad){
            aux = &it.pActual->Dato;
        }
    }
    return aux;
}

Ciudad Lista_Doblemente_Ligada::Eliminar(const std::string &ciudad)
{
    Iterador it;
    Ciudad aux;
    Nodo *nodo = nullptr;
    for(it = this->Begin(); it != this->End(); it++){
        if(it.pActual->Dato.getNombre() == ciudad){
            nodo = it.pActual;
        }
    }
    if(nodo == nullptr){
        return aux;
    }
    else{
        nodo = nodo->pAnt;
        aux = nodo->eliminar_adelante();
        return aux;
    }
}

int Lista_Doblemente_Ligada::size()
{
    int total_nodes(0);
    Nodo *p = inicio.pSig;
    while(p != &final){
        total_nodes++;
        p = p->pSig;
    }
    return total_nodes;
}

bool Lista_Doblemente_Ligada::isEmpty()
{
    return inicio.pSig == &final;
}

bool Lista_Doblemente_Ligada::isFull()
{
    Nodo *newNode;
    if((newNode = new Nodo())==nullptr){
        return true;
    }
    else{
        delete newNode;
        return false;
    }
}

void Lista_Doblemente_Ligada::Imprimir()
{
    Iterador it;
    unsigned int i(1);
    for(it = this->Begin();it != this->End(); it++){
        std::cout << i << ") " << *it << ". " << std::endl;
        i++;
    }
}

Iterador &Lista_Doblemente_Ligada::Begin()
{
    m_itBegin.setNodo(inicio.pSig);
    return m_itBegin;
}

Iterador &Lista_Doblemente_Ligada::End()
{
    m_itEnd.setNodo(&final);
    return m_itEnd;
}

Iterador &Lista_Doblemente_Ligada::rBegin()
{
    m_itBegin.setNodo(final.pAnt);
    return m_itBegin;
}

Iterador &Lista_Doblemente_Ligada::rEnd()
{
    m_itEnd.setNodo(&inicio);
    return m_itEnd;
}

Lista_Doblemente_Ligada::~Lista_Doblemente_Ligada()
{
    while(inicio.pSig != &final){
        Nodo *aux = inicio.pSig;
        aux->pAnt = nullptr;
        inicio.pSig = aux->pSig;
        aux->pSig = nullptr;
        delete aux;
    }
    final.pAnt = &inicio;
    inicio.pSig = &final;
}

void Lista_Doblemente_Ligada::deleteAll()
{
    while(inicio.pSig != &final){
        Nodo *aux = inicio.pSig;
        aux->pAnt = nullptr;
        inicio.pSig = aux->pSig;
        aux->pSig = nullptr;
        delete aux;
    }
    final.pAnt = &inicio;
    inicio.pSig = &final;
}
