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
  public:
    SensorMovimiento(PosicionChasisHorizontal posicionHorizontal, PosicionChasisVertical posicionVertical, int pin);
    long distanciaRecorrida(); // distancia recorrida desde la última medición
    void inicializar();
};

#endif


