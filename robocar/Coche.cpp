/*
 * Coche.cpp - abstracción de un coche robótico
 */
 
#include "Coche.h"

void Coche::inicializar() {
  for (int i = 0; i < NUMERO_SENSORES_US; i++)
    _sensoresUS[i].inicializar();
}

void Coche::reaccionar(Orden orden) {
  _estadoOrdenado.actualizar(orden);
  //if (!_estadoActual.igual(_estadoOrdenado))
  //  _estadoOrdenado.print(); // TEST
  actualizarEstado();
}

void Coche::actualizarEstado() {
  if (_estadoActual.igual(_estadoOrdenado))
    return;
    
  Serial.println("SITUACION INICIAL"); // TEST
  this->print();
  
  pararMotoresPorReversion(); // evita problemas con los motores que tenga que revertir el sentido
  establecerDireccion();
  establecerVelocidadMotores(); 
  _estadoActual.copiar(_estadoOrdenado);
  
  Serial.println("SITUACION FINAL"); // TEST
  this->print();
  Serial.println("D (aDelante) T (aTrás) + (acelerar) - (frenar) I (Izquierda) R (deRecha) E (rEcto) P (Pausa /continuar) F (indeFinida) ");
}

void Coche::establecerDireccion() {
  for (int i = 0; i < NUMERO_MOTORES; i++)
    _motores[i].setSentidoRotacion(_motores[i].obtenerSentidoRotacion(_estadoOrdenado.getDireccionHorizontal(), _estadoOrdenado.getDireccionVertical()));
}

void Coche::establecerVelocidadMotores() {
  for (int i = 0; i < NUMERO_MOTORES; i++)
    if (_motores[i].getSentidoRotacion() != SentidoRotacion::Indefinido)
      _motores[i].setVelocidad(_estadoOrdenado.getVelocidad());
}

void Coche::pararMotoresPorReversion() {
  bool parada = false;
  
  for (int i = 0; i < NUMERO_MOTORES; i++)
    if (_motores[i].getSentidoRotacion() != SentidoRotacion::Indefinido
          && _motores[i].obtenerSentidoRotacion(_estadoOrdenado.getDireccionHorizontal(), _estadoOrdenado.getDireccionVertical()) != SentidoRotacion::Indefinido
          && _motores[i].obtenerSentidoRotacion(_estadoOrdenado.getDireccionHorizontal(), _estadoOrdenado.getDireccionVertical()) != _motores[i].getSentidoRotacion()) {
      _motores[i].parar();
      parada = true;
    }
  if (parada)
    delay(TIEMPO_PROTECCION_REVERSION); // deja que los motores se paren antes de revertir la marcha
}

void Coche::print() { // TEST
  Serial.println("\tEstado actual");
  _estadoActual.print();
  Serial.println("\tEstado ordenado");
  _estadoOrdenado.print();
  for (int i = 0; i < NUMERO_MOTORES; i++) {
    Serial.print("\tMotor "); Serial.println(i + 1);
    _motores[i].print();    
  }
}

