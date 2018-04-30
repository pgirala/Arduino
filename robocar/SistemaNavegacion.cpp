/*
 * SistemaNavegacion.cpp - abstracción de un sistema de navegación
 */
 
#include "SistemaNavegacion.h"

void SistemaNavegacion::inicializar() {
  _unidadMedicion.inicializar();
}

boolean SistemaNavegacion::preparado() {
  return _unidadMedicion.preparada();
}

void SistemaNavegacion::reset() {
  _unidadMedicion.reset();
}

UnidadMedicion * SistemaNavegacion::getUnidadMedicion() {
  return &_unidadMedicion;
}

#ifdef LOG

void SistemaNavegacion::print() {
  Serial.println("\tEstado del sistema de navegación: ");
  _unidadMedicion.print();
}

#endif

