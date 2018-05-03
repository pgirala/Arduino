/*
 * UnidadMedicion.cpp - abstracción de una unidad de medición inercial (IMU)
 */
 
#include "UnidadMedicion.h"

void UnidadMedicion::inicializar() {
  for (int i = 0; i < NUMERO_SENSORES_MOVIMIENTO; i++)
    _sensoresMovimiento[i].inicializar();
}

boolean UnidadMedicion::preparada() {
  for (int i = 0; i < NUMERO_SENSORES_MOVIMIENTO; i++)
    if (!_sensoresMovimiento[i].preparado())
      return false;
  return true;
}

void UnidadMedicion::reset() {
  for (int i = 0; i < NUMERO_SENSORES_MOVIMIENTO; i++)
    _sensoresMovimiento[i].reset();
}

SensorMovimiento * UnidadMedicion::getSensorMovimiento(PosicionChasisHorizontal posicionChasisHorizontal, PosicionChasisVertical posicionChasisVertical) {
  for (int i = 0; i < NUMERO_SENSORES_MOVIMIENTO; i++)
    if (_sensoresMovimiento[i].getPosicionChasisHorizontal() == posicionChasisHorizontal &&
        _sensoresMovimiento[i].getPosicionChasisVertical() == posicionChasisVertical)
      return &_sensoresMovimiento[i];

  return NULL;
}

void UnidadMedicion::iniciarCuentaParcial() {
  for (int i = 0; i < NUMERO_SENSORES_MOVIMIENTO; i++)
    _sensoresMovimiento[i].iniciarCuentaParcial();
}

void UnidadMedicion::pararCuentaParcial() {
  for (int i = 0; i < NUMERO_SENSORES_MOVIMIENTO; i++)
    _sensoresMovimiento[i].pararCuentaParcial();
}

long UnidadMedicion::getCuentaParcialMedia() {
  long suma = 0;
  
  for (int i = 0; i < NUMERO_SENSORES_MOVIMIENTO; i++)
    suma += _sensoresMovimiento[i].getCuentaParcial();

  return suma / NUMERO_SENSORES_MOVIMIENTO;
}

double UnidadMedicion::getDistancia() { // distancia recorrida desde el último reset
  return 0.0;
}

double getAngulo() { // ángulo recorrido desde el último reset
  return 0.0;
}

#ifdef LOG

void UnidadMedicion::print() {
  for (int i = 0; i < NUMERO_SENSORES_MOVIMIENTO; i++) {
    Serial.print("\tSensor movimiento "); Serial.print(i + 1); Serial.print(": ");
    _sensoresMovimiento[i].print();    
  }
}

#endif
