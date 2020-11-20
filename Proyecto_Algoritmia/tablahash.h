#ifndef TABLAHASH_H
#define TABLAHASH_H
#include "lista_doblemente_ligada.h"
#include "ciudad.h"
#include <fstream>

#define MAX 17
#define CLSID_TABLAHASH 2000

class TablaHash
{
private:
    Lista_Doblemente_Ligada ArregloCiudades[MAX];
    int NumElemCiudades;

public:
    TablaHash();
    int GETCLSID();
    int GetSize();
    int fnHash(const Ciudad &elemento);
    void InsertarElemento(Ciudad &v);
    Ciudad *Buscar(const Ciudad &elemento);
    void Eliminar(const Ciudad &elemento);
    void Imprimir();
    void Salvar(std::ofstream &out);
    void Cargar(std::ifstream &in);
    Lista_Doblemente_Ligada *GetArregloCiudades();
    int Max();
};

#endif
