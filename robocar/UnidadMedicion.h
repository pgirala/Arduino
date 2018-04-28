/*
 * UnidadMedicion.h - abstracción de una unidad de medición inercial (IMU)
 */

#ifndef UnidadMedicion_h
#define UnidadMedicion_h

#include "comun.h"
#include "SensorMovimiento.h"

class UnidadMedicion {
  private:
    SensorMovimiento _sensoresMovimiento[NUMERO_SENSORES_MOVIMIENTO] = {SensorMovimiento(PosicionChasisHorizontal::Izquierda, PosicionChasisVertical::Delante, SM_PIN_DELANTERO_I),
                                                                        SensorMovimiento(PosicionChasisHorizontal::Derecha, PosicionChasisVertical::Delante, SM_PIN_DELANTERO_D),
                                                                        SensorMovimiento(PosicionChasisHorizontal::Izquierda, PosicionChasisVertical::Detras, SM_PIN_TRASERO_I),
                                                                        SensorMovimiento(PosicionChasisHorizontal::Derecha, PosicionChasisVertical::Detras, SM_PIN_TRASERO_D)};
  public:
    void inicializar();
    void reset();
    double getDistancia(); // distancia recorrida desde el último reset
    double getAngulo(); // ángulo recorrido desde el último reset
    SensorMovimiento * getSensorMovimiento(PosicionChasisHorizontal posicionChasisHorizontal, PosicionChasisVertical posicionChasisVertical);
#ifdef LOG
    void print();
#endif
};

#endif


