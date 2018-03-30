/*
 * Coche.h - abstracción de un coche robótico
 */

#ifndef Coche_h
#define Coche_h
 
#include "comun.h"

#include "SensorUltraSonidos.h"
#include "Motor.h"
#include "EstadoMarcha.h"

class Coche {
  private:
    Motor _motores[NUMERO_MOTORES] = {Motor(1, PosicionChasisHorizontal::Izquierda, PosicionChasisVertical::Detras, AJUSTE_MOTOR_TRASERO_IZQUIERDO), 
                                      Motor(2, PosicionChasisHorizontal::Derecha, PosicionChasisVertical::Detras, AJUSTE_MOTOR_TRASERO_DERECHO), 
                                      Motor(3, PosicionChasisHorizontal::Derecha, PosicionChasisVertical::Delante, AJUSTE_MOTOR_DELANTERO_DERECHO), 
                                      Motor(4, PosicionChasisHorizontal::Izquierda, PosicionChasisVertical::Delante, AJUSTE_MOTOR_DELANTERO_IZQUIERDO)};
    // estados de la marcha
    EstadoMarcha _estadoActual{0, DireccionMovimientoHorizontal::Recta, DireccionMovimientoVertical::Adelante};
    EstadoMarcha _estadoOrdenado{0, DireccionMovimientoHorizontal::Recta, DireccionMovimientoVertical::Adelante};
    EstadoMarcha *_estadoPrevioObstaculo;
    // sensor de ultrasonidos
    SensorUltraSonidos _sensoresUS[NUMERO_SENSORES_US] = {SensorUltraSonidos(PosicionChasisHorizontal::Izquierda, PosicionChasisVertical::Delante, ECHO_PIN_DELANTERO_I, TRIGGER_PIN_DELANTERO_I),
                                                           SensorUltraSonidos(PosicionChasisHorizontal::Centro, PosicionChasisVertical::Delante, ECHO_PIN_DELANTERO_C, TRIGGER_PIN_DELANTERO_C),
                                                           SensorUltraSonidos(PosicionChasisHorizontal::Derecha, PosicionChasisVertical::Delante, ECHO_PIN_DELANTERO_D, TRIGGER_PIN_DELANTERO_D),
                                                           SensorUltraSonidos(PosicionChasisHorizontal::Centro, PosicionChasisVertical::Detras, ECHO_PIN_TRASERO_C, TRIGGER_PIN_TRASERO_C),
                                                           SensorUltraSonidos(PosicionChasisHorizontal::Centro, PosicionChasisVertical::Delante, ECHO_PIN_TRASERO_C, TRIGGER_PIN_TRASERO_C),
                                                           SensorUltraSonidos(PosicionChasisHorizontal::Derecha, PosicionChasisVertical::Delante, ECHO_PIN_TRASERO_D, TRIGGER_PIN_TRASERO_D)};
    // acciones dirigidas a los motores
    void establecerDireccion();
    void establecerVelocidadMotores();
    void establecerVelocidadMotores(int velocidad);
    void pararMotoresPorReversion();
    // acciones del coche
    void actualizarEstado();
    bool hayObstaculo(DireccionMovimientoVertical direccionVertical);
    bool estaEvitandoObstaculo();
  public:
    void inicializar();
    void reaccionar(Orden orden);
    void pararMotores();
    EstadoMarcha getEstadoActual();
    void evitarObstaculo();
    bool encontrarDireccionEscape(DireccionMovimientoHorizontal& direccionEscape, DireccionMovimientoVertical direccionMovimientoVertical, bool evitarRecta = false);
    void establecerDireccion(DireccionMovimientoHorizontal direccionHorizontal, DireccionMovimientoVertical direccionVertical);
#ifdef LOG
    void print();
#endif
#ifdef TEST
    void reset();
    void resetObstaculos();
    int comprobarSincronizacionMotores();
    SensorUltraSonidos * getSensorUltraSonidos(PosicionChasisHorizontal posicionChasisHorizontal, PosicionChasisVertical posicionChasisVertical);
    int getNumeroSensoresUltraSonidos(PosicionChasisVertical posicionChasisVertical);
#endif
};

#endif
