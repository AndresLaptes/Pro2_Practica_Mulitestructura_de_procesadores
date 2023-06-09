/** @file AreaDeProcesos.cc
    @brief Código de la clase AreaDeProcesos 
*/
#include "AreaDeProcesos.hh"
#include "Prioridad.hh"
#include "Proceso.hh"
#ifndef NO_DIAGRAM
#include <string>
#include <map>
#include <queue>
#include <iostream>
#endif
using namespace std;

AreaDeProcesos::AreaDeProcesos() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        Prioridad aux;
        string prio;
        cin >> prio;
        area.insert(make_pair(prio, aux));
    }
}


void AreaDeProcesos::alta_prioridad(string prio) {
    Prioridad aux;
    map<string, Prioridad>::iterator it = area.find(prio);
    if (it == area.end()) area.insert(make_pair(prio, aux));
    else cout << "error: ya existe prioridad" << endl;
}

void AreaDeProcesos::baja_prioridad(string prio) {
    map<string, Prioridad>::const_iterator it = area.find(prio);
    if (it != area.end() and not it->second.tiene_procesos()) area.erase(it);
    else if (it == area.end()) cout << "error: no existe prioridad" << endl;
    else cout << "error: prioridad con procesos" << endl;
}

void AreaDeProcesos::enviar_procesos_cluster(int n, Cluster& a) { 
    map<string, Prioridad>::iterator it = area.begin();
    while (it != area.end() and n > 0) {
        if (it->second.tiene_procesos()){
            int size = it->second.size();
            while (n > 0 and size > 0) {
                Proceso aux = it->second.extraer_proceso();
                --size;
                if (not a.envio_procesos_clust(aux)) {
                    it->second.aumenta_rechazo();
                    it->second.añadir_proceso(aux);
                } else {
                    it->second.aumenta_env();
                    --n;
                }
            }
        }
        ++it;
    }
}

void AreaDeProcesos::alta_proceso_espera(const Proceso& b, string prio) {
    map<string, Prioridad>::iterator it = area.find(prio);
    if (it != area.end() and not it->second.esta_proceso(b.consultar_id())) it->second.añadir_proceso(b);
    else if (it == area.end()) cout << "error: no existe prioridad" << endl;
    else cout << "error: ya existe proceso" << endl;
}

void AreaDeProcesos::imprimir_prioridad(string prio) {
    map<string, Prioridad>::iterator it = area.find(prio);
    if (it != area.end()) it->second.imprimir_proridad();
    else cout << "error: no existe prioridad" << endl;
}

void AreaDeProcesos::imprimir_area_espera() {
    map<string, Prioridad>::iterator it = area.begin();
    while (it != area.end()) {
        cout << it->first << endl;
        it->second.imprimir_proridad();
        ++it;
    }
}

bool AreaDeProcesos::existe(string prio) const{
    map<string, Prioridad>::const_iterator it = area.find(prio);
    return it != area.end();
}

bool AreaDeProcesos::tiene_procesos(string prio) const{
    map<string, Prioridad>::const_iterator it = area.find(prio);
    return it->second.tiene_procesos();
}

bool AreaDeProcesos::tiene_ese_proceso(string prio, int id) const {
    map<string, Prioridad>::const_iterator it = area.find(prio);
    return it->second.esta_proceso(id);
}