/*
 * Coche.cpp - abstracción de un coche robótico
 */
 
#include "Coche.h"

void Coche::reaccionar(Orden orden) {
  _estadoOrdenado.actualizar(orden);
  actualizarEstado();
}

void Coche::actualizarEstado() {
  // intenta sincronizar el estado actual con el ordenado
  // si el estado actual es igual que el solicitado no hace nada
  if (_estadoActual.igual(_estadoOrdenado))
    return;

  // parada de motores
  if (_estadoOrdenado.getVelocidad() == VELOCIDAD_MINIMA && _estadoActual.getVelocidad() != VELOCIDAD_MINIMA) {
    pararMotores(PosicionChasisHorizontal::Indiferente, PosicionChasisVertical::Indiferente);
    _estadoActual.setVelocidad(0);
    return;
  }

  // actualización de la velocidad
  if (_estadoOrdenado.getVelocidad() != VELOCIDAD_MINIMA && _estadoActual.getVelocidad() != _estadoOrdenado.getVelocidad()) {
    establecerVelocidadMotores(_estadoOrdenado.getVelocidad(), PosicionChasisHorizontal::Indiferente, PosicionChasisVertical::Indiferente); 
    _estadoActual.setVelocidad(_estadoOrdenado.getVelocidad());
    return;
  }

  // actualización de la dirección vertical de marcha
  // TODO: atención si va hacia adelante girando hacia la izquierda o derecha si revierte la marcha iría recto hacia atrás, pero debería girar en el mismo sentido
  if (_estadoActual.getDireccionVertical() != _estadoOrdenado.getDireccionVertical()) {
    // primero para los motores para protegerlos
    pararMotores(PosicionChasisHorizontal::Indiferente, PosicionChasisVertical::Indiferente);
    // invierte la dirección de giro de los motores
    establecerSentidoRotacion(Motor::obtenerSentidoRotacion(_estadoOrdenado.getDireccionVertical()), PosicionChasisHorizontal::Indiferente, PosicionChasisVertical::Indiferente); 
    _estadoActual.getDireccionVertical() == _estadoOrdenado.getDireccionVertical();
    // recupera la velocidad que llevaba
    establecerVelocidadMotores(_estadoActual.getVelocidad(), PosicionChasisHorizontal::Indiferente, PosicionChasisVertical::Indiferente); 
    return;
  }
  // actualizacion de la dirección horizontal de marcha
  if (_estadoActual.getDireccionHorizontal() != _estadoOrdenado.getDireccionHorizontal()) {
    
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
