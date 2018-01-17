/*
 * Motor.cpp - abstracción del motor de un coche robótico
 */
 
#include "Arduino.h"

#include "Motor.h"

void Motor::setVelocidad(int velocidad) {
  _velocidad = velocidad;
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

void Motor::setReverso(boolean reverso) {
  _reverso = reverso;
}

boolean Motor::isReverso() {
  return _reverso;
}

boolean Motor::isDirecto() {
  return !isReverso();
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
