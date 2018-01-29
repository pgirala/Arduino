/*
 * Motor.cpp - abstracción del motor de un coche robótico
 */
 
#include "Motor.h"

Motor::Motor(int numero, PosicionChasisHorizontal posicionHorizontal, PosicionChasisVertical posicionVertical, int ajuste = 0) : 
              _posicionHorizontal (posicionHorizontal), 
              _posicionVertical (posicionVertical),
              _ajuste (ajuste) {
  _motorReal = new AF_DCMotor(numero, MOTOR34_1KHZ);
  _velocidad = 0; // parado
  _sentidoRotacion = SentidoRotacion::Indefinido;
}

void Motor::setSentidoRotacion(SentidoRotacion sentidoRotacion) {
  _motorReal->run(Motor::obtenerSentidoRealRotacion(sentidoRotacion));
  if (sentidoRotacion == SentidoRotacion::Indefinido)
    _velocidad = 0;
  _sentidoRotacion = sentidoRotacion;
}

SentidoRotacion Motor::getSentidoRotacion() {
  return _sentidoRotacion;
}

void Motor::setVelocidad(int velocidad) {
  _velocidad = velocidad;
  int velocidadEfectiva = velocidad;
  
  if (_velocidad == 0)
    _sentidoRotacion = SentidoRotacion::Indefinido;
  else
    velocidadEfectiva = velocidadEfectiva + _ajuste;

  velocidadEfectiva = (velocidadEfectiva > VELOCIDAD_MAXIMA_MOTOR ? VELOCIDAD_MAXIMA_MOTOR : velocidadEfectiva);

  _motorReal->setSpeed(velocidadEfectiva);
}

int Motor::getVelocidad() {
  return _velocidad;
}

void Motor::parar() {
  _motorReal->run(RELEASE);
  _velocidad = 0;
  _sentidoRotacion = SentidoRotacion::Indefinido;
}

// obtiene el sentido de rotación a partir de las direcciones de movimiento y de la posición del motor en el chasis
static SentidoRotacion Motor::obtenerSentidoRotacion(DireccionMovimientoHorizontal direccionHorizontal, DireccionMovimientoVertical direccionVertical) {
  return Motor::obtenerSentidoRotacion(direccionHorizontal, direccionVertical, _posicionHorizontal, _posicionVertical);
}

// obtiene el sentido de rotación a partir de las direcciones de movimiento y de la posición del motor en el chasis
static SentidoRotacion Motor::obtenerSentidoRotacion(DireccionMovimientoHorizontal direccionHorizontal, DireccionMovimientoVertical direccionVertical, 
                                                      PosicionChasisHorizontal posicionHorizontal, PosicionChasisVertical posicionVertical) {

  if (direccionVertical == DireccionMovimientoVertical::Adelante) {
    if (direccionHorizontal == DireccionMovimientoHorizontal::Recta)
      return SentidoRotacion::Directo;

    if (direccionHorizontal == DireccionMovimientoHorizontal::Izquierda) {
      if (posicionHorizontal == PosicionChasisHorizontal::Izquierda)
        return SentidoRotacion::Reverso;
        
      if (posicionHorizontal == PosicionChasisHorizontal::Derecha)
        return SentidoRotacion::Directo;
    }

    if (direccionHorizontal == DireccionMovimientoHorizontal::Derecha) {
      if (posicionHorizontal == PosicionChasisHorizontal::Izquierda)
        return SentidoRotacion::Directo;
        
      if (posicionHorizontal == PosicionChasisHorizontal::Derecha)
        return SentidoRotacion::Reverso;
    }
  }
    
  if (direccionVertical == DireccionMovimientoVertical::Atras) {
    if (direccionHorizontal == DireccionMovimientoHorizontal::Recta)
      return SentidoRotacion::Reverso;

    if (direccionHorizontal == DireccionMovimientoHorizontal::Izquierda) {
      if (posicionHorizontal == PosicionChasisHorizontal::Izquierda)
        return SentidoRotacion::Directo;
        
      if (posicionHorizontal == PosicionChasisHorizontal::Derecha)
        return SentidoRotacion::Reverso;
    }

    if (direccionHorizontal == DireccionMovimientoHorizontal::Derecha) {
      if (posicionHorizontal == PosicionChasisHorizontal::Izquierda)
        return SentidoRotacion::Reverso;
        
      if (posicionHorizontal == PosicionChasisHorizontal::Derecha)
        return SentidoRotacion::Directo;
    }
  }

  return SentidoRotacion::Indefinido;;
}

// obtiene el sentido real de rotación
static int Motor::obtenerSentidoRealRotacion(SentidoRotacion sentidoRotacion) {
  if (sentidoRotacion == SentidoRotacion::Reverso)
    return BACKWARD;
    
  if (sentidoRotacion == SentidoRotacion::Directo)
    return FORWARD;

  return RELEASE; // opción por defecto
}

void Motor::print() { // TEST
  Serial.print("\t\tSentido rotación: "); Serial.print(static_cast<int>(_sentidoRotacion));
  Serial.print("  Velocidad: "); Serial.println(_velocidad);
}
