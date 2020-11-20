#include "tablahash.h"

TablaHash::TablaHash()
{
    NumElemCiudades = 0;
}

int TablaHash::GETCLSID()
{
    return CLSID_TABLAHASH;
}

int TablaHash::fnHash(const VisitaDeCiudad &elemento)
{
    int aux = -1;
    switch(elemento.getNombre().size()){
        case 1:
            aux = 0;
            break;
        case 2:
            aux = 1;
            break;
        case 3:
            aux = 2;
            break;
        case 4:
            aux = 3;
            break;
        case 5:
            aux = 4;
            break;
        case 6:
            aux = 5;
            break;
        case 7:
            aux = 6;
            break;
        case 8:
            aux = 7;
            break;
        case 9:
            aux = 8;
            break;
        case 10:
            aux = 9;
            break;
        case 11:
            aux = 10;
            break;
        case 12:
            aux = 11;
            break;
        case 13:
            aux = 12;
            break;
        case 14:
            aux = 13;
            break;
        case 15:
            aux = 14;
            break;
        case 16:
            aux = 15;
            break;
        case 17:
            aux = 16;
            break;
    }
    return aux;
}

void TablaHash::InsertarElemento(VisitaDeCiudad &v)
{
    int posicion = fnHash(v);
    if(posicion == -1){
        std::cout << "No fue posible insertar el elemento.\n";
    }
    else{
        ArregloCiudades[posicion].insertarAlFinal(v);
        NumElemCiudades++;
    }
}

VisitaDeCiudad *TablaHash::Buscar(const VisitaDeCiudad &elemento)
{
    int posicion = fnHash(elemento);
    VisitaDeCiudad *direccion = nullptr;
    direccion = ArregloCiudades[posicion].Buscar(elemento.getNombre());
    return direccion;
}

void TablaHash::Eliminar(const VisitaDeCiudad &elemento)
{
    int posicion = fnHash(elemento);
    VisitaDeCiudad aux;
    aux = ArregloCiudades[posicion].Eliminar(elemento.getNombre());
    if(aux.getNombre().size() < 1){
        std::cout << "El elemento no existe.\n";
        return;
    }
    else{
        std::cout << "Se elimino " << aux << "\n";
        NumElemCiudades--;
    }
}

void TablaHash::Imprimir()
{
    for(int i = 0; i < MAX; i++){
        std::cout << "\n\nLista " << i+1 << ".\n";
        ArregloCiudades[i].Imprimir();
    }
}

void TablaHash::Salvar(std::ofstream &out)
{
    out << CLSID_TABLAHASH << "\n";
    out << NumElemCiudades << "\n";
    for(int i=0; i<MAX; i++){
        ArregloCiudades[i].Salvar(out);
    }
}

void TablaHash::Cargar(std::ifstream &in)
{
    int tamanio;
    in >> tamanio;
    for(int i=0; i<MAX; i++){
        int ClsidLista = 0;
        in >> ClsidLista;
        if(ClsidLista != CLSID_LISTA_DOBLEMENTE_LIGADA){
            std::cout << "No se trata de una lista ligada.\n";
        }
        else{
            int elementos = 0;
            in >> elementos;
            for(int i=0; i<elementos; i++){
                VisitaDeCiudad ciudad;
                int idCiudad = 0;
                in >> idCiudad;
                if(idCiudad != CLSID_VISITADECIUDAD){
                    std::cout << "No es una ciudad.\n";
                }
                ciudad.Cargar(in);
                InsertarElemento(ciudad);
            }
        }
    }
}

TablaHashCaminos::TablaHashCaminos()
{
    NumElemCaminos = 0;
}

int TablaHashCaminos::GETCLSID()
{
    return CLSID_TABLAHASHCAMINOS;
}

int TablaHashCaminos::fnHash(const CEdgeInfo &elemento)
{
    int aux = -1;
    switch(elemento.getDestino().size()){
        case 1:
            aux = 0;
            break;
        case 2:
            aux = 1;
            break;
        case 3:
            aux = 2;
            break;
        case 4:
            aux = 3;
            break;
        case 5:
            aux = 4;
            break;
        case 6:
            aux = 5;
            break;
        case 7:
            aux = 6;
            break;
        case 8:
            aux = 7;
            break;
        case 9:
            aux = 8;
            break;
        case 10:
            aux = 9;
            break;
        case 11:
            aux = 10;
            break;
        case 12:
            aux = 11;
            break;
        case 13:
            aux = 12;
            break;
        case 14:
            aux = 13;
            break;
        case 15:
            aux = 14;
            break;
        case 16:
            aux = 15;
            break;
        case 17:
            aux = 16;
            break;
    }
    return aux;
}

void TablaHashCaminos::InsertarElemento(CEdgeInfo &v)
{
    int posicion = fnHash(v);
    if(posicion == -1){
        std::cout << "No fue posible insertar el elemento.\n";
    }
    else{
        ArregloCaminos[posicion].insertarAlFinal(v);
        NumElemCaminos++;
    }
}

CEdgeInfo *TablaHashCaminos::Buscar(const CEdgeInfo &elemento)
{
    int posicion = fnHash(elemento);
    CEdgeInfo *direccion = nullptr;
    double aux = elemento.getCosto();
    direccion = ArregloCaminos[posicion].Buscar(elemento.getDestino(), aux);
    return direccion;
}

void TablaHashCaminos::Eliminar(const CEdgeInfo &elemento)
{
    int posicion = fnHash(elemento);
    CEdgeInfo aux;
    double aux2 = elemento.getCosto();
    aux = ArregloCaminos[posicion].Eliminar(elemento.getDestino(), aux2);
    if(aux.getDestino().size() < 1){
        std::cout << "El elemento no existe.\n";
        return;
    }
    else{
        std::cout << "Se elimino " << aux << "\n";
        NumElemCaminos--;
    }
}

void TablaHashCaminos::Imprimir()
{
    for(int i = 0; i < MAX; i++){
        std::cout << "\n\nLista " << i+1 << ".\n";
        ArregloCaminos[i].Imprimir();
    }
}

void TablaHashCaminos::Salvar(std::ofstream &out)
{
    out << CLSID_TABLAHASH << "\n";
    out << NumElemCaminos << "\n";
    for(int i=0; i<MAX; i++){
        ArregloCaminos[i].Salvar(out);
    }
}

void TablaHashCaminos::Cargar(std::fstream &in)
{/*
    int tamanio;
    in >> tamanio;
    for(int i=0; i<MAX; i++){
        int ClsidLista = 0;
        in >> ClsidLista;
        if(ClsidLista != CLSID_LISTA_DOBLEMENTE_LIGADA){
            std::cout << "No se trata de una lista ligada.\n";
        }
        else{
            int elementos = 0;
            in >> elementos;
            for(int i=0; i<elementos; i++){
                VisitaDeCiudad ciudad;
                int idCiudad = 0;
                in >> idCiudad;
                if(idCiudad != CLSID_VISITADECIUDAD){
                    std::cout << "No es una ciudad.\n";
                }
                ciudad.Cargar(in);
                InsertarElemento(ciudad);
            }
        }
    }*/
}


TablaHashComentarios::TablaHashComentarios()
{
    NumElemComentarios = 0;
}

int TablaHashComentarios::GETCLSID()
{
    return CLSID_TABLAHASHCAMINOS;
}

int TablaHashComentarios::fnHash(const std::string &elemento)
{
    int aux = -1;
    switch(elemento.size()){
        case 1:
            aux = 0;
            break;
        case 2:
            aux = 1;
            break;
        case 3:
            aux = 2;
            break;
        case 4:
            aux = 3;
            break;
        case 5:
            aux = 4;
            break;
        case 6:
            aux = 5;
            break;
        case 7:
            aux = 6;
            break;
        case 8:
            aux = 7;
            break;
        case 9:
            aux = 8;
            break;
        case 10:
            aux = 9;
            break;
        case 11:
            aux = 10;
            break;
        case 12:
            aux = 11;
            break;
        case 13:
            aux = 12;
            break;
        case 14:
            aux = 13;
            break;
        case 15:
            aux = 14;
            break;
        case 16:
            aux = 15;
            break;
        case 17:
            aux = 16;
            break;
    }
    return aux;
}

void TablaHashComentarios::InsertarElemento(std::string &v)
{
    int posicion = fnHash(v);
    if(posicion == -1){
        std::cout << "No fue posible insertar el elemento.\n";
    }
    else{
        ArregloComentarios[posicion].insertarAlFinal(v);
        NumElemComentarios++;
    }
}

std::string *TablaHashComentarios::Buscar(const std::string &elemento)
{
    int posicion = fnHash(elemento);
    std::string *direccion = nullptr;
    direccion = ArregloComentarios[posicion].Buscar(elemento);
    return direccion;
}

void TablaHashComentarios::Eliminar(const std::string &elemento)
{
    int posicion = fnHash(elemento);
    std::string aux;
    aux = ArregloComentarios[posicion].Eliminar(elemento);
    if(aux.size() < 1){
        std::cout << "El elemento no existe.\n";
        return;
    }
    else{
        std::cout << "Se elimino " << aux << "\n";
        NumElemComentarios--;
    }
}

void TablaHashComentarios::Imprimir()
{
    for(int i = 0; i < MAX; i++){
        std::cout << "\n\nLista " << i+1 << ".\n";
        ArregloComentarios[i].Imprimir();
    }
}

void TablaHashComentarios::Salvar(std::ofstream &out)
{
    out << CLSID_TABLAHASH << "\n";
    out << NumElemComentarios << "\n";
    for(int i=0; i<MAX; i++){
        ArregloComentarios[i].Salvar(out);
    }
}

void TablaHashComentarios::Cargar(std::fstream &in)
{/*
    int tamanio;
    in >> tamanio;
    for(int i=0; i<MAX; i++){
        int ClsidLista = 0;
        in >> ClsidLista;
        if(ClsidLista != CLSID_LISTA_DOBLEMENTE_LIGADA){
            std::cout << "No se trata de una lista ligada.\n";
        }
        else{
            int elementos = 0;
            in >> elementos;
            for(int i=0; i<elementos; i++){
                VisitaDeCiudad ciudad;
                int idCiudad = 0;
                in >> idCiudad;
                if(idCiudad != CLSID_VISITADECIUDAD){
                    std::cout << "No es una ciudad.\n";
                }
                ciudad.Cargar(in);
                InsertarElemento(ciudad);
            }
        }
    }*/
}
