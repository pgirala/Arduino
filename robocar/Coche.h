/*
 * Coche.h - abstracción de un coche robótico
 */

#ifndef Coche_h
#define Coche_h
 
#include "Arduino.h"

#include "EstadoMarcha.h"
#include "Motor.h"

// motores

#define NUMERO_MOTORES 4

class Coche {
  private:
    Motor _motores[NUMERO_MOTORES] = {Motor(1, PosicionChasisHorizontal::Izquierda, PosicionChasisVertical::Detras), 
                                      Motor(2, PosicionChasisHorizontal::Derecha, PosicionChasisVertical::Detras), 
                                      Motor(3, PosicionChasisHorizontal::Derecha, PosicionChasisVertical::Delante), 
                                      Motor(4, PosicionChasisHorizontal::Izquierda, PosicionChasisVertical::Delante)};
    // estados de la marcha
    EstadoMarcha _estadoActual;
    EstadoMarcha _estadoOrdenado;
    // acciones dirigidas a los motores
    void establecerDireccion();
    void establecerVelocidadMotores();
    void pararMotoresPorReversion();
    // acciones del coche
    void actualizarEstado();
  public:
    void reaccionar(Orden orden);
};

#endif
