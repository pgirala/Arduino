/*
 * Coche.cpp - abstracción de un coche robótico
 */
 
#include "Coche.h"

EstadoMarcha Coche::getEstadoActual() {
  return _estadoActual;
}

void Coche::inicializar() {
  for (int i = 0; i < NUMERO_SENSORES_US; i++)
    _sensoresUS[i].inicializar();
}

void Coche::reaccionar(Orden orden) {
  _estadoOrdenado.actualizar(orden);
#ifdef LOG
    Serial.print("\t\tComprobación de obstáculo en la dirección: "); Serial.println(static_cast<int>(_estadoOrdenado.getDireccionVertical()));
#endif 
  if (hayObstaculo(_estadoOrdenado.getDireccionVertical())) {
#ifdef LOG
    Serial.println("\t\tObstáculo detectado");
#endif    
    evitarObstaculo();
#ifdef LOG
    Serial.println("\t\tObstáculo evitado");
#endif     return;
  }
  
  actualizarEstado();
}

void Coche::evitarObstaculo() {
  DireccionMovimientoHorizontal direccionEscape;

  if (!encontrarDireccionEscape(_estadoOrdenado.getDireccionVertical(), direccionEscape)) {
#ifdef LOG
    Serial.println("\t\tNo hay escape");
#endif    
    establecerVelocidadMotores(0); // para los motores para evitar el choque
    return;
  }
  
  establecerDireccion(direccionEscape, _estadoOrdenado.getDireccionVertical());
  
#ifdef LOG
  Serial.print("\t\tDirección de escape: "); Serial.println(static_cast<int>(direccionEscape)); 
#endif  

  while (hayObstaculo(_estadoOrdenado.getDireccionVertical())); // gira hasta que no detecta un obstáculo
  
  establecerDireccion(_estadoOrdenado.getDireccionHorizontal(), _estadoOrdenado.getDireccionVertical()); // vuelve a comportarse como antes
  return;
}

boolean Coche::encontrarDireccionEscape(DireccionMovimientoVertical direccionMovimientoVertical, DireccionMovimientoHorizontal& direccionEscape) {
  int indiceSensorEscape = -1;
  long distancia = 0;
  long distanciaSensor = 0;

  for (int i = 0; i < NUMERO_SENSORES_US; i++) {
    if (_sensoresUS[i].getDireccionMovimientoVertical() != direccionMovimientoVertical)
      continue;
    
    distanciaSensor = _sensoresUS[i].obtenerDistanciaObstaculo(3 * DISTANCIA_SEGURIDAD); // amplía la dirección chequeada para encontrar la mejor ruta de escape

    if (distanciaSensor >= distancia && distanciaSensor > DISTANCIA_SEGURIDAD) {
      distancia = distanciaSensor;
      indiceSensorEscape = i;
    }
  }

  if (indiceSensorEscape >= 0) { // ha encontrado una dirección
    direccionEscape = _sensoresUS[indiceSensorEscape].getDireccionMovimientoHorizontal(); // devuelve la mejor dirección de escape
    return true;
  } else
    return false;
}

void Coche::actualizarEstado() {
  if (_estadoActual.igual(_estadoOrdenado))
    return;

#ifdef LOG

  Serial.println("SITUACION INICIAL");
  this->print();

#endif

  pararMotoresPorReversion(); // evita problemas con los motores que tenga que revertir el sentido
  establecerVelocidadMotores(); 
  establecerDireccion();
  _estadoActual.copiar(_estadoOrdenado);

#ifdef LOG

  Serial.println("SITUACION FINAL"); // TEST
  this->print();
  Serial.println("D (aDelante) T (aTrás) + (acelerar) - (frenar) I (Izquierda) R (deRecha) E (rEcto) P (Pausa /continuar) F (indeFinida) ");

#endif
}

void Coche::establecerDireccion() {
  establecerDireccion(_estadoOrdenado.getDireccionHorizontal(), _estadoOrdenado.getDireccionVertical());
}

void Coche::establecerDireccion(DireccionMovimientoHorizontal direccionHorizontal, DireccionMovimientoVertical direccionVertical) {
  for (int i = 0; i < NUMERO_MOTORES; i++)
    _motores[i].setSentidoRotacion(_motores[i].obtenerSentidoRotacion(direccionHorizontal, direccionVertical));
}

void Coche::establecerVelocidadMotores() {
  establecerVelocidadMotores(_estadoOrdenado.getVelocidad());
}

void Coche::establecerVelocidadMotores(int velocidad) {
  for (int i = 0; i < NUMERO_MOTORES; i++)
    _motores[i].setVelocidad(velocidad);
}

void Coche::pararMotores() {
  _estadoActual.setVelocidad(0);
  establecerVelocidadMotores(0);
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

#ifndef TEST

  if (parada)
    delay(TIEMPO_PROTECCION_REVERSION); // deja que los motores se paren antes de revertir la marcha; solo es necesario si se está en modo no test

#endif
}

boolean Coche::hayObstaculo(DireccionMovimientoVertical direccionVertical) 
{  
  for (int i = 0; i < NUMERO_SENSORES_US; i++)
    if (_sensoresUS[i].hayObstaculo(direccionVertical))
      return true;
    
  return false;
}

#ifdef LOG

void Coche::print() {
  Serial.print("\tEstado actual: ");
  _estadoActual.print();
  Serial.print("\tEstado orden.: ");
  _estadoOrdenado.print();
  for (int i = 0; i < NUMERO_MOTORES; i++) {
    Serial.print("\tMotor "); Serial.print(i + 1); Serial.print(": ");
    _motores[i].print();    
  }
}

#endif

#ifdef TEST

void Coche::reset() {
  // coche parado dirigido hacia adelante
  _estadoActual.reset();
  _estadoOrdenado.reset();  
  // sensores de ultrasonidos
  for (int i = 0; i < NUMERO_SENSORES_US; i++)
    _sensoresUS[i].setDistanciaObstaculo(DISTANCIA_SEGURIDAD + 1);
  // motores
  for (int i = 0; i < NUMERO_MOTORES; i++)
    _motores[i].reset();
}

int Coche::comprobarSincronizacionMotores() {
  for (int i = 0; i < NUMERO_MOTORES; i++)
    if (_motores[i].getSentidoRotacion() != _motores[i].obtenerSentidoRotacion(_estadoActual.getDireccionHorizontal(), _estadoActual.getDireccionVertical())
        || _motores[i].getVelocidad() != _estadoActual.getVelocidad())
      return i + 1;
  return 0;
}


SensorUltraSonidos * Coche::getSensorUltraSonidos(PosicionChasisHorizontal posicionChasisHorizontal, PosicionChasisVertical posicionChasisVertical) {
  for (int i = 0; i < NUMERO_SENSORES_US; i++)
    if (_sensoresUS[i].getPosicionChasisHorizontal() == posicionChasisHorizontal &&
        _sensoresUS[i].getPosicionChasisVertical() == posicionChasisVertical)
      return &_sensoresUS[i];

  return NULL;
}

#endif

