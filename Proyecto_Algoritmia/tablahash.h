#ifndef TABLAHASH_H
#define TABLAHASH_H
#include "lista_doblemente_ligada.h"
#include "cserializable.h"
#include "listacaminos.h"
#include "listacomentarios.h"
#include "clistainvertida.h"
#include "visitadeciudad.h"
#include "cedgeinfo.h"
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
    int fnHash(const VisitaDeCiudad &elemento);
    void InsertarElemento(VisitaDeCiudad &v);
    VisitaDeCiudad *Buscar(const VisitaDeCiudad &elemento);
    void Eliminar(const VisitaDeCiudad &elemento);
    void Imprimir();
    void Salvar(std::ofstream &out);
    void Cargar(std::ifstream &in);
};

#define CLSID_TABLAHASHCAMINOS 2001
class TablaHashCaminos
{
private:
    ListaCaminos ArregloCaminos[MAX];
    int NumElemCaminos;

    public:
        TablaHashCaminos();
        int GETCLSID();
        int fnHash(const CEdgeInfo &elemento);
        void InsertarElemento(CEdgeInfo &v);
        CEdgeInfo *Buscar(const CEdgeInfo &elemento);
        void Eliminar(const CEdgeInfo &elemento);
        void Imprimir();
        void Salvar(std::ofstream &out);
        void Cargar(std::fstream &in);
};

class TablaHashComentarios
{
private:
    ListaComentarios ArregloComentarios[MAX];
    int NumElemComentarios;

    public:
        TablaHashComentarios();
        int GETCLSID();
        int fnHash(const std::string &elemento);
        void InsertarElemento(std::string &v);
        std::string *Buscar(const std::string &elemento);
        void Eliminar(const std::string &elemento);
        void Imprimir();
        void Salvar(std::ofstream &out);
        void Cargar(std::fstream &in);
};

#endif // TABLAHASH_H
