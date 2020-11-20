#include "tablahash.h"

TablaHash::TablaHash()
{
    NumElemCiudades = 0;
}

int TablaHash::GETCLSID()
{
    return CLSID_TABLAHASH;
}

int TablaHash::GetSize()
{
    return NumElemCiudades;
}

int TablaHash::fnHash(const Ciudad &elemento)
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

void TablaHash::InsertarElemento(Ciudad &v)
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

Ciudad *TablaHash::Buscar(const Ciudad &elemento)
{
    int posicion = fnHash(elemento);
    Ciudad *direccion = nullptr;
    direccion = ArregloCiudades[posicion].Buscar(elemento.getNombre());
    return direccion;
}

void TablaHash::Eliminar(const Ciudad &elemento)
{
    int posicion = fnHash(elemento);
    Ciudad aux;
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

Lista_Doblemente_Ligada *TablaHash::GetArregloCiudades(){
    return ArregloCiudades;
}

