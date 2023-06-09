/** @file Prioridad.cc
    @brief Código de la clase Prioridad 
*/
#include "Prioridad.hh"
#include "Proceso.hh"
#ifndef NO_DIAGRAM
#include <queue>
#include <iostream>
#endif
using namespace std;

Prioridad::Prioridad() {
    enviados = 0;
    rechazados = 0;
}

void Prioridad::añadir_proceso(const Proceso& b) {
    a.push(b);
}

void Prioridad::imprimir_proridad() {
    queue<Proceso> b = a;
    while (b.size() > 0) {
        cout << b.front().consultar_id() << " " << b.front().consultar_ocupacion() << " "<< b.front().consultar_tiempo() << endl;
        b.pop();
    }
    cout << enviados << " " << rechazados << endl;
}

Proceso Prioridad::extraer_proceso() {
    Proceso aux = a.front();
    a.pop();
    return aux;
}

void Prioridad::aumenta_rechazo() {
    ++rechazados;
}
    
void Prioridad::aumenta_env() {
    ++enviados;
}

bool Prioridad::tiene_procesos() const{
    return a.size() != 0;
}

int Prioridad::size() const {
    return a.size();
}


bool Prioridad::esta_proceso(int id) const{
    queue<Proceso> c = a;
    while (c.size() != 0) {
        if (c.front().consultar_id() == id) return true;
        c.pop(); 
    }
    return false;
}
