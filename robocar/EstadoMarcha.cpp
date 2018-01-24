/*
 * EstadoMarcha.cpp - el estado de marcha del coche (real o solicitado)
 */
 
#include "EstadoMarcha.h"

void EstadoMarcha::setVelocidad(int velocidad) {
  _velocidad = velocidad;
}
int EstadoMarcha::getVelocidad() {
  return _velocidad;
}

void EstadoMarcha::setDireccionHorizontal(DireccionMovimientoHorizontal direccionHorizontal) {
  _direccionHorizontal = direccionHorizontal;
}

DireccionMovimientoHorizontal EstadoMarcha::getDireccionHorizontal() {
  return _direccionHorizontal;
}

void EstadoMarcha::setDireccionVertical(DireccionMovimientoVertical direccionVertical) {
  _direccionVertical = direccionVertical;
}

DireccionMovimientoVertical EstadoMarcha::getDireccionVertical() {
  return _direccionVertical;
}

void EstadoMarcha::asumir(Orden orden) {
  switch (orden)
  {
    case Orden::Indefinida:
      // no aplica ningún cambio
      break;
    case Orden::Parar:
      _velocidad = 0;
      break;
    case Orden::Arrancar:
      _velocidad = INCREMENTO_VELOCIDAD;
      break;
    case Orden::IrAdelante:
      _direccionVertical = DireccionMovimientoVertical::Adelante;
      break;
    case Orden::IrAtras:
      _direccionVertical = DireccionMovimientoVertical::Atras;
      break;
    case Orden::GirarIzquierda:
      _direccionHorizontal = DireccionMovimientoHorizontal::Izquierda;
      break;
    case Orden::GirarDerecha:
      _direccionHorizontal = DireccionMovimientoHorizontal::Derecha;
      break;
    case Orden::Acelerar:
      _velocidad = (_velocidad + INCREMENTO_VELOCIDAD > VELOCIDAD_MAXIMA ? VELOCIDAD_MAXIMA :_velocidad + INCREMENTO_VELOCIDAD);
      break;
    case Orden::Frenar:
      _velocidad = (_velocidad - INCREMENTO_VELOCIDAD > VELOCIDAD_MINIMA ? VELOCIDAD_MINIMA :_velocidad - INCREMENTO_VELOCIDAD);
      break;
   };
}

