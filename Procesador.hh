/** @file Procesador.hh
   @brief Especificación de la clase Procesador.
*/
#ifndef PROCESADOR_HH
#define PROCESADOR_HH
#include "Proceso.hh"
#ifndef NO_DIAGRAM
#include <map>
#include <set>
#include <iostream>
#include <string>
#endif
using namespace std;

/** @class Procesador
   @brief Representa un procesador.
   
   Este tiene un identificador que le repesenta, cada procesador tiene una cantidad
   de memoria determinada en la cual puede almacenar procesos. 
 */

class Procesador{
   private:

   /** @brief Representa el identificador del procesador. */
   string p;

   /** @brief Representa la capacidad de memoria del procesador. */
   int m_max;

   /** @brief Representa la memoria del procesador,
       el primer valor es la posicion la cual ocupa el proceso,
       el segundo es dicho proceso.
   */
   map<int, Proceso> memoria;

   /** @brief Representa una estructura para hacer unas busquedas mas rápidas.
       El primer valor es el identificador del proceso, el segundo es la posición
       de la memoria la cual dicho proceso ocupa.
   */
   map<int, int> posiciones;

   /** @brief Representa los hueco vacios de la memoria. 
       El primer valor es el tamaño del hueco y el segundo
       son todas las posiciones las cuales tienen esa dimension 
       de hueco.
   */
   map<int, set<int>> huecos;

    public:

   //Constructoras
   /** @brief Constructora por defecto de la clase.
       \pre cierto.
       \post Crea un <em>procesador</em> vacío
       \par Coste 
       El coste de esta función es de tipo constante O(c).
    */
   Procesador();

   /** @brief Constructora especifica.
       \pre El valor de b > 0.
       \post Crea un procesador con identificador a y memoria máxima b.
       \par Coste 
       El coste de esta función es de tipo constante O(c).
   */
   Procesador(string a, int b);

   //Modificadoras
   /** @brief Lee los datos del <em>procesador</em> y se los asigna.
       \pre cierto.
       \post Lee los datos necesarios de un <em>procesador</em>.
       \par Coste 
       El coste de esta función es constante O(c).
   */
   void leer_procesador();

   /** @brief Imprime los datos del <em>procesador</em>.
       \pre cierto.
       \post Escribe los <em>procesos</em> del <em>procesador</em> y sus datos en caso de que hayan
       \par Coste 
       Tiene un coste lineal respecto al numero de procesos del procesador m O(m).
   */
   void escribir_procesos();

   /** @brief Función que retorna true y añade un proceso
       en la posicion de memoria mas ajustada si un proceso cabe
       en el procesador.
       \pre cierto.
       \post retorna true y añade un proceso
       en la posicion de memoria mas ajustada si un proceso cabe
       en el procesador.  Si el proceso no cabe en el procesador 
       retorna false.
       \par Coste 
       Tiene un coste logaritmico respecto el tamaño m de los huecos O(log m).
   */
   bool insertar_proceso(const Proceso& cual); 

   /** @brief Elimina un proceso de un procesador.
       \pre El proceso existe en el procesador.
       \post Se elimina el proceso, de tal manera que lo ocupava, pasa a ser un hueco.
       \par Coste 
       Tiene un coste logaritmico respecto al tamaño m de los huecos O(log m).
   */
   void eliminar_proceso(int id);

   /** @brief Avanza el tiempo de todos los procesos del procesador.
       \pre cierto.
       \post Se reduce en t unidades de tiempo la ejecución de todos los
       procesos del procesador, en caso de que su tiempo lluegue a 0 se elimina del procesador.
       \par Coste 
       Tiene un coste lineal respecto al numero de procesos del procesador m O(m)
   */
   void mas_tiempo(int t);

   /** @brief Junta todos los <em>procesos</em>, eliminando espacios entre ellos.
       \pre cierto.
       \post Mueve todos los <em>procesos</em> al principio sin dejar huecos y los huecos se juntan al final
       \par Coste 
       Tiene un coste líneal respecto al número de procesos del procesador m O(m).
    */
   void compactar_mem();

    //Consultoras
   /** @brief Consultora del identificador del procesador.
       \pre cierto.
       \post Devuelve el identificador del procesador.
       \par Coste 
       El coste de esta función es constante O(c).
   */
   string consultar_identificador() const;

   /** @brief Consultora de la existencia de <em>procesos</em> en el <em>procesador</em>.
       \pre cierto.
       \post Devuelve true si el <em>procesador</em> tiene <em>procesos</em>, false en caso contrario
       \par Coste 
       Tiene un coste constante O(c).
   */
    bool te_procesos() const;

   /** @brief Consultora de si hay un mismo <em>proceso</em> en el <em>procesador</em>.
       \pre cierto.
       \post Devuelve cierto si el <em>procesador</em> contien ya un <em>proceso</em> con esa id, false en caso contrario
       \par Coste 
       Tiene un coste logaritmico respecto al numero de procesos del procesador m O(log m).
   */
   bool mismo_proceso(int id) const;

   /** @brief Consultora que devuelve en caso de que cabe el proceso
       en el procesador, devuelve el tamaño del hueco.
       \pre cierto.
       \post Devuelve si cabe el proceso en el procesado el hueco mas ajustado, devuelve -1 si no cabe.
       \par Coste 
       Tiene un coste logaritmico respecto al numero de huecos del procesador m O(log m).
    */
    int hueco_ajustado(const Proceso& proceso) const;

   /** @brief Consultora que devuelve la cantidad de memoria libre del procesador
       \pre cierto.
       \post Devuelve la cantidad de memoria libre del procesador.
       \par Coste 
       Tiene un coste lineal respecto al numero de procesos de la memoria O(m).
   */
   int memoria_libre() const;

   int cuantos_procesos() const;
};
#endif