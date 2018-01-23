/*
 * Motor.cpp - abstracción del motor de un coche robótico
 */
 
#include "Motor.h"

Motor::Motor(int numero, PosicionChasisHorizontal posicionHorizontal, PosicionChasisVertical posicionVertical, int ajuste = 0) : 
              _posicionHorizontal (posicionHorizontal), 
              _posicionVertical (posicionVertical),
              _ajuste (ajuste) {
  _motorReal = new AF_DCMotor(numero, MOTOR34_1KHZ);
  setSentidoRotacion(SentidoRotacion::Directa);
  setVelocidad(0); // parado
}

void Motor::setSentidoRotacion(SentidoRotacion sentidoRotacion) {
  _sentidoRotacion = sentidoRotacion;
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

