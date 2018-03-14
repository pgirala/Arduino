/*
 * SensorUltraSonidos.h - abstracción de un sensor de ultrasonidos
 */

#ifndef SensorUltraSonidos_h
#define SensorUltraSonidos_h

#include "comun.h"

class SensorUltraSonidos {
  private:
    PosicionChasisHorizontal _posicionHorizontal; // izquierda o derecha
    PosicionChasisVertical _posicionVertical; // delante o detrás
    int _triggerPin;
    int _echoPin;
    long ping(long distanciaMaxima);
    #ifdef TEST
      bool _hayObstaculo;
    #endif
    bool hayObstaculo();
  public:
    SensorUltraSonidos(PosicionChasisHorizontal posicionHorizontal, PosicionChasisVertical posicionVertical, int echoPin, int triggerPin);
    void inicializar();
    long ping();
    DireccionMovimientoHorizontal getDireccionMovimientoHorizontal();
    DireccionMovimientoVertical getDireccionMovimientoVertical();
    bool hayObstaculo(DireccionMovimientoVertical direccionVertical);
    #ifdef TEST
      bool setHayObstaculo(bool hayObs);
    #endif
};

#endif


