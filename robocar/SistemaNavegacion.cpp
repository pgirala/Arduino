/*
 * SistemaNavegacion.cpp - abstracción de un sistema de navegación
 */
 
#include "SistemaNavegacion.h"

void SistemaNavegacion::inicializar() {
  _unidadMedicion.inicializar();
}

UnidadMedicion * SistemaNavegacion::getUnidadMedicion() {
  return &_unidadMedicion;
}

