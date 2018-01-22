/*
 * Coche.cpp - abstracción de un coche robótico
 */
 
#include "Coche.h"

void Coche::setVelocidad(int velocidad) {
  _velocidad = velocidad;
}

void Coche::funcionar(int orden) {
  // TODO
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

void Coche::setSentidoRotacion(SentidoRotacion sentidoRotacion, int posicionHorizontal, int posicionVertical) {
  for (int i = 1; NUMERO_MOTORES; i++)
    if (_motores[i].isColocado(posicionHorizontal, posicionVertical))
      _motores[i].setSentidoRotacion(sentidoRotacion);
}
