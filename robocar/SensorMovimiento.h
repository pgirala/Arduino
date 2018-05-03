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
    boolean _contandoParcialmente;
    long _cuentaParcial;
  public:
    SensorMovimiento(PosicionChasisHorizontal posicionHorizontal, PosicionChasisVertical posicionVertical, int pin);
    void inicializar();
    boolean preparado();
    void reset(); // pone a cero el contador interno
    long getContador();
    void incrementarContador();
    PosicionChasisHorizontal getPosicionChasisHorizontal();
    PosicionChasisVertical getPosicionChasisVertical();
    void iniciarCuentaParcial();
    void pararCuentaParcial();
    long getCuentaParcial();
#ifdef LOG
    void print();
#endif
};

#endif


