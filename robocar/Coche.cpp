/*
 * Coche.cpp - abstracción de un coche robótico
 */
 
#include "Coche.h"

void Coche::reaccionar(Orden orden) {
  _estadoOrdenado.actualizar(orden);
  //if (!_estadoActual.igual(_estadoOrdenado))
  //  _estadoOrdenado.print(); // TEST
  actualizarEstado();
}

void Coche::actualizarEstado() {
  if (_estadoActual.igual(_estadoOrdenado))
    return;

  pararMotoresPorReversion(); // evita problemas con los motores que tenga que revertir el sentido
  establecerDireccion();
  establecerVelocidadMotores(); 
  
  _estadoActual.copiar(_estadoOrdenado);
}

void Coche::establecerDireccion() {
  for (int i = 1; NUMERO_MOTORES; i++)
    _motores[i].setSentidoRotacion(_motores[i].obtenerSentidoRotacion(_estadoOrdenado.getDireccionHorizontal(), _estadoOrdenado.getDireccionVertical()));
}

void Coche::establecerVelocidadMotores() {
  for (int i = 1; NUMERO_MOTORES; i++)
    if (_motores[i].getSentidoRotacion() != SentidoRotacion::Indefinido)
      _motores[i].setVelocidad(_estadoOrdenado.getVelocidad());
}

void Coche::pararMotoresPorReversion() {
  for (int i = 1; NUMERO_MOTORES; i++)
    if (_motores[i].getSentidoRotacion() != SentidoRotacion::Indefinido
          && _motores[i].obtenerSentidoRotacion(_estadoOrdenado.getDireccionHorizontal(), _estadoOrdenado.getDireccionVertical()) != SentidoRotacion::Indefinido
          && _motores[i].obtenerSentidoRotacion(_estadoOrdenado.getDireccionHorizontal(), _estadoOrdenado.getDireccionVertical()) != _motores[i].getSentidoRotacion())
      _motores[i].parar();
}
