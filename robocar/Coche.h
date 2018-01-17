/*
 * Coche.h - abstracción de un coche robótico
 */

#ifndef Coche_h
#define Coche_h
 
#include "Arduino.h"

class Coche {
  private:
    int _velocidad;
  public:
    void setVelocidad(int velocidad);
};

#endif
