/*
 * Coche.cpp - abstracción de un coche robótico
 */
 
#include "Coche.h"

void Coche::funcionar(Orden orden) {
  _estadoOrdenado.actualizar(orden);
  Orden ordenEfectiva = _estadoActual.sincronizar(_estadoOrdenado);
  asumir(ordenEfectiva);
}

void Coche::asumir(Orden orden) {
  // TODO
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

