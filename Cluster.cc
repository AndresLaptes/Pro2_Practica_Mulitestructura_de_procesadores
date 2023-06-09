/** @file Cluster.cc
    @brief Codigo de la clase clúster.
*/
#include "Proceso.hh"
#include "Cluster.hh"
#include "Procesador.hh"
#ifndef NO_DIAGRAM
#include "BinTree.hh"
#include <map>
#include <queue>
#include <iostream>
#endif
using namespace std;


Cluster::Cluster() {
    b.clear();
}

BinTree<string> Cluster::lectura() {
    string id;
    cin >> id;
    if (id == "*") {
        BinTree<string> vacio;
        return vacio;
    }
    int mem;
    cin >> mem;
    Procesador n(id, mem);
    b.insert(make_pair(id, n));
    BinTree<string> left = lectura();
    BinTree<string> right = lectura();
    BinTree<string> d(id, left, right);
    return d;
}


void Cluster::configurar_cluster() {
    b.clear();
    a = lectura();
}

void Cluster::alta_proceso_procesador(string p, const Proceso& cual) {
    map<string, Procesador>::iterator it = b.find(p);
    if (it != b.end() and not it->second.mismo_proceso(cual.consultar_id())) {
        if (not it->second.insertar_proceso(cual)) cout << "error: no cabe proceso" << endl;
    } else if (it == b.end()) cout << "error: no existe procesador" << endl;
    else cout << "error: ya existe proceso" << endl;
}

void Cluster::baja_proceso_procesador(string p, int id) {
    map<string, Procesador>::iterator it = b.find(p);
    if (it != b.end() and it->second.mismo_proceso(id)) it->second.eliminar_proceso(id);
    else if (it == b.end()) cout << "error: no existe procesador" << endl;
    else cout << "error: no existe proceso" << endl;
}

void Cluster::borrar_arb(const BinTree<string>& a, int& procesadores, int& procesos) {
    if (not a.empty()) {
        borrar_arb(a.left(), procesadores, procesos);
        borrar_arb(a.right(), procesadores, procesos);
        ++procesadores;
        procesos += this->consultar_procesador(a.value()).cuantos_procesos();
        b.erase(a.value());
    }
}

BinTree<string> Cluster::podacion(const BinTree<string>& a, string p, int& procesadores, int& procesos){
    if (not a.empty()) {
        if (a.value() == p) {
            ++procesadores;
            procesos += this->consultar_procesador(p).cuantos_procesos();
            borrar_arb(a.left(), procesadores, procesos);
            borrar_arb(a.right(), procesadores, procesos);
            
            b.erase(p);
            return BinTree<string> ();
        } else {
            BinTree<string> left = podacion(a.left(), p, procesadores, procesos);
            BinTree<string> right = podacion(a.right(), p, procesadores, procesos);
            return BinTree<string>(a.value(), left, right);
        }
    }
    return BinTree<string> ();
}

void Cluster::podar_cluster(string p) {
    if (a.value() == p) cout << "error: se intenta borrar la raiz" << endl;
    else if (this->existeix(p)) {
        int procesos_eliminados = 0;
        int procesadores_eliminados = 0;
        a = podacion(a, p, procesos_eliminados, procesadores_eliminados);
        cout << "Poda " << procesos_eliminados << " " << procesadores_eliminados << endl;
    } else cout << "error: no existe procesador" << endl;
}

void Cluster::avanzar_tiempo(int t) {
    map<string, Procesador>::iterator it = b.begin();
    while (it != b.end()) {
        it->second.mas_tiempo(t);
        ++it;
    }
}

void Cluster::imprimir_procesadores_cluster() {
    map<string, Procesador>::iterator it = b.begin();
    while (it != b.end()) {
        cout << it->first << endl;
        it->second.escribir_procesos();
        ++it;
    }
}

string Cluster::profundidad(const BinTree<string>& a, string id1, string id2) {
    queue<BinTree<string>> c;
    c.push(a);
    while (not c.empty()) {
        BinTree<string> aux(c.front());
        if (aux.value() == id1) return id1;
        if (aux.value() == id2) return id2;
        if (not aux.left().empty()) c.push(aux.left());
        if (not aux.right().empty()) c.push(aux.right());
        c.pop();
    }
    return "";
}


bool Cluster::envio_procesos_clust(const Proceso& proceso) {
    map<string, Procesador>::iterator it = b.begin();
    map<string, Procesador>::iterator mejorCandidato = b.end();
    int hueco = -1;
    while (it != b.end()) {
        int hueco_aux = it->second.hueco_ajustado(proceso);
        if (hueco_aux != -1 and not it->second.mismo_proceso(proceso.consultar_id())) {
            if (hueco == -1) {
                hueco = hueco_aux;
                mejorCandidato = it;
            } else if (hueco_aux < hueco) {
                hueco = hueco_aux;
                mejorCandidato = it;
            } else if (hueco_aux == hueco) {
                if (it->second.memoria_libre() == mejorCandidato->second.memoria_libre()) {
                    string idMejorCandidato = profundidad(a, mejorCandidato->first, it->first);
                    if (idMejorCandidato == it->first) {
                        mejorCandidato = it;
                    }
                } else if (it->second.memoria_libre() > mejorCandidato->second.memoria_libre()) {
                    mejorCandidato = it;
                }
            }
        }
        ++it;
    }

    if (mejorCandidato != b.end()) {
        mejorCandidato->second.insertar_proceso(proceso);
        return true;
    }
    return false;
}

void Cluster::imprimir_arbol(const BinTree<string>& a) {
    if (not a.empty()) {
        cout << "(" << a.value();
        if (not a.left().empty()) imprimir_arbol(a.left());
        else cout << " ";
        if (not a.right().empty()) imprimir_arbol(a.right());
        else cout << " ";
        cout << ")";
    }
}

void Cluster::compactar_memoria_procesador(string p) {
    map<string, Procesador>::iterator it = b.find(p);
    if (it != b.end()) it->second.compactar_mem();
    else cout << "error: no existe procesador" << endl;
}

void Cluster::modificar_cluster(string p, const Cluster& c) {
    bool se_mod = false;
    BinTree<string> aux = arbol_sitiene(a, p, c.estructura(), se_mod);

    if (se_mod) {
        a = aux;
        map<string, Procesador>::const_iterator it2 = b.find(p);
        b.erase(it2);
        map<string, Procesador> lista_c = c.procesadores();
        map<string, Procesador>::iterator it = lista_c.begin();
        while (it != lista_c.end()) {
            b.insert(make_pair(it->second.consultar_identificador(), it->second));
            ++it;
        }
    } else cout << "error: procesador con auxiliares" << endl;
}
   
void Cluster::compactar_memoria_cluster() {
    map<string, Procesador>::iterator it = b.begin();
    while (it != b.end()) {
        it->second.compactar_mem();
        ++it;
    }
}

void Cluster::imprimir_estructura_cluster() {
    imprimir_arbol(a);
    cout << endl;
}

bool Cluster::existeix(string p) const{
    map<string, Procesador>::const_iterator it = b.find(p);
    return it != b.end();
}

BinTree<string> Cluster::arbol_sitiene(const BinTree<string>& a, string p, const BinTree<string>& b, bool& aux) {
    if (a.empty()) return a;
    if (a.value() == p) {
        if (a.left().empty() and a.right().empty()) {
            aux = true;
            return b;
        }
    }
    BinTree<string> izquierda = arbol_sitiene(a.left(), p, b, aux);
    BinTree<string> derecha = arbol_sitiene(a.right(), p, b, aux);
    return BinTree<string>(a.value(), izquierda, derecha);
}

Procesador Cluster::consultar_procesador(string p) const{
    map<string, Procesador>::const_iterator it = b.find(p);
    return it->second;
}

BinTree<string> Cluster::estructura() const {
    return a;
}

map<string, Procesador> Cluster::procesadores() const{
    return b;
}
