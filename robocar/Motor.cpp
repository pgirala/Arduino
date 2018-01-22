/*
 * Motor.cpp - abstracción del motor de un coche robótico
 */
 
#include "Motor.h"
#include "Coche.h"

Motor::Motor(int numero, int posicionHorizontal, int posicionVertical, int ajuste = 0) : 
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

boolean Motor::isColocado(int posicionHorizontal, int posicionVertical) {
  return (posicionHorizontal == INDIFERENTE || posicionHorizontal == getPosicionHorizontal())
        and (posicionVertical == INDIFERENTE || posicionVertical == getPosicionVertical());
}

void Motor::parar() {
  _motorReal->run(RELEASE);
}

