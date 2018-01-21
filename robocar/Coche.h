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
    // acciones dirigidas a los motores
    void setVelocidadMotores(int velocidad, int posicionHorizontal, int posicionVertical);
    void pararMotores(int posicionHorizontal, int posicionVertical);
    void setDireccionGiroMotores(int sentidoGiro, int posicionHorizontal, int posicionVertical);
  public:
    // acciones dirigidas al coche
    void setVelocidad(int velocidad);
};

#endif
