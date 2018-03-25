/*
 * EstadoMarcha.cpp - el estado de marcha del coche (real o solicitado)
 */
 
#include "EstadoMarcha.h"

EstadoMarcha::EstadoMarcha() {
  
}

EstadoMarcha::EstadoMarcha(int velocidad, DireccionMovimientoHorizontal direccionHorizontal, DireccionMovimientoVertical direccionVertical) :
                            _velocidad (velocidad),
                            _direccionHorizontal (direccionHorizontal),
                            _direccionVertical (direccionVertical) {
  
}

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

void EstadoMarcha::actualizar(Orden orden) {
  switch (orden)
  {
    case Orden::Indefinida:
      // no aplica ningún cambio
      break;
    case Orden::Parar:
      _velocidadPreviaParada = _velocidad;
      _velocidad = 0;
      break;
    case Orden::Arrancar:
      _velocidad = _velocidadPreviaParada;
      break;
    case Orden::IrAdelante:
      _direccionVertical = DireccionMovimientoVertical::Adelante;
      break;
    case Orden::IrAtras:
      _direccionVertical = DireccionMovimientoVertical::Atras;
      break;
    case Orden::Recto:
      _direccionHorizontal = DireccionMovimientoHorizontal::Recta;
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
      _velocidad = (_velocidad - INCREMENTO_VELOCIDAD > 0 ? _velocidad - INCREMENTO_VELOCIDAD : 0);
      break;
   };
}

bool EstadoMarcha::igual(EstadoMarcha otroEstado) {
  return getVelocidad() == otroEstado.getVelocidad()
        and getDireccionVertical() == otroEstado.getDireccionVertical()
        and getDireccionHorizontal() == otroEstado.getDireccionHorizontal();
}

void EstadoMarcha::copiar(EstadoMarcha otroEstado) {
  _velocidad = otroEstado.getVelocidad();
  _direccionVertical = otroEstado.getDireccionVertical();
  _direccionHorizontal = otroEstado.getDireccionHorizontal();
}

#ifdef LOG

void EstadoMarcha::print() {
  Serial.print("\t\tVelocidad: "); Serial.print(_velocidad);
  Serial.print("  Direccion horizontal: "); Serial.print(direccionesMovimientoHorizontal[static_cast<int>(_direccionHorizontal)]);
  Serial.print("  Direccion vertical: "); Serial.println(direccionesMovimientoVertical[static_cast<int>(_direccionVertical)]);
}

#endif

#ifdef TEST

void EstadoMarcha::reset() {
  _velocidad = 0;
  _direccionHorizontal = DireccionMovimientoHorizontal::Recta;
  _direccionVertical = DireccionMovimientoVertical::Adelante;
}

#endif
