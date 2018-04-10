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
    long _distanciaObstaculo;
    bool hayObstaculo();
    long obtenerDistanciaObstaculo(long distanciaMaxima);
  public:
    SensorUltraSonidos(PosicionChasisHorizontal posicionHorizontal, PosicionChasisVertical posicionVertical, int echoPin, int triggerPin);
    void inicializar();
    void escanearObstaculo();
    DireccionMovimientoHorizontal getDireccionMovimientoHorizontal();
    DireccionMovimientoVertical getDireccionMovimientoVertical();
    long getDistanciaObstaculo();
    bool hayObstaculo(DireccionMovimientoVertical direccionVertical);
    #ifdef TEST
      void setDistanciaObstaculo(long distanciaObstaculo);
      PosicionChasisHorizontal getPosicionChasisHorizontal();
      PosicionChasisVertical getPosicionChasisVertical();
    #endif
};

#endif


