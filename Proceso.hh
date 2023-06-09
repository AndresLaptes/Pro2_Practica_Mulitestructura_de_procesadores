/** @file Proceso.hh
    @brief Documentación de la clase Proceso
*/
#ifndef PROCESO_HH
#define PROCESO_HH
#ifndef NO_DIAGRAM
#include <iostream>
#endif
using namespace std;


/** @class Proceso
    @brief Representa un proceso.
    
    Este tiene su propia identificación que lo representa, el cual el proceso tiene sus determinadas características.
    Como cuanto dura y lo que ocupa en memoria.
*/
class Proceso{
    private:

    /** @brief Representa el identiicador del Proceso.*/
    int id;

    /** @brief Representa la cantidad de memoria que ocupa el proceso en memoria.*/
    int ocupa_en_mem;

    /** @brief Representa la cantidad de tiempo antes de que se acabe el proceso.*/
    int t_previsto;
    public:

    //Constructoras
    /** @brief Constructora de la clase.
        \pre cierto.
        \post Crea un <em>proceso</em> vacío.
        \par Coste 
        El coste de esta función es constante (c).
    */
    Proceso();

    //Modificadoras
    /** @brief Lee los datos del procesador.
        \pre cierto
        \post Lee los datos del <em>proceso</em>.
        \par Coste 
        Tiene un coste constante O(c).
    */
    void leer();

    /** @brief Avanza el tiempo de la simulación.
        \pre cierto.
        \post Se avanza el tiempo dela simulación, en caso de que el se acabe el tiempo
        devuelve true en caso contrario devuelve false.
        \par Coste 
        Tiene un coste constante O(c).
    */
    bool tiempo_reducido(int t);

    //Consultoras
    /** @brief Consultora del identificador del <em>proceso</em>.
        \pre cierto.
        \post Devuelve el identificador del <em>proceso</em>.
        \par Coste 
        Tiene un coste constante O(c).
    */
    int consultar_id() const;

    /** @brief Consultora del tamaño del <em>proceso</em>.
        \pre cierto.
        \post Devuelve lo que ocupa en memoria el <em>proceso</em>.
        \par Coste 
        Tiene un coste constante O(c).
    */
    int consultar_ocupacion() const;

    /** @brief Consultora del tiempo del <em>proceso</em>.
        \pre cierto.
        \post Devuelve el tiempo que le queda por acabar el <em>proceso</em>.
        \par Coste 
        Tiene un coste constante O(c).
    */
    int consultar_tiempo() const;
};
#endif
