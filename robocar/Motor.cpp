/*
 * Motor.cpp - abstracción del motor de un coche robótico
 */
 
#include "Motor.h"

Motor::Motor(int numero, int posicionHorizontal, int posicionVertical, int ajuste = 0) : 
              _posicionHorizontal (posicionHorizontal), 
              _posicionVertical (posicionVertical),
              _ajuste (ajuste) {
  _motorReal = new AF_DCMotor(numero, MOTOR34_1KHZ);
  setSentidoGiro(INDEFINIDO);
  setVelocidad(0); // parado
}

void Motor::setSentidoGiro(int sentidoGiro) {
  _sentidoGiro = sentidoGiro;
}

int Motor::getSentidoGiro() {
  return _sentidoGiro;
}

void Motor::setVelocidad(int velocidad) {
  _velocidad = velocidad;
  _motorReal->setSpeed(velocidad);
}

int Motor::getVelocidad() {
  return _velocidad;
}

void Motor::setAjuste(int Ajuste) {
  _ajuste = Ajuste;
}

int Motor::getAjuste() {
  return _ajuste;
}

void Motor::setPosicionHorizontal(int posicionHorizontal) {
  _posicionHorizontal = posicionHorizontal;
}

int Motor::getPosicionHorizontal() {
  return _posicionHorizontal;
}

void Motor::setPosicionVertical(int posicionVertical) {
  _posicionVertical = posicionVertical;
}

int Motor::getPosicionVertical() {
  return _posicionVertical;
}
