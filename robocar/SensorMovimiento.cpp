/*
 * SensorMovimiento.cpp - abstracción de un sensor de movimiento de un coche robótico
 */
 
#include "SensorMovimiento.h"

SensorMovimiento::SensorMovimiento(PosicionChasisHorizontal posicionHorizontal, PosicionChasisVertical posicionVertical, int pin) : 
              _posicionHorizontal (posicionHorizontal),
              _posicionVertical (posicionVertical),
              _pin (pin) { 
}

void SensorMovimiento::inicializar() {
  if (_pin > 0)
    pinMode(_pin, INPUT);
}

// Movimiento

long SensorMovimiento::distanciaRecorrida() {
   return 0.0;
}

