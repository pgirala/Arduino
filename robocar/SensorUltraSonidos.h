/*
 * SensorUltraSonidos.h - abstracción de un sensor de ultrasonidos
 */

#ifndef SensorUltraSonidos_h
#define SensorUltraSonidos_h

#include "Arduino.h"
#include "Motor.h"

// parámetros pra el control de distancia por ultrasonidos
const int DISTANCIA_SEGURIDAD = 20; // centímetros

class SensorUltraSonidos {
  private:
    PosicionChasisVertical _posicionVertical; // delante o detrás
    int _triggerPin;
    int _echoPin;
    bool ping();
  public:
    SensorUltraSonidos(PosicionChasisVertical posicionVertical, int echoPin, int triggerPin);
    void inicializar();
    bool hayObstaculo();
};

#endif


