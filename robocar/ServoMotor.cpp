/*
 * Servo.cpp - abstracción del Servo de un coche robótico
 */
 
#include "ServoMotor.h"

ServoMotor::ServoMotor() {
  _servoReal = new Servo();
}

void ServoMotor::inicializar() {
  _servoReal->attach(SERVO_MOTOR_PIN);  
  setAngulo(90);
  setSentidoRotacion(SentidoRotacion::Directo); -
}

void ServoMotor::setAngulo(int angulo) {
  _angulo = angulo;
  _servoReal->write(_angulo);
  delay(90);
}

int ServoMotor::getAngulo() {
  return _angulo;
}

void ServoMotor::girar() {
  int nuevoAngulo = getAngulo() + (getSentidoRotacion() == SentidoRotacion::Reverso ? -1 : 1) * PASO_SERVO_MOTOR;
  
  if (nuevoAngulo < 0) {
    nuevoAngulo = 0;
    setSentidoRotacion(SentidoRotacion::Directo);
  }
  
  if (nuevoAngulo > 180) {
    nuevoAngulo = 180;
    setSentidoRotacion(SentidoRotacion::Reverso);
  }

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
