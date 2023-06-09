/** @file Proceso.cc
    @brief Código de la clase Proceso
*/
#ifndef NO_DIAGRAM
#include <iostream>
#endif
#include "Proceso.hh"
using namespace std;

Proceso::Proceso() {
    id = -1;
    ocupa_en_mem = -1;
    t_previsto = -1;
}

void Proceso::leer() {
    cin >> id >> ocupa_en_mem >> t_previsto;
}

bool Proceso::tiempo_reducido(int t) {
    t_previsto = t_previsto - t;
    if (t_previsto <= 0) {
        t_previsto = 0;
        return true;
    }
    return false;
}

int Proceso::consultar_id() const{
    return id;
}

int Proceso::consultar_ocupacion() const{
    return ocupa_en_mem;
}

int Proceso::consultar_tiempo() const{
    return t_previsto;
}