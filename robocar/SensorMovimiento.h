/*
 * SensorMovimiento.h - abstracción de un sensor de movimiento
 */

#ifndef SensorMovimiento_h
#define SensorMovimiento_h

#include "comun.h"

class SensorMovimiento {
  private:
    PosicionChasisHorizontal _posicionHorizontal; // izquierda o derecha
    PosicionChasisVertical _posicionVertical; // delante o detrás
    int _pin;
    volatile long _contador;
  public:
    SensorMovimiento(PosicionChasisHorizontal posicionHorizontal, PosicionChasisVertical posicionVertical, int pin);
    void inicializar();
    void reset(); // pone a cero el contador interno
    long getContador();
    void incrementarContador();
    PosicionChasisHorizontal getPosicionChasisHorizontal();
    PosicionChasisVertical getPosicionChasisVertical();
};

#endif


