/*
 * CuentaMovimiento.h - abstracción de un contador de radios de la rueda
 */

#ifndef CuentaMovimiento_h
#define CuentaMovimiento_h

#include "comun.h"

class CuentaMovimiento {
  private:
    boolean _contando = false;
    long _cuenta = 0;
  public:
    void iniciar(long contador);
    void parar(long contador);
    long getCuenta();
};

#endif


