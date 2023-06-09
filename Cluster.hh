/** @file Cluster.hh
    @brief Especificación de la clase clúster.
 */
#ifndef CLUSTER_HH
#define CLUSTER_HH
#ifndef NO_DIAGRAM
#include <map>
#include <iostream>
#include "BinTree.hh"
#endif
#include "Proceso.hh"
#include "Procesador.hh"
using namespace std;

/** @class Cluster
    @brief Representa una estructura jerárquica de procesadores,
    el cual cada procesador como máximo solo pueden tener dos procesadores auxiliares.
    Esta estructura se puede gestionar, dado que la clase tiene operaciónes de
    añadir procesos, eliminarlos, modificar la estructura de dicha jerárquia.
 */  

/// @brief 
class Cluster{
    private:

    /** @brief Representa el orden jerárquico de los procesadores.*/
    BinTree<string> a;
    /** @brief Represnta el contenido de dichos procesadores.*/
    map<string, Procesador> b;

    /** @brief Función que lee los datos de la estructura jerárquica.
        \pre cierto.
        \post Lee los datos de los procesadores y los pone en la estructura jerárquica.
        \par Coste
        Tiene un coste lineal respecto al número de procesadores n O(n).
    */
    BinTree<string> lectura();

    /** @brief Función que imprime la estructura jerárquica de los procesadores.
        \pre El arbol no esat vació.
        \post Imprime la estructura jerárquica de los procesadores.
        \par Coste
        Tiene un coste lineal respecto al número de procesadores n O(n).
    */
    static void imprimir_arbol(const BinTree<string>& a);

    /** @brief Función que sustituye si es posible en un procesador la extensión de otro arbol.
        \pre El arbol a no esta vació y el procesador p siempre esta en el clúster.
        \post Si el procesador con identificación p tiene no tiene auxiliares, se_mod se modifica en true
        y el arbol b pasa a extender en la posición donde estaba el procesador p. Si tiene procesadores
        auxiliares se_mod queda en false y no se modifica el arbol a que queda igual.
        \par Coste
        Tiene un coste lineal respecto al número de procesadores de a, n O(n).
    */
    static BinTree<string> arbol_sitiene(const BinTree<string>& a, string p, const BinTree<string>& c, bool& se_mod);

    /** @brief Función que hace un recorrido por niveles de la estructura jerárquica de procesadores.
        \pre El procesadores con identificadores id1 y id2 estan en el clúster.
        \post Retornara el procesador más cercano a la raiz, en caso de que los dos estan al mismo nivel, retornara el
        de más la izquierda.
        \par Coste
        Tiene un coste lineal respecto al número de procesadores de a, n O(n).
    */
    static string profundidad(const BinTree<string>& a, string id1, string id2);

    BinTree<string> podacion(const BinTree<string>& a, string p, int& num_procesadores, int& num_procesos);

    void borrar_arb(const BinTree<string>& a, int& procesadores, int& procesos);

    public:
    
    //Constructoras
    /** @brief Creadora por defecto de un <em>clúster</em>.
        \pre cierto.
        \post Crea un <em>clúster</em> vacio.
        \par Coste
        Constante O(c).
    */
    Cluster();

    //Modificadoras
    /** @brief Lee los datos de un <em>clúster</em>.
        \pre cierto.
        \post Lee un nuevo <em>clúster</em> tal que si havia uno es sustituido por este nuevo.
        \par Coste 
        Tiene un coste líneal respecto al número de procesadores que añadimos O(n).
    */
    void configurar_cluster();

    /** @brief Modifica el <em>clúster</em>, extendiendolo juntando otro clúster en la posición de un procesador.
        \pre El procesador existe, no tiene procesos en ejecución.
        \post En la posición del procesador se extiene el <em>clúster</em> a si este no tiene auxiliares.
        \par Coste 
        Tiene un coste líneal respecto al número de procesador del segundo cluster, y
        la profundidad h del primer cluster O(n + h).
    */
    void modificar_cluster(string p, const Cluster& a);

    void podar_cluster(string p);

    /** @brief Anade un <em>proceso</em> a un <em>procesador</em>.
        \pre cierto.
        \post El proceso pasa a executarse en el procesador, si es valido la asignación.
        La asignación es valida si el procesador existe en el clúster y no contiene un proceso con el mismo id,
        si no es valida da un mensaje de error.
        \par Coste
        Tiene un coste logaritmico respecto al numero de procesadores n y
        a la cantidad de huecos m del procesador O(log n + log m). 
    */
    void alta_proceso_procesador(string p, const Proceso& cual);

    /** @brief Elimina un <em>proceso</em> del <em>procesador</em>.
        \pre cierto.
        \post Se elimina de ese procesador el proceso si es valido. 
        Es valido si el procesador existe en el clúster y el proceso existe en el procesador, 
        en caso contrario devuelve un mensaje de error.
        \par Coste
        Tiene un coste logaritimico respecto al numero de procesadores n y 
        al número de huecos del procesador m O(log m + log n). 
    */
    void baja_proceso_procesador(string p, int id);

    /** @brief Avanza el tiempo de la simulación.
        \pre t > 0.
        \post La simulación avanza t unidades de tiempo
        \par Coste 
        El coste en el peor de los casos es (m*n) donde m son los elementos del clúster
        y n el nombre de procesos del procesador.
    */
    void avanzar_tiempo(int t);

    /** @brief Elimina los huecos de memoria libre entre <em>procesos</em> del <em>procesador</em>.
        \pre cierto.
        \post Mueven todos los <em>procesos</em> al principio, eliminando huecos de memoria del <em>procesador</em>.
        Si el proceso proceso existe, si no imprime un mensaje de error.
        \par Coste 
        Tiene un coste semilogaritmico respecto al número de procesadores n y al número
        de procesos m del procesos (log n + m).
    */
    void compactar_memoria_procesador(string p);

    /** @brief Elimina los huecos de memoria libre entre <em>procesos</em> del <em>clúster</em>.
        \pre cierto.
        \post Mueve todos los <em>procesos</em> al principio, eliminando huecos de memoria de todo el <em>clúster</em>.
        \par Coste 
        Tiene un coste líneal respecto al número de procesadores n y al número de procesos m del cada procesador
        O(n*m).
    */
    void compactar_memoria_cluster();

    /** @brief Escribe los <em>procesadores</em> del <em>clúster</em>.
        \pre cierto.
        \post Escribe todos los <em>procesadores</em> del <em>cúster</em> por orden creciente de identificador.
        \par Coste 
        Tiene un coste líneal respecto al número de procesadores del cluster O(n).
    */
    void imprimir_procesadores_cluster();

    /** @brief Función auxiliar que sirve para encontrar el mejor procesador 
        el cual poner el proceso.
        \pre cierto.
        \post Devuelve true y añade el proceso en el mejor procesador si se existe dicho procesador.
        en caso en que no cabe el proceso en ningun procesador o no existen procesadores devuelve false.
        \par Coste
        Esta función en el peor de los casos tiene un coste lineal respecto 
        al número de procesadores n, al número de huecos de cada uno m y de la altura en donde se encuentran
        los procesadores h O(n*(m+h)).
    */
    bool envio_procesos_clust(const Proceso& proceso);

    /** @brief Escribe el <em>clúster</em>.
        \pre cierto.
        \post Escribe la estructura del <em>clúster</em>.
        \par Coste 
        Tiene un coste líneal respecto al número de procesadores del cluster O(n).
    */
    void imprimir_estructura_cluster();

    //Consultoras
    /** @brief Consultora de la existencia del <em>procesador</em>.
        \pre cierto.
        \post Devuelve true si p existe en el <em>clúster</em>, false en caso contrario.
        \par Coste 
        El coste de esta función es logaritmica respecto al numero de 
        procesadores n O(log n).
    */
    bool existeix(string p) const;

    /** @brief Consultora de la existencia de auxiliares en un determinado <em>procesador</em>.
        \pre p esta en el cluster.
        \post Devuelve true si p tiene auxiliares, false en caso contrario.
        \par Coste 
        Tiene un coste logaritmico respecto al número de elementos del clúster O(log n);
    */

    /** @brief Consultora de un <em>procesador</em>.
        \pre Existe p en el <em>clúster</em>.
        \post Devuelve el <em>procesador</em> con el identificador p.
        \par Coste  
        Tiene un coste logaritmico respecto al número de procesadores O(log n);
    */
    Procesador consultar_procesador(string p) const;

    /** @brief Consultora de la estructura jerárquica del Clúster
        \pre El Clúster no esta vacio.
        \post Retorna la estructura jerárquica del Clúster en forma de Arbol Binario.
        \par Coste  
        Tiene un coste constante O(c)
    */
    BinTree<string> estructura() const;

    /** @brief Consultora del mapa de la clase.
        \pre cierto.
        \post Retorna el mapa de la clase.
        \par Coste  
        Tiene un coste constante O(c)
    */
    map<string, Procesador> procesadores() const;
};

#endif