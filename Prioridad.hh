/** @file Prioridad.hh
    @brief Especificación de la clase prioridad.
*/
#ifndef PRIORIDAD_HH
#define PRIORIDAD_HH
#ifndef NO_DIAGRAM
#include <queue>
#include <iostream>
#endif
#include "Proceso.hh"
using namespace std;

/** @class Prioridad
    @brief Representa una Prioridad.
    
    En la clase se almacenan procesos por orden de antiguedad y tienen contadores
    que dicen cuantos procesos se han enviado con exito al cluster y cuantos han sido
    rechazados.
*/
class Prioridad{
    private:

    /** @brief Representa el interior de la prioridad, donde se almacenan los procesos a la espera
       por orden de antiguedad, el primero de todos es el más antiguo.
    */
    queue<Proceso> a;

    /** @brief Representa la cantidad de procesos acceptados por el clúster de la prioridad. */
    int enviados;

    /** @brief Representa la cantidad de procesos rechazdos por el clúster de la prioridad.*/
    int rechazados;
    public:

    /*Constructora*/
    /** @brief Constructora de la clase.
        \pre cierto.
        \post Crea una prioridad vacia, és decir sin procesos.
        \par Coste 
        Tiene un coste cosntante O(c).
    */
    Prioridad();

    /*Modificadoras*/
    /** @brief Añade un nuevo proceso a la Prioridad.
        \pre cierto.
        \post El proceso a sido añadido a la Prioridad.
        \par Coste 
        Tiene un coste constante O(c).
    */
    void añadir_proceso(const Proceso& b);

    /** @brief Se imprime todos los procesos de la prioridad por orden de antiguedad.
        \pre cierto.
        \post Se a imprimido los procesos de la prioridad por orden de antiguedad.
        \par Coste 
        Tiene un coste lineal respecto al numero de procesos n O(n).
    */
    void imprimir_proridad();

    /** @brief Devuelve el proceso más antiguo eliminandolo de la prioridad.
        \pre Que la prioridad no este vacia.
        \post Retorna el proceso más antiguo de la prioridad, y lo elimina de dicha prioridad.
        \par Coste 
        Tiene un coste constante O(c).
    */
    Proceso extraer_proceso();

    /** @brief Auementa en una unidad los rechazos de la priridad.
        \pre cierto.
        \post Se a aumentado en una unidad los rechazos de la prioridad.
        \par Coste 
        Tiene un coste constante O(c).
    */
    void aumenta_rechazo();
    
    /** @brief Auementa en una unidad los enviados de la priridad.
        \pre cierto.
        \post Se a aumentado en una unidad los enviados de la prioridad.
        \par Coste 
        Tiene un coste constante O(c).
    */
    void aumenta_env();

    /*Consultora*/
    /** @brief Consultora de si la Prioridad tiene procesos.
        \pre cierto.
        \post Devuelve true si tiene procesos, false en caso contrario.
        \par Coste 
        Tiene un coste cosntante O(c).
    */
    bool tiene_procesos() const;

    /** @brief Consultora de si la Prioridad tiene ese proceso.
        \pre cierto.
        \post Devuelve true si el proceso esta en la Prioridad.
        \par Coste 
        Tiene un coste en el peor de los casos líneal respecto al numero de procesos
        m O(m).
    */ 
    bool esta_proceso(int id) const;

    /** @brief Consultora de la cantidad de procesos de la prioridad.
        \pre cierto.
        \post Devuelve el tamaño de la prioridad.
        \par Coste 
        Tiene un coste constante O(c).
    */
    int size() const;
};
#endif