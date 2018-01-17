/*
 * Coche.cpp - abstracción de un coche robótico
 */
 
#include "Arduino.h"

#include "Coche.h"

void Coche::setVelocidad(int velocidad) {
  _velocidad = velocidad;
}

