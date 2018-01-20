/*
 * Motor.h - abstracción de un coche robótico
 */

#ifndef Motor_h
#define Motor_h
 
#include "Arduino.h"
#include <AFMotor.h>

//dirección de giro
#define INDEFINIDO 0
#define DIRECTO 1
#define REVERSO 2

class Motor {
  private:
    // giro
    int _sentidoGiro = INDEFINIDO;
    int _velocidad = 0;
    int _ajuste = 0; // para calibrar diferencias en el comportamiento de los motores
    // posicionamiento
    int _posicionHorizontal; // izquierda o derecha
    int _posicionVertical; // delante o detrás
    // motor real
    AF_DCMotor * _motorReal; // el motor de verdad
  public:
    Motor(int numero, int posicionHorizontal, int posicionVertical, int ajuste = 0);
  
    void setSentidoGiro(int sentidoGiro);
    int getSentidoGiro();

    void setVelocidad(int velocidad);
    int getVelocidad();

    void setAjuste(int ajuste);
    int getAjuste();

    void setPosicionHorizontal(int posicionHorizontal);
    int getPosicionHorizontal();
    
    void setPosicionVertical(int posicionVertical);
    int getPosicionVertical();
};

#endif
