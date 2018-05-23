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

void SensorMovimiento::iniciarCuenta(int indice) {
  _cuentasMovimiento[indice].iniciar(_contador);
}

void SensorMovimiento::pararCuenta(int indice) {
  _cuentasMovimiento[indice].parar(_contador);
}

long SensorMovimiento::getCuenta(int indice) {
  return _cuentasMovimiento[indice].getCuenta();
}

#ifdef LOG

void SensorMovimiento::print() {
  Serial.print("\t\tContador: "); Serial.println(_contador); 
}

#endif
