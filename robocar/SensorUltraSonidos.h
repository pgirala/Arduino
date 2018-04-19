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
    int _choquePin;
    #ifdef TEST
      bool _colision;
    #endif
    long _distanciaObstaculo;
    bool hayObstaculo();
    long obtenerDistanciaObstaculo(long distanciaMaxima);
  public:
    SensorUltraSonidos(PosicionChasisHorizontal posicionHorizontal, PosicionChasisVertical posicionVertical, int echoPin, int triggerPin, int choquePin);
    void inicializar();
    void escanearObstaculo();
    DireccionMovimientoHorizontal getDireccionMovimientoHorizontal();
    DireccionMovimientoVertical getDireccionMovimientoVertical();
    long getDistanciaObstaculo();
    bool hayObstaculo(DireccionMovimientoVertical direccionVertical);
    bool hayColision();
    bool hayColision(DireccionMovimientoVertical direccionVertical);
    #ifdef TEST
      void setDistanciaObstaculo(long distanciaObstaculo);
      void setColision(bool colision);
      PosicionChasisHorizontal getPosicionChasisHorizontal();
      PosicionChasisVertical getPosicionChasisVertical();
    #endif
};

#endif


