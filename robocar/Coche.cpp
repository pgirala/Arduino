/*
 * Coche.cpp - abstracción de un coche robótico
 */
 
#include "Coche.h"

EstadoMarcha Coche::getEstadoActual() {
  return _estadoActual;
}

SistemaNavegacion * Coche::getSistemaNavegacion() {
  return &_sistemaNavegacion;
}

void Coche::inicializar() {
  for (int i = 0; i < NUMERO_SENSORES_US; i++)
    _sensoresUS[i].inicializar();

  _sistemaNavegacion.inicializar();
}

void Coche::reaccionar(Orden orden) {
  _estadoOrdenado.actualizar(orden);
  actualizarEstado();

  if (hayObstaculo(_estadoActual.getDireccionVertical())) {
#ifdef LOG
    Serial.println("\t\tObstáculo detectado");
#endif    
    evitarObstaculo();
  } else if (estaEvitandoObstaculo()) {
    if (_estadoActual.getDireccionVertical() == _estadoPrevioObstaculo->getDireccionVertical()) { // el caso más normal: ha desaparecido el obstáculo en la dirección de avance
      #ifdef LOG
          Serial.println("\t\tHa desaparecido el obstáculo en la dirección de avance original");
      #endif    
      _estadoOrdenado.copiar(*_estadoPrevioObstaculo);
      delete _estadoPrevioObstaculo;
      _estadoPrevioObstaculo = NULL;
    } else { // se va en dirección contraria evitando un bloqueo total
      DireccionMovimientoHorizontal direccionEscapeHorizontal;
      
      if (!hayObstaculo(_estadoActual.getDireccionVerticalOpuesta())) { // ha desaparecido el obstáculo que evitaba el avance y que obligó a ir en dirección contraria
      #ifdef LOG
          Serial.println("\t\tHa desaparecido el obstáculo en la dirección de avance original yendo en la dirección contraria para evitar el bloqueo");
      #endif    
        _estadoOrdenado.copiar(*_estadoPrevioObstaculo);
        delete _estadoPrevioObstaculo;
        _estadoPrevioObstaculo = NULL;
      }
    }
  }
}

void Coche::evitarObstaculo() {
  if (!estaEvitandoObstaculo()) {
    _estadoPrevioObstaculo = new EstadoMarcha();
    _estadoPrevioObstaculo->copiar(_estadoActual);
  }
  
  DireccionMovimientoHorizontal direccionEscapeHorizontal;

  if (encontrarDireccionEscape(direccionEscapeHorizontal, _estadoActual.getDireccionVertical()))
    _estadoOrdenado.copiar(_estadoActual);
  else {
#ifdef LOG
    Serial.println("\t\tNo hay escape en la dirección de avance");
#endif    
    if (encontrarDireccionEscape(direccionEscapeHorizontal, _estadoActual.getDireccionVerticalOpuesta())) {
#ifdef LOG
      Serial.print("\t\tDirección de escape vertical: "); Serial.println(direccionesMovimientoVertical[static_cast<int>(_estadoActual.getDireccionVerticalOpuesta())]); 
#endif  
      _estadoOrdenado.copiar(_estadoActual);
      _estadoOrdenado.setDireccionVertical(_estadoActual.getDireccionVerticalOpuesta()); // revierte la marcha
    } else {
#ifdef LOG
      Serial.println("\t\tNo hay escape en la dirección contraria al avance");
#endif    
      pararMotores(); // para los motores para evitar el choque
      // TODO si no hay obstáculo en la dirección opuesta, encontrar dirección de escape en la otra dirección 
      // y cuando deje de haber obstáculos en la dirección original volver a localizar la dirección de escape (un giro a ser posible)
      _estadoOrdenado.copiar(_estadoActual);
      return;
    }
  }
  
#ifdef LOG
  Serial.print("\t\tDirección de escape horizontal: "); Serial.println(direccionesMovimientoHorizontal[static_cast<int>(direccionEscapeHorizontal)]); 
#endif  

  _estadoOrdenado.setDireccionHorizontal(direccionEscapeHorizontal); // en la siguiente iteración se cambiará la dirección
}

boolean Coche::encontrarDireccionEscape(DireccionMovimientoHorizontal& direccionEscape, DireccionMovimientoVertical direccionMovimientoVertical, bool evitarRecta = false) {
  int indiceSensorEscape = -1;
  long distancia = 0;
  long distanciaSensor = 0;
  bool rectaLibre = false;

  for (int i = 0; i < NUMERO_SENSORES_US; i++) {
    if (_sensoresUS[i].getDireccionMovimientoVertical() != direccionMovimientoVertical)
      continue;

    distanciaSensor = _sensoresUS[i].obtenerDistanciaObstaculo(DISTANCIA_SEGURIDAD); // amplía la dirección chequeada para encontrar la mejor ruta de escape

    if (distanciaSensor > DISTANCIA_SEGURIDAD) {
      if (_sensoresUS[i].getDireccionMovimientoHorizontal() == DireccionMovimientoHorizontal::Recta) {
        rectaLibre = true;
        continue;    
      }

      if (distanciaSensor >= distancia) {
        distancia = distanciaSensor;
        indiceSensorEscape = i;
      }
    }
  }

  if (indiceSensorEscape >= 0) { // ha encontrado una dirección
    direccionEscape = _sensoresUS[indiceSensorEscape].getDireccionMovimientoHorizontal(); // los giros tienen preferencia para evitar comportamiento errático
    return true;
  } 
  
  if (rectaLibre && !evitarRecta) {
    direccionEscape = DireccionMovimientoHorizontal::Recta;
    return true;
  }
  
  return false; // no hay escapatoria en la dirección de marcha
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

boolean Coche::hayObstaculo(DireccionMovimientoVertical direccionVertical) {  
  for (int i = 0; i < NUMERO_SENSORES_US; i++)
    if (_sensoresUS[i].hayObstaculo(direccionVertical))
      return true;
    
  return false;
}

boolean Coche::estaEvitandoObstaculo() {
  return _estadoPrevioObstaculo != NULL;
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
  resetObstaculos();
  // motores
  for (int i = 0; i < NUMERO_MOTORES; i++)
    _motores[i].reset();
}

void Coche::resetObstaculos() {
  for (int i = 0; i < NUMERO_SENSORES_US; i++)
    _sensoresUS[i].setDistanciaObstaculo(DISTANCIA_SEGURIDAD + 1);  
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

int Coche::getNumeroSensoresUltraSonidos(PosicionChasisVertical posicionChasisVertical) {
  int resultado = 0;
  
  for (int i = 0; i < NUMERO_SENSORES_US; i++)
    if (_sensoresUS[i].getPosicionChasisVertical() == posicionChasisVertical)
      resultado++;

  return resultado;
}
#endif


