/*
 * EstadoMarcha.cpp - el estado de marcha del coche (real o solicitado)
 */
 
#include "EstadoMarcha.h"
#include "Coche.h"

void EstadoMarcha::setVelocidad(int velocidad) {
  _velocidad = velocidad;
}
int EstadoMarcha::getVelocidad() {
  return _velocidad;
}

void EstadoMarcha::setDireccionHorizontal(int direccionHorizontal) {
  _direccionHorizontal = direccionHorizontal;
}

int EstadoMarcha::getDireccionHorizontal() {
  return _direccionHorizontal;
}

void EstadoMarcha::setDireccionVertical(int direccionVertical) {
  _direccionVertical = direccionVertical;
}

int EstadoMarcha::getDireccionVertical() {
  return _direccionVertical;
}

