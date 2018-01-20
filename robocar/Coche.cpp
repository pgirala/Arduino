/*
 * Coche.cpp - abstracción de un coche robótico
 */
 
#include "Coche.h"

void Coche::setVelocidad(int velocidad) {
  _velocidad = velocidad;
}

void Coche::setVelocidadMotores(int velocidad, int posicionHorizontal, int posicionVertical) {
  for (int i = 1; NUMERO_MOTORES; i++)
    _motores[i].setVelocidad(velocidad);
}

