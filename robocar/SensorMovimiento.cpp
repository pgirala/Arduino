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

long SensorMovimiento::distanciaRecorrida() {
   return 0.0;
}

