/** @mainpage
	Programa modular el cual gestiona el funcionamiento de una arquitectura multiprocesador, donde
	cada procesador trabaja exclusivamente con su propia memoria y puede ejecutar más
	de un proceso simultáneamente.
*/
#ifndef NO_DIAGRAM
#include <iostream>
#include <string>
#endif
#include "Cluster.hh"
#include "Procesador.hh"
#include "AreaDeProcesos.hh" 
#include "Proceso.hh"
#include "Prioridad.hh"
using namespace std;

/** @file main.cc
   @brief El programa principal.
*/
int main() {
    Cluster a;
    a.configurar_cluster();
    AreaDeProcesos de_a;

    string comando;
    cin >> comando;
    while (comando != "fin") {
        if (comando == "cc" or comando == "configurar_cluster") {
            if (comando == "cc") cout << "#cc" << endl;
            else cout << "#configurar_cluster" << endl;
            
            a.configurar_cluster();
        } else if (comando == "mc" or comando == "modificar_cluster") {
            string p;
            cin >> p;
            if (comando == "mc") cout << "#mc ";
            else cout << "#modificar_cluster ";
            cout << p << endl;

            if (a.existeix(p) and not a.consultar_procesador(p).te_procesos()) {
                Cluster b;

                b.configurar_cluster();
                a.modificar_cluster(p, b);
            } else if (not a.existeix(p)) cout << "error: no existe procesador" << endl;
            else cout << "error: procesador con procesos" << endl;
        } else if (comando == "ap" or comando == "alta_prioridad") {
            string prio;
            cin >> prio;

            if (comando == "ap") cout << "#ap ";
            else cout << "#alta_prioridad ";
            cout << prio << endl; 
            
            de_a.alta_prioridad(prio);
        } else if (comando == "bp" or comando == "baja_prioridad") {
            string prio;
            cin >> prio;

            if (comando == "bp") cout << "#bp ";
            else cout << "#baja_prioridad ";
            cout << prio << endl;

            de_a.baja_prioridad(prio);
        } else if (comando == "ape" or comando == "alta_proceso_espera") {
            Proceso aux;
            string prio;
            cin >> prio;
            aux.leer();
            int id = aux.consultar_id();

            if (comando == "ape") cout << "#ape ";
            else cout << "#alta_proceso_espera ";
            cout << prio << " " << id << endl;

            de_a.alta_proceso_espera(aux, prio);
        } else if (comando == "app" or comando == "alta_proceso_procesador") {
            string p;
            cin >> p;
            Proceso aux;
            aux.leer();
            int id = aux.consultar_id();

            if (comando == "alta_proceso_procesador") cout << "#alta_proceso_procesador ";
            else if (comando == "app") cout  << "#app ";
            cout  << p << " " << id << endl;


            a.alta_proceso_procesador(p, aux);
        } else if (comando == "bpp" or comando == "baja_proceso_procesador") {
            string p;
            int id;
            cin >> p >> id;

            if (comando == "bpp") cout << "#bpp ";
            else cout << "#baja_proceso_procesador ";
            cout << p << " " << id << endl;


            a.baja_proceso_procesador(p, id);
         } else if (comando == "epc" or comando == "enviar_procesos_cluster") {
            if (comando == "epc") cout << "#epc ";
            else cout << "#enviar_procesos_cluster ";
            int n;
            cin >> n;
            cout << n << endl;

            de_a.enviar_procesos_cluster(n, a);
        } else if (comando == "at" or comando == "avanzar_tiempo") {
            int t;
            cin >> t;
            if (comando == "at") cout << "#at ";
            else cout << "#avanzar_tiempo ";
            cout << t << endl;

            a.avanzar_tiempo(t);
        } else if (comando == "ipri" or comando == "imprimir_prioridad") {
            string prio;
            cin >> prio;

            if (comando == "ipri") cout << "#ipri ";
            else cout << "#imprimir_prioridad ";
            cout << prio << endl;

            de_a.imprimir_prioridad(prio);
        } else if (comando == "iae" or comando == "imprimir_area_espera") {
            if (comando != "iae") cout << "#imprimir_area_espera" << endl;
            else cout << "#iae" << endl;

            de_a.imprimir_area_espera();
        } else if (comando == "ipro" or comando == "imprimir_procesador") {
            string p;
            cin >> p;

            if (comando == "imprimir_procesador") cout << "#imprimir_procesador ";
            else cout << "#ipro ";
            cout << p << endl;

            if (a.existeix(p)) {
                a.consultar_procesador(p).escribir_procesos();
            } else cout << "error: no existe procesador" << endl;
        } else if (comando == "ipc" or comando == "imprimir_procesadores_cluster") {
            if (comando == "ipc") cout << "#ipc" << endl;
            else cout << "#imprimir_procesadores_cluster" << endl;

            a.imprimir_procesadores_cluster();
        } else if (comando == "iec" or comando == "imprimir_estructura_cluster") {
            if (comando != "iec") cout << "#imprimir_estructura_cluster" << endl;
            else cout << "#iec" << endl;

            a.imprimir_estructura_cluster();
        } else if (comando == "cmp" or comando == "compactar_memoria_procesador") {
            string p;
            cin >> p;
            if (comando == "cmp") cout << "#cmp ";
            else cout << "#compactar_memoria_procesador ";
            cout << p << endl;

            a.compactar_memoria_procesador(p);
        } else if (comando == "cmc" or comando == "compactar_memoria_cluster") {
            if (comando == "cmc") cout << "#cmc";
            else cout << "#compactar_memoria_cluster";
            cout << endl;
            a.compactar_memoria_cluster();
        } else if (comando == "pc" or comando == "podar_cluster") {
            string p;
            cin >> p;
            if (comando == "podar_cluster") cout << "#podar_cluster ";
            else cout << "#pc ";
            cout << p << endl;
            a.podar_cluster(p);
        }
        cin >> comando;
    }
}

