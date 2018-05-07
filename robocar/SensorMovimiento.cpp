/*
 * SensorMovimiento.cpp - abstracción de un sensor de movimiento de un coche robótico
 */
 
#include "SensorMovimiento.h"

SensorMovimiento::SensorMovimiento(PosicionChasisHorizontal posicionHorizontal, PosicionChasisVertical posicionVertical, int pin) : 
              _posicionHorizontal (posicionHorizontal),
              _posicionVertical (posicionVertical),
              _pin (pin) { 
}

void SensorMovimiento::inicializar() {
  pinMode(_pin, INPUT);
  reset();
}

boolean SensorMovimiento::preparado() {
  return _contador > 0; // debe realizarse tras una parada de los motores, un reset de los sensores y un encendido de los motores.
}

// Movimiento

void SensorMovimiento::reset() {
  _contador = 0;
}

PosicionChasisHorizontal SensorMovimiento::getPosicionChasisHorizontal() {
  return _posicionHorizontal;
}

PosicionChasisVertical SensorMovimiento::getPosicionChasisVertical() {
  return _posicionVertical;
}

long SensorMovimiento::getContador() {
  return _contador;
}

void SensorMovimiento::incrementarContador() {
  _contador++;
}

void SensorMovimiento::iniciarCuentaParcial() {
  _contandoParcialmente = true;
  _cuentaParcial = _contador;
}

void SensorMovimiento::pararCuentaParcial() {
  _contandoParcialmente = false;
  _cuentaParcial -= _contador;
}

long SensorMovimiento::getCuentaParcial() {
  if (_contandoParcialmente)
    return 0;
  return _cuentaParcial;
}

#ifdef LOG

void SensorMovimiento::print() {
  Serial.print("\t\tContador: "); Serial.print(_contador);  
  Serial.print(" contando parcialmente: ");
  if (_contandoParcialmente)
    Serial.println(" sí");
  else
    Serial.print(" no. Contador parcial "); Serial.println(_contador);
}

#endif
