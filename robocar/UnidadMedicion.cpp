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

void UnidadMedicion::iniciarCuenta(int indice) {
  for (int i = 0; i < NUMERO_SENSORES_MOVIMIENTO; i++)
    _sensoresMovimiento[i].iniciarCuenta(indice);
}

void UnidadMedicion::pararCuenta(int indice) {
  for (int i = 0; i < NUMERO_SENSORES_MOVIMIENTO; i++)
    _sensoresMovimiento[i].pararCuenta(indice);
}

long UnidadMedicion::getCuentaMedia(int indice) {
  long suma = 0;
  
  for (int i = 0; i < NUMERO_SENSORES_MOVIMIENTO; i++)
    suma += _sensoresMovimiento[i].getCuenta(indice);

  return suma / NUMERO_SENSORES_MOVIMIENTO;
}

long UnidadMedicion::getCuentaMedia(int indice, PosicionChasisHorizontal posicionChasisHorizontal) {
  long suma = 0;
  int ocurrencias = 0;
  
  for (int i = 0; i < NUMERO_SENSORES_MOVIMIENTO; i++)
    if (_sensoresMovimiento[i].getPosicionChasisHorizontal() == posicionChasisHorizontal) {
      suma += _sensoresMovimiento[i].getCuenta(indice);
      ocurrencias += 1;
    }

  if (ocurrencias = 0)
    return 0;
    
  return suma / ocurrencias;
}

void UnidadMedicion::iniciarCuentaSincronizacion() {
  iniciarCuenta(CUENTA_SINCRONIZACION);
}

void UnidadMedicion::pararCuentaSincronizacion() {
  pararCuenta(CUENTA_SINCRONIZACION);  
}

long UnidadMedicion::getCuentaSincronizacion(PosicionChasisHorizontal posicionChasisHorizontal, PosicionChasisVertical posicionChasisVertical){
  return getSensorMovimiento(posicionChasisHorizontal, posicionChasisVertical)->getCuenta(CUENTA_SINCRONIZACION);  
}

long UnidadMedicion::getCuentaMediaSincronizacion() {
  return getCuentaMedia(CUENTA_SINCRONIZACION);    
}

void UnidadMedicion::iniciarComputoRecorrido() {
  iniciarCuenta(CUENTA_DISTANCIA);
}

double UnidadMedicion::getDistancia() { // distancia recorrida. ATENCIÓN (solo es útil si el movimiento es adelante o atrás
  return getCuentaMedia(CUENTA_DISTANCIA);
}

double UnidadMedicion::getAngulo() { // ángulo recorrido. ATENCIÓN (solo es útil si se ha descrito un giro)
  long distanciaIzquierda = getCuentaMedia(CUENTA_DISTANCIA, PosicionChasisHorizontal::Izquierda);
  long distanciaDerecha = getCuentaMedia(CUENTA_DISTANCIA, PosicionChasisHorizontal::Derecha);

  if (distanciaIzquierda == distanciaDerecha)
    return 0.0; // no se ha descrito un ángulo

  if (distanciaIzquierda < distanciaDerecha) // giro a la izquierda
    return -1 * calcularAngulo(distanciaIzquierda, distanciaDerecha); // ATENCIÓN el signo volverá a condicionarse si el movimiento es adelante o hacia atrás

  return calcularAngulo(distanciaDerecha, distanciaIzquierda);
}

double UnidadMedicion::calcularDistancia(long s) {
  // s es el número de radios contados
  return 2 * PI * RADIO_RUEDA * s / RADIOS_RUEDA
}

double UnidadMedicion::calcularAngulo(long s1, long s2) {
  // s1: arco menor descrito con radio r1, s2: arco mayor descrito con radio r2 + d siendo d la distancia entre ruedas
  return 0.0; // TODO  ATENCIÓN que puede haber descrito vuelta y pico, en cuyo caso primero habrá que restar la vuelta
}


#ifdef LOG

void UnidadMedicion::print() {
  for (int i = 0; i < NUMERO_SENSORES_MOVIMIENTO; i++) {
    Serial.print("\tSensor movimiento "); Serial.print(i + 1); Serial.print(": ");
    _sensoresMovimiento[i].print();    
  }
}

#endif
