/*
 * Coche.cpp - abstracción de un coche robótico
 */
 
#include "Coche.h"

void Coche::setVelocidad(int velocidad) {
  _velocidad = velocidad;
}

void Coche::setVelocidadMotores(int velocidad, int posicionHorizontal, int posicionVertical) {
  for (int i = 1; NUMERO_MOTORES; i++)
    if (_motores[i].isColocado(posicionHorizontal, posicionVertical))
      _motores[i].setVelocidad(velocidad);
}

void Coche::pararMotores(int posicionHorizontal, int posicionVertical) {
  for (int i = 1; NUMERO_MOTORES; i++)
    if (_motores[i].isColocado(posicionHorizontal, posicionVertical))
      _motores[i].parar();
}

void Coche::setDireccionGiroMotores(int sentidoGiro, int posicionHorizontal, int posicionVertical) {
  for (int i = 1; NUMERO_MOTORES; i++)
    if (_motores[i].isColocado(posicionHorizontal, posicionVertical))
      _motores[i].setSentidoGiro(sentidoGiro);
}
