/*
 * SistemaNavegacion.h - abstracción de un sistema de navegación
 */

#ifndef SistemaNavegacion_h
#define SistemaNavegacion_h

#include "comun.h"
#include "UnidadMedicion.h"

class SistemaNavegacion {
  private:
    UnidadMedicion _unidadMedicion;
  public:
    void inicializar();
    UnidadMedicion * getUnidadMedicion();
#ifdef LOG
    void print();
#endif
};

#endif


