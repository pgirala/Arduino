/*
 * Coche.h - abstracción de un coche robótico
 */

#ifndef Coche_h
#define Coche_h
 
#include "Arduino.h"

#include "EstadoMarcha.h"
#include "SensorUltraSonidos.h"
#include "Motor.h"

// motores

#define NUMERO_MOTORES 4
#define TIEMPO_PROTECCION_REVERSION 100 // milisegundos

// ultrasonidos

#define NUMERO_SENSORES_US 2
#define ECHO_PIN_DELANTERO 33
#define TRIGGER_PIN_DELANTERO 35
#define ECHO_PIN_TRASERO 37
#define TRIGGER_PIN_TRASERO 39

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
    void pararMotoresPorReversion();
    // acciones del coche
    void actualizarEstado();
    bool hayObstaculo(DireccionMovimientoVertical direccionVertical);
  public:
    void inicializar();
    void reaccionar(Orden orden);
    void print(); // TEST
};

#endif
