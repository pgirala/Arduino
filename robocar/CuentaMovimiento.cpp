/*
 * CuentaMovimiento.cpp - abstracción de un contador de radios de la rueda
 */
 
#include "CuentaMovimiento.h"

void CuentaMovimiento::iniciar(long contador) {
  _contando = true;
  _cuenta = contador;
}

void CuentaMovimiento::parar(long contador) {
  _contando = false;
  _cuenta -= contador;
}

long CuentaMovimiento::getCuenta() {
  if (_contando)
    return 0;
  return _cuenta;
}
