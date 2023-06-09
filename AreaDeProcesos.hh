/** @file AreaDeProcesos.hh
    @brief Especificación de la clase AreaDeProcesos 
*/
#ifndef AREADEPROCESOS_HH
#define AREADEPROCESOS_HH
#ifndef NO_DIAGRAM
#include <map>
#include <string>
#include <queue>
#include <iostream>
#endif
#include "Prioridad.hh"
#include "Cluster.hh"
#include "Proceso.hh"
using namespace std;

/** @class AreaDeProcesos
    @brief Representa una zona para almacenar <em>procesos</em> que están a la espera para ejecutarse en el <em>clúster</em>.
 
   Esta zona de espera clasifica los procesos con una prioridad, los cuales si tienen mayor prioridad se ejecutaran antes. 
   Además están ordenados por orden de antiguedad si pertenecen a la misma prioridad. Eso significa que los procesos más 
   antiguos seran los primeros en enviar a ejecutarse.
 */
class AreaDeProcesos{
    private:

    /** @brief Representa la area de Espera, donde el primer valor es la prioridad, y
        el segundo es su contenido.
    */
    map<string, Prioridad> area;
    public:

    //Constructoras
    /** @brief Constructora de la clase.
        Se ejecuta automáticamente al declarar una área.
        \pre cierto        
        \post Crea un <em>área de procesos</em> con n prioridades.
        \par Coste 
        Tiene un coste constante O(c).
    */
    AreaDeProcesos();

    //Modificadoras
    /** @brief Añade una prioridad nueva vacia al área.
        \pre cierto.
        \post Se añade esa prioridad al área. Si la prioridad existia en el area
        escribe un mensaje de error.
        \par Coste 
        Tiene un coste logaritmico respecto al numero de prioridades n O(log n).
    */
    void alta_prioridad(string prio);

    /** @brief Elimina la prioridad del área.
        \pre cierto
        \post Elimina esta prioridad de el <em>área de espera</em>. Si la prioridad
        no existe o tiene procesos esta escribe un respectivo mensaje de error.
        \par Coste 
        Tiene un coste logaritmico respecto al numero de prioridades n O(log n).
    */
    void baja_prioridad(string prio);

    /** @brief Añade un <em>proceso</em> al área con una determinada prioridad.
        \pre cierto.
        \post El proceso pasa al área con esa prioridad. En el caso de que no existe esa prioridad
        o de que la prioidad ya tiene un proceso con ese id escribe un mensaje de error.
        \par Coste 
        Tiene un coste logaritmico respecto al numero de prioridades n O(log n).
    */
    void alta_proceso_espera(const Proceso& a, string prio);

    /** @brief Escribe los procesos de la prioridad.
        \pre cierto.
        \post Se imprime por orden decreciente en antiguedad los procesos de esa prioridad. En caso
        de que no existe esa prioridad escribe un mesnaje de error.
        \par Coste 
        Tiene un coste logaritmico respecto al numero de prioridades n O(log n).
        */
    void imprimir_prioridad(string prio);

    /** @brief Coloca de el <em>área de procesos</em> n <em>procesos</em> en el <em>clúster</em>.
        \pre n > 0;
        \post Se intenta colocar n <em>procesos</em> por orden de prioridad y antiguedad en los <em>procesadores</em> del <em>clúster</em>.
        Estos procesos se pondran en el procesador en el cual su ocupación sea la más ajustada, en caso de que haya
        más de un procesador que estan igual de ajustados se pondra en el de más memoria libre, si el empate
        prevalece se pondra en el procesador más cercano del procesador principal. En caso de empate se podndra el de más a la izquierda.
        \par Coste 
        Esta función en el peor de los casos tiene un coste lineal respecto 
        al número de procesadores n, al número de huecos de cada uno m ,  de la altura en donde se encuentran
        los procesadores h y la cantidad de procesos que se intentan enviar g O(n*(m+h) + g).
    */
    void enviar_procesos_cluster(int n, Cluster& a);

    /** @brief Escribe los procesos del área.
        \pre cierto.
        \post Escribe toda el área por orden creciente de prioridad y los procesos por orden decreciente en antiguedad.
        \par Coste 
        Tiene un coste lineal respecto al numero de prioridades n O(n).
    */
    void imprimir_area_espera();

    //Consultoras
    /** @brief Consultora de la existencia de la prioridad.
        \pre cierto.
        \post Devuelve true si existe la prioridad en el área, false en caso contrario.
        \par Coste 
        Tiene un coste logaritmico respecto al numero de prioridades n O(log n).
    */
    bool existe(string prio) const;

    /** @brief Consultora de la existencia de <em>procesos</em> en la prioridad.
        \pre cierto.
        \post Devuelve true si la prioridad tiene <em>procesos</em>, false en caso contrario.
        \par Coste 
        Tiene un coste logaritmico respecto al numero de prioridades n O(log n).
    */
    bool tiene_procesos(string prio) const;

    /** @brief Consultora de la existencia de un determinado proceso dado en una prioridad.
        \pre cierto.
        \post Devuelve true si un determinado poroceso dado esta en el área, false en caso contrario.
        \par Coste 
        Tiene un coste semilogaritmico respecto al numero de prioridades n y
        al numero de procesos de la prioridad m O(m + log n).
    */
    bool tiene_ese_proceso(string prio, int id) const;
};
#endif