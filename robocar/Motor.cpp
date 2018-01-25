/*
 * Motor.cpp - abstracción del motor de un coche robótico
 */
 
#include "Motor.h"

Motor::Motor(int numero, PosicionChasisHorizontal posicionHorizontal, PosicionChasisVertical posicionVertical, int ajuste = 0) : 
              _posicionHorizontal (posicionHorizontal), 
              _posicionVertical (posicionVertical),
              _ajuste (ajuste) {
  _motorReal = new AF_DCMotor(numero, MOTOR34_1KHZ);
  setSentidoRotacion(SentidoRotacion::Directo);
  setVelocidad(0); // parado
}

void Motor::setSentidoRotacion(SentidoRotacion sentidoRotacion) {
  _sentidoRotacion = sentidoRotacion;
  _motorReal->run(Motor::obtenerSentidoRealRotacion(sentidoRotacion));
}

SentidoRotacion Motor::getSentidoRotacion() {
  return _sentidoRotacion;
}

void Motor::setVelocidad(int velocidad) {
  _velocidad = velocidad;
  _motorReal->setSpeed(velocidad);
}

int Motor::getVelocidad() {
  return _velocidad;
}

boolean Motor::isColocado(PosicionChasisHorizontal posicionHorizontal, PosicionChasisVertical posicionVertical) {
  return (posicionHorizontal == PosicionChasisHorizontal::Indiferente || posicionHorizontal == _posicionHorizontal)
        and (posicionVertical == PosicionChasisVertical::Indiferente || posicionVertical == _posicionVertical); 
}

void Motor::parar() {
  _motorReal->run(RELEASE);
}

// obtiene el sentido de rotación a partir de una dirección vertical de movimiento
static SentidoRotacion Motor::obtenerSentidoRotacion(DireccionMovimientoVertical direccionVertical) {
  if (direccionVertical == DireccionMovimientoVertical::Atras)
    return SentidoRotacion::Reverso;
  return SentidoRotacion::Directo; // opción por defecto
}

// obtiene el sentido real de rotación
static int Motor::obtenerSentidoRealRotacion(SentidoRotacion sentidoRotacion) {
  if (sentidoRotacion == SentidoRotacion::Reverso)
    return BACKWARD;
  return FORWARD; // opción por defecto
}

