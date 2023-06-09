/** @file Procesador.cc
   @brief Código de la clase Procesador.
*/
#ifndef NO_DIAGRAM
#include <list>
#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <set>
#endif
#include "Procesador.hh"
#include "Proceso.hh"
using namespace std;

Procesador::Procesador() {
    p = "vacio";
    m_max = -1;
}

Procesador::Procesador(string a, int b) {
    p = a;
    m_max = b;
    huecos[m_max].insert(0);
}

void Procesador::leer_procesador() {
    cin >> p >> m_max;
    huecos[m_max].insert(0);
}

void Procesador::escribir_procesos() {
    map<int, Proceso>::const_iterator it = memoria.begin();
    while (it != memoria.end()) {
        cout << it->first << " ";
        cout << it->second.consultar_id() << " ";
        cout << it->second.consultar_ocupacion() << " ";
        cout << it->second.consultar_tiempo() << endl;
        ++it;
    }
}


void Procesador::compactar_mem() {
    if (not memoria.empty()) {
        huecos.clear();
        posiciones.clear();
        map<int, Proceso>::const_iterator it = memoria.begin();
        queue<Proceso> aux;
        while (it != memoria.end()) {
            aux.push(it->second);
            ++it;
        }

        int mem_t = 0;
        memoria.clear();
        while (not aux.empty()) {
            memoria.insert(make_pair(mem_t, aux.front()));
            posiciones.insert(make_pair(aux.front().consultar_id(), mem_t));
            mem_t += aux.front().consultar_ocupacion();
            aux.pop();
        }  
        if (m_max != mem_t) {
            huecos[m_max - mem_t].insert(mem_t);
        }

    }
}

bool Procesador::insertar_proceso(const Proceso& proceso) {
    map<int,set<int>>::iterator it = huecos.lower_bound(proceso.consultar_ocupacion());
    if (it != huecos.end()) {
        set<int>::const_iterator it2 = it->second.end();
        --it2;
        int pos = *it2;
        
        posiciones[proceso.consultar_id()] = pos;
        memoria[*it2] = proceso;
        it->second.erase(*it2);
        int tam_nuevo = it->first - proceso.consultar_ocupacion();
        int nueva_pos = pos + proceso.consultar_ocupacion();
        if (it->second.empty()) huecos.erase(it);
        if (tam_nuevo != 0) huecos[tam_nuevo].insert(nueva_pos);
        return true;
    }
    return false;
}

void Procesador::eliminar_proceso(int id) {
    int pos = posiciones[id];
    posiciones.erase(id);
    int size = memoria[pos].consultar_ocupacion();
    map<int,Proceso>::iterator it = memoria.erase(memoria.find(pos));
    int nuevo_hueco = size;
    int nueva_pos = pos;

    if (it != memoria.end()) {
        int dif = it->first - (pos+size);
        if (dif != 0) {
            nuevo_hueco += dif;
            huecos[dif].erase(pos+size);
            if (huecos[dif].empty()) huecos.erase(dif);
        }
    } else if (m_max != (pos+size)) {
        int hueco_final = m_max - (pos+ size);
        nuevo_hueco += hueco_final;
        huecos[hueco_final].erase(pos+size);
        if (huecos[hueco_final].empty()) huecos.erase(hueco_final);
    }

    if (it != memoria.begin()) {
        --it;
        int aux_pos = it->first;
        int aux_size = it->second.consultar_ocupacion();
        int dif = pos - (aux_pos + aux_size);
        if (dif != 0) {
            nueva_pos = it->first + it->second.consultar_ocupacion();
            nuevo_hueco += pos - nueva_pos;
            huecos[dif].erase(nueva_pos);
            if (huecos[dif].empty()) huecos.erase(dif);
        }
    } else if (pos != 0) {
        nuevo_hueco += pos;
        nueva_pos = 0;
        huecos[pos].erase(0);
        if (huecos[pos].empty()) huecos.erase(pos);
    }
    huecos[nuevo_hueco].insert(nueva_pos);
}

void Procesador::mas_tiempo(int t) {
    list<int> procesos_a_eliminar;
    map<int, Proceso>::iterator it = memoria.begin();
    while (it != memoria.end()) {
        if (it->second.tiempo_reducido(t)) {
            int id_proceso = it->second.consultar_id();
            procesos_a_eliminar.push_back(id_proceso);
        }
        ++it;
    }
    list<int>::const_iterator it2;
    for (it2 = procesos_a_eliminar.begin(); it2 != procesos_a_eliminar.end(); ++it2) {
        eliminar_proceso(*it2);
    }
}

string Procesador::consultar_identificador() const{
    return p;
}

bool Procesador::te_procesos() const{
    return not memoria.empty();
}

bool Procesador::mismo_proceso(int id) const{
    return posiciones.find(id) != posiciones.end();
}

int Procesador::hueco_ajustado(const Proceso& proceso) const {
    map<int, set<int>>::const_iterator it = huecos.lower_bound(proceso.consultar_ocupacion());
    if (it == huecos.end()) return -1;
    return it->first;
}

int Procesador::memoria_libre() const {
    map<int,set<int>>::const_iterator it = huecos.begin();
    int memoria_libre = 0;
    while (it != huecos.end()) {
        int posiciones_con_huecos = it->second.size();
        memoria_libre += posiciones_con_huecos*(it->first); 
        ++it;
    }
    return memoria_libre;
}

int Procesador::cuantos_procesos() const {
    return memoria.size();
}