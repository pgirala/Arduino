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
    Motor _motores[NUMERO_MOTORES] = {Motor(1, PosicionChasisHorizontal::Izquierda, PosicionChasisVertical::Detras, 60), 
                                      Motor(2, PosicionChasisHorizontal::Derecha, PosicionChasisVertical::Detras, 70), 
                                      Motor(3, PosicionChasisHorizontal::Derecha, PosicionChasisVertical::Delante, 75), 
                                      Motor(4, PosicionChasisHorizontal::Izquierda, PosicionChasisVertical::Delante, 70)};
    // estados de la marcha
    EstadoMarcha _estadoActual;
    EstadoMarcha _estadoOrdenado;
    // sensor de ultrasonidos
    SensorUltraSonidos _sensoresUS[NUMERO_SENSORES_US] = {SensorUltraSonidos(PosicionChasisVertical::Delante, ECHO_PIN_DELANTERO, TRIGGER_PIN_DELANTERO),
                                                           SensorUltraSonidos(PosicionChasisVertical::Detras, ECHO_PIN_TRASERO, TRIGGER_PIN_TRASERO)};
    // acciones dirigidas a los motores
    void establecerDireccion();
    void establecerVelocidadMotores();
    void establecerVelocidadMotores(int velocidad);
    void pararMotores();
    void pararMotoresPorReversion();
    // acciones del coche
    void actualizarEstado();
    bool hayObstaculo(DireccionMovimientoVertical direccionVertical);
  public:
    void inicializar();
    void reaccionar(Orden orden);
    void print();
};

#endif
