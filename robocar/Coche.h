/*
 * Coche.h - abstracción de un coche robótico
 */

#ifndef Coche_h
#define Coche_h
 
#include "Arduino.h"

#include "Motor.h"

class Coche {
  private:
    int _velocidad;
    Motor motores[4] = {Motor(IZQUIERDA, DETRAS), Motor(DERECHA, DETRAS), Motor(DERECHA, DELANTE), Motor(IZQUIERDA, DELANTE)};
  public:
    void setVelocidad(int velocidad);
};

#endif
