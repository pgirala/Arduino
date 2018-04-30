/*
 * Motor.cpp - abstracción del motor de un coche robótico
 */
 
#include "Motor.h"

Motor::Motor(int numero, PosicionChasisHorizontal posicionHorizontal, PosicionChasisVertical posicionVertical) : 
              _posicionHorizontal (posicionHorizontal), 
              _posicionVertical (posicionVertical) {
  _motorReal = new AF_DCMotor(numero, MOTOR34_1KHZ);
  _velocidad = 0; // parado
  _sentidoRotacion = SentidoRotacion::Indefinido;
}

void Motor::calibrar(UnidadMedicion * unidadMedicion) {
  SensorMovimiento * sensorMovimiento = unidadMedicion->getSensorMovimiento(_posicionHorizontal, _posicionVertical);
  
  if (sensorMovimiento == NULL)
    return;

  long contadorInicial = sensorMovimiento->getContador();
  _ajuste = 0;
  parar();
  
  while (_ajuste < VELOCIDAD_MAXIMA_MOTOR && sensorMovimiento->getContador() > contadorInicial + RADIOS_RUEDA) {
    setSentidoRotacion(SentidoRotacion::Directo);
    _ajuste += INCREMENTO_VELOCIDAD;
    setVelocidad(INCREMENTO_VELOCIDAD);
    delay(200); // espera para ver si se mueve al menos una vuelta de rueda
    parar();
  }

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
  if (_velocidad == 0)
    return SentidoRotacion::Indefinido;
    
  return Motor::obtenerSentidoRotacion(direccionHorizontal, direccionVertical, _posicionHorizontal, _posicionVertical);
}

static SentidoRotacion Motor::obtenerSentidoRotacionDefecto(DireccionMovimientoVertical direccionVertical) {
  return (direccionVertical == DireccionMovimientoVertical::Adelante ? SentidoRotacion::Directo : SentidoRotacion::Reverso);
}

static SentidoRotacion Motor::obtenerSentidoRotacionContrario(SentidoRotacion sentidoRotacion) {
  return (sentidoRotacion == SentidoRotacion::Directo ? SentidoRotacion::Reverso : SentidoRotacion::Directo);
}

// obtiene el sentido de rotación a partir de las direcciones de movimiento y de la posición del motor en el chasis
static SentidoRotacion Motor::obtenerSentidoRotacion(DireccionMovimientoHorizontal direccionHorizontal, DireccionMovimientoVertical direccionVertical, 
                                                      PosicionChasisHorizontal posicionHorizontal, PosicionChasisVertical posicionVertical) {
  SentidoRotacion sentidoDefecto = obtenerSentidoRotacionDefecto(direccionVertical);
  SentidoRotacion sentidoContrario = obtenerSentidoRotacionContrario(sentidoDefecto);
  
  if (direccionHorizontal == DireccionMovimientoHorizontal::Recta)
    return sentidoDefecto;

  if (direccionHorizontal == DireccionMovimientoHorizontal::Izquierda) {
    if (posicionHorizontal == PosicionChasisHorizontal::Izquierda)
      return sentidoContrario;
      
    if (posicionHorizontal == PosicionChasisHorizontal::Derecha)
      return sentidoDefecto;
  }

  if (direccionHorizontal == DireccionMovimientoHorizontal::Derecha) {
    if (posicionHorizontal == PosicionChasisHorizontal::Izquierda)
      return sentidoDefecto;
      
    if (posicionHorizontal == PosicionChasisHorizontal::Derecha)
      return sentidoContrario;
  }

  return SentidoRotacion::Indefinido;
}

// obtiene el sentido real de rotación
static int Motor::obtenerSentidoRealRotacion(SentidoRotacion sentidoRotacion) {
  if (sentidoRotacion == SentidoRotacion::Reverso)
    return BACKWARD;
    
  if (sentidoRotacion == SentidoRotacion::Directo)
    return FORWARD;

  return RELEASE; // opción por defecto
}

#ifdef LOG

void Motor::print() {
  Serial.print("\t\tSentido rotación: "); Serial.print(sentidosRotacion[static_cast<int>(_sentidoRotacion)]);
  Serial.print("  Velocidad: "); Serial.println(_velocidad);
}

#endif

#ifdef TEST

void Motor::reset() {
  _velocidad = 0; // parado
  _sentidoRotacion = SentidoRotacion::Indefinido;  
}

#endif
