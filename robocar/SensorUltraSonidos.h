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
    #ifdef TEST
      long _distanciaObstaculo;
    #endif
    bool hayObstaculo();
  public:
    SensorUltraSonidos(PosicionChasisHorizontal posicionHorizontal, PosicionChasisVertical posicionVertical, int echoPin, int triggerPin);
    void inicializar();
    DireccionMovimientoHorizontal getDireccionMovimientoHorizontal(DireccionMovimientoVertical direccionMovimientoVertical);
    DireccionMovimientoVertical getDireccionMovimientoVertical();
    long obtenerDistanciaObstaculo(long distanciaMaxima);
    bool hayObstaculo(DireccionMovimientoVertical direccionVertical);
    #ifdef TEST
      void setDistanciaObstaculo(long distanciaObstaculo);
      PosicionChasisHorizontal getPosicionChasisHorizontal();
      PosicionChasisVertical getPosicionChasisVertical();
    #endif
};

#endif


