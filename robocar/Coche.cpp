/*
 * Coche.cpp - abstracción de un coche robótico
 */
 
#include "Coche.h"

void Coche::inicializar() {
  for (int i = 0; i < NUMERO_SENSORES_US; i++)
    _sensoresUS[i].inicializar();
}

void Coche::reaccionar(Orden orden) {
  _estadoOrdenado.actualizar(orden);

  if (hayObstaculo(_estadoOrdenado.getDireccionVertical())) { // TODO mejorar la respuesta ante obstaculos, evitándolos
    pararMotores();
    return;
  }
  
  actualizarEstado();
}

void Coche::actualizarEstado() {
  if (_estadoActual.igual(_estadoOrdenado))
    return;

#ifdef TEST    
  Serial.println("SITUACION INICIAL");
  this->print();
#endif
  
  pararMotoresPorReversion(); // evita problemas con los motores que tenga que revertir el sentido
  establecerDireccion();
  establecerVelocidadMotores(); 
  _estadoActual.copiar(_estadoOrdenado);

#ifdef TEST
  Serial.println("SITUACION FINAL"); // TEST
  this->print();
  Serial.println("D (aDelante) T (aTrás) + (acelerar) - (frenar) I (Izquierda) R (deRecha) E (rEcto) P (Pausa /continuar) F (indeFinida) ");
#endif
}

void Coche::establecerDireccion() {
  for (int i = 0; i < NUMERO_MOTORES; i++)
    _motores[i].setSentidoRotacion(_motores[i].obtenerSentidoRotacion(_estadoOrdenado.getDireccionHorizontal(), _estadoOrdenado.getDireccionVertical()));
}

void Coche::establecerVelocidadMotores() {
  establecerVelocidadMotores(_estadoOrdenado.getVelocidad());
}

void Coche::establecerVelocidadMotores(int velocidad) {
  for (int i = 0; i < NUMERO_MOTORES; i++)
    if (_motores[i].getSentidoRotacion() != SentidoRotacion::Indefinido)
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
    
  if (parada)
    delay(TIEMPO_PROTECCION_REVERSION); // deja que los motores se paren antes de revertir la marcha
}

boolean Coche::hayObstaculo(DireccionMovimientoVertical direccionVertical) 
{  
  for (int i = 0; i < NUMERO_SENSORES_US; i++) {
    if (_sensoresUS[i].hayObstaculo(direccionVertical))
      return true;
  }

  return false;
}

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

