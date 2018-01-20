/*
 * Coche.h - abstracción de un coche robótico
 */

#ifndef Coche_h
#define Coche_h
 
#include "Arduino.h"

#include "Motor.h"

#define NUMERO_MOTORES 4

// posiciones en el chasis
#define INDIFERENTE 0

// horizontales
#define IZQUIERDA 1
#define DERECHA 2

// verticales
#define DELANTE 1
#define DETRAS 2

class Coche {
  private:
    int _velocidad;
    Motor _motores[NUMERO_MOTORES] = {Motor(1, IZQUIERDA, DETRAS), Motor(2, DERECHA, DETRAS), Motor(3, DERECHA, DELANTE), Motor(4, IZQUIERDA, DELANTE)};
    void setVelocidadMotores(int velocidad, int posicionHorizontal, int posicionVertical);
    
  public:
    void setVelocidad(int velocidad);
};

#endif
