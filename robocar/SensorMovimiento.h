/*
 * SensorMovimiento.h - abstracción de un sensor de movimiento
 */

#ifndef SensorMovimiento_h
#define SensorMovimiento_h

#include "comun.h"

#include "CuentaMovimiento.h"

class SensorMovimiento {
  private:
    PosicionChasisHorizontal _posicionHorizontal; // izquierda o derecha
    PosicionChasisVertical _posicionVertical; // delante o detrás
    int _pin;
    volatile long _contador;
    CuentaMovimiento _cuentasMovimiento[NUMERO_CUENTAS_MOVIMIENTO] = {CuentaMovimiento()};
  public:
    SensorMovimiento(PosicionChasisHorizontal posicionHorizontal, PosicionChasisVertical posicionVertical, int pin);
    void inicializar();
    boolean preparado();
    void reset(); // pone a cero el contador interno
    long getContador();
    void incrementarContador();
    PosicionChasisHorizontal getPosicionChasisHorizontal();
    PosicionChasisVertical getPosicionChasisVertical();
    void iniciarCuenta(int indice);
    void pararCuenta(int indice);
    long getCuenta(int indice);
#ifdef LOG
    void print();
#endif
};

#endif


