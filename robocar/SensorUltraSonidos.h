/*
 * SensorUltraSonidos.h - abstracción de un sensor de ultrasonidos
 */

#ifndef SensorUltraSonidos_h
#define SensorUltraSonidos_h

#include "comun.h"

class SensorUltraSonidos {
  private:
    PosicionChasisVertical _posicionVertical; // delante o detrás
    int _triggerPin;
    int _echoPin;
    #ifdef TEST
      bool _hayObstaculo;
    #endif
    long ping();
    bool hayObstaculo();
  public:
    SensorUltraSonidos(PosicionChasisVertical posicionVertical, int echoPin, int triggerPin);
    void inicializar();
    bool hayObstaculo(DireccionMovimientoVertical direccionVertical);
    #ifdef TEST
      bool setHayObstaculo(bool hayObs);
    #endif
};

#endif


