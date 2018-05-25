/*
 * Servo.cpp - abstracción del Servo de un coche robótico
 */
 
#include "ServoMotor.h"

ServoMotor::ServoMotor() {
  _servoReal = new Servo();
}

void ServoMotor::inicializar() {
  setAngulo(90);
  setSentidoRotacion(SentidoRotacion::Directo);
}

void ServoMotor::setAngulo(int angulo) {
  _angulo = angulo;
  
  _servoReal->write(_angulo);
}

int ServoMotor::getAngulo() {
  return _angulo;
}

void ServoMotor::girar() {
  int nuevoAngulo = getAngulo() + (getSentidoRotacion() == SentidoRotacion::Reverso ? -1 : 1);
  if (nuevoAngulo < 0)
    nuevoAngulo = 0;
  if (nuevoAngulo > 180)
    nuevoAngulo = 180;
  setAngulo(nuevoAngulo);
}

void ServoMotor::setSentidoRotacion(SentidoRotacion sentidoRotacion) {
  _sentidoRotacion = sentidoRotacion;
}

SentidoRotacion ServoMotor::getSentidoRotacion() {
  return _sentidoRotacion;
}
#ifdef LOG

void ServoMotor::print() {
  Serial.print(" ángulo servo "); Serial.print(_angulo);
}

#endif
