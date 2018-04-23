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

UnidadDeteccionObstaculos * Coche::getUnidadDeteccionObstaculos() {
  return &_unidadDeteccionObstaculos;
}

void Coche::inicializar() {
  _unidadDeteccionObstaculos.inicializar();
  _sistemaNavegacion.inicializar();
}

void Coche::reaccionar(Orden orden) {
  _estadoOrdenado.actualizar(orden);
  actualizarEstado();
  tratarObstaculos();
}

boolean Coche::estaEvitandoObstaculo() {
  return _estadoPrevioObstaculo != NULL;
}

void Coche::tratarObstaculos() {
  // lo más urgente es detectar choques
  if (_unidadDeteccionObstaculos.hayColision(_estadoActual.getDireccionVertical())) {
  #ifdef LOG
      Serial.println("\t\tSe ha detectado una colisión en la dirección de avance");
  #endif    
    tratarColision();
    return;
  }
  // tratamento ordinario de detección de obstáculos
  _unidadDeteccionObstaculos.escanearObstaculos(); // primero realiza un ciclo de detección de obstáculos
  
  if (estaEvitandoObstaculo()) {
    if (!_unidadDeteccionObstaculos.hayObstaculo(_estadoPrevioObstaculo->getDireccionVertical())) {
      #ifdef LOG
          Serial.println("\t\tHa desaparecido el obstáculo en la dirección de avance original");
      #endif    
      _estadoOrdenado.copiar(*_estadoPrevioObstaculo);
       delete _estadoPrevioObstaculo;
       _estadoPrevioObstaculo = NULL;
       return;
    }
  }
  
  if (_unidadDeteccionObstaculos.hayObstaculo(_estadoActual.getDireccionVertical()))
    evitarObstaculo(); 
}

void Coche::tratarColision() {
  if (!estaEvitandoObstaculo()) {
    #ifdef LOG
        Serial.println("\t\tSe guarda el estado original de marcha");
    #endif
    _estadoPrevioObstaculo = new EstadoMarcha();
    _estadoPrevioObstaculo->copiar(_estadoActual);
  }
  // no es posible girar ya que no hay margen por lo que revierte la marcha para liberar el bloqueo por colisión
  DireccionMovimientoVertical direccionOriginalChoque = _estadoActual.getDireccionVertical();
  _estadoOrdenado.copiar(_estadoActual);
  _estadoOrdenado.setDireccionHorizontal(DireccionMovimientoHorizontal::Recta);
  _estadoOrdenado.setDireccionVertical(_estadoOrdenado.getDireccionVerticalOpuesta());
  actualizarEstado();
  // se queda en este estado hasta que no se libere de la colisión o detecte otra en el otro sentido, en cuyo caso se para
  while (_unidadDeteccionObstaculos.hayColision(direccionOriginalChoque))
    if (_unidadDeteccionObstaculos.hayColision(_estadoActual.getDireccionVertical())) {
      #ifdef LOG
          Serial.print("\t\t¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡¡Obstáculos en las dos direcciones de avance!!!!!!!!!!!!!!!!!!!!!!"); 
      #endif  
      pararMotores(); // para los motores para evitar el choque
      _estadoOrdenado.copiar(_estadoActual);
      return;      
    }
}

void Coche::evitarObstaculo() {
  if (!estaEvitandoObstaculo()) {
    #ifdef LOG
        Serial.println("\t\tSe guarda el estado original de marcha");
    #endif
    _estadoPrevioObstaculo = new EstadoMarcha();
    _estadoPrevioObstaculo->copiar(_estadoActual);
  }
  
  DireccionMovimientoHorizontal direccionEscapeHorizontal = _estadoActual.getDireccionHorizontal();

  if (!_unidadDeteccionObstaculos.encontrarDireccionEscape(direccionEscapeHorizontal, _estadoActual.getDireccionVertical())) {
#ifdef LOG
    Serial.print("\t\tNo hay salida"); 
#endif  
    pararMotores(); // para los motores para evitar el choque
    _estadoOrdenado.copiar(_estadoActual);
    return;
  }
  
#ifdef LOG
  Serial.print("\t\tDirección de escape horizontal: "); Serial.println(direccionesMovimientoHorizontal[static_cast<int>(direccionEscapeHorizontal)]); 
#endif  

  _estadoOrdenado.copiar(_estadoActual);
  _estadoOrdenado.setDireccionHorizontal(direccionEscapeHorizontal); // en la siguiente iteración se cambiará la dirección
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
  _unidadDeteccionObstaculos.reset();
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

#endif


