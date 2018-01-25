/*
 * Coche.cpp - abstracción de un coche robótico
 */
 
#include "Coche.h"

void Coche::reaccionar(Orden orden) {
  _estadoOrdenado.actualizar(orden);
  actualizarEstado();
}

void Coche::actualizarEstado() {
  // TODO
  // intenta sincronizar el estado actual con el ordenado
  // si el estado actual es igual que el solicitado no hace nada
  if (_estadoActual.igual(_estadoOrdenado))
    return;

  // parada de motores
  if (_estadoOrdenado.getVelocidad() == 0 && _estadoActual.getVelocidad() != 0) {
    pararMotores(PosicionChasisHorizontal::Indiferente, PosicionChasisVertical::Indiferente);
    _estadoActual.setVelocidad(0);
    return;
  }

  // actualización de la velocidad
  if (_estadoOrdenado.getVelocidad() != 0 && _estadoActual.getVelocidad() != _estadoOrdenado.getVelocidad()) {
    establecerVelocidadMotores(_estadoOrdenado.getVelocidad(), PosicionChasisHorizontal::Indiferente, PosicionChasisVertical::Indiferente); 
    _estadoActual.setVelocidad(_estadoOrdenado.getVelocidad());
    return;
  }
}

void Coche::establecerSentidoRotacion(SentidoRotacion sentidoRotacion, PosicionChasisHorizontal posicionHorizontal, PosicionChasisVertical posicionVertical) {
  for (int i = 1; NUMERO_MOTORES; i++)
    if (_motores[i].isColocado(posicionHorizontal, posicionVertical))
      _motores[i].setSentidoRotacion(sentidoRotacion);
}

void Coche::establecerVelocidadMotores(int velocidad, PosicionChasisHorizontal posicionHorizontal, PosicionChasisVertical posicionVertical) {
  for (int i = 1; NUMERO_MOTORES; i++)
    if (_motores[i].isColocado(posicionHorizontal, posicionVertical))
      _motores[i].setVelocidad(velocidad);
}

void Coche::pararMotores(PosicionChasisHorizontal posicionHorizontal, PosicionChasisVertical posicionVertical) {
  for (int i = 1; NUMERO_MOTORES; i++)
    if (_motores[i].isColocado(posicionHorizontal, posicionVertical))
      _motores[i].parar();
}

