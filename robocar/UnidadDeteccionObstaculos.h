/*
 * UnidadDeteccionObstaculos.h - coordina la acción de los sensores de ultrasonidos
 */

#ifndef UnidadDeteccionObstaculos_h
#define UnidadDeteccionObstaculos_h

#include "comun.h"
#include "SensorUltrasonidos.h"
#include "EstadoMarcha.h"

class UnidadDeteccionObstaculos {
  private:
    // sensor de ultrasonidos
    SensorUltraSonidos _sensoresUS[NUMERO_SENSORES_US] = {SensorUltraSonidos(PosicionChasisHorizontal::Izquierda, PosicionChasisVertical::Delante, ECHO_PIN_DELANTERO_I, TRIGGER_PIN_DELANTERO_I, CHOQUE_PIN_DELANTERO_I),
                                                           SensorUltraSonidos(PosicionChasisHorizontal::Centro, PosicionChasisVertical::Delante, ECHO_PIN_DELANTERO_C, TRIGGER_PIN_DELANTERO_C, CHOQUE_PIN_DELANTERO_C),
                                                           SensorUltraSonidos(PosicionChasisHorizontal::Derecha, PosicionChasisVertical::Delante, ECHO_PIN_DELANTERO_D, TRIGGER_PIN_DELANTERO_D, CHOQUE_PIN_DELANTERO_D),
                                                           SensorUltraSonidos(PosicionChasisHorizontal::Centro, PosicionChasisVertical::Detras, ECHO_PIN_TRASERO_C, TRIGGER_PIN_TRASERO_C, CHOQUE_PIN_TRASERO_C),
                                                           SensorUltraSonidos(PosicionChasisHorizontal::Izquierda, PosicionChasisVertical::Detras, ECHO_PIN_TRASERO_I, TRIGGER_PIN_TRASERO_I, CHOQUE_PIN_TRASERO_I),
                                                           SensorUltraSonidos(PosicionChasisHorizontal::Derecha, PosicionChasisVertical::Detras, ECHO_PIN_TRASERO_D, TRIGGER_PIN_TRASERO_D, CHOQUE_PIN_TRASERO_D)};
    bool encontrarDireccionEscape(DireccionMovimientoHorizontal& direccionEscape, DireccionMovimientoVertical direccionMovimientoVertical, long distanciaPerimetro, bool evitarRecta = true);
    SensorUltraSonidos * obtenerSensorDiametralmenteOpuesto(DireccionMovimientoHorizontal direccionHorizontal, DireccionMovimientoVertical direccionVertical);
  public:
    void inicializar();
    void escanearObstaculos();
    bool hayObstaculo(DireccionMovimientoVertical direccionVertical);
    bool hayColision(DireccionMovimientoVertical direccionVertical);
    bool encontrarDireccionEscape(DireccionMovimientoHorizontal& direccionEscape, DireccionMovimientoVertical direccionMovimientoVertical, bool evitarRecta = true);
#ifdef TEST
    void reset();
    SensorUltraSonidos * getSensorUltraSonidos(PosicionChasisHorizontal posicionChasisHorizontal, PosicionChasisVertical posicionChasisVertical);
    int getNumeroSensoresUltraSonidos(PosicionChasisVertical posicionChasisVertical);
#endif
};

#endif


