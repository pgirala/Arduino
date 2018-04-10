/*
 * UnidadDeteccionObstaculos.cpp - abstracción de un sensor de ultrasonidos de un coche robótico
 */
 
#include "UnidadDeteccionObstaculos.h"
 
void UnidadDeteccionObstaculos::inicializar() {
  for (int i = 0; i < NUMERO_SENSORES_US; i++)
    _sensoresUS[i].inicializar();

}

void UnidadDeteccionObstaculos::escanearObstaculos() {
  #ifdef LOG
  Serial.println("\tSituación de la unidad de detección de obstáculos: ");  
  #endif

  for (int i = 0; i < NUMERO_SENSORES_US; i++)
    _sensoresUS[i].escanearObstaculo();
}

boolean UnidadDeteccionObstaculos::hayObstaculo(DireccionMovimientoVertical direccionVertical) {  
  for (int i = 0; i < NUMERO_SENSORES_US; i++)
    if (_sensoresUS[i].hayObstaculo(direccionVertical))
      return true;
    
  return false;
}

boolean UnidadDeteccionObstaculos::encontrarDireccionEscape(DireccionMovimientoHorizontal& direccionEscape, DireccionMovimientoVertical direccionMovimientoVertical, bool evitarRecta = true) {
  // primero intenta encontrar una dirección de escape sin obstáculos
  if (encontrarDireccionEscape(direccionEscape, direccionMovimientoVertical, DISTANCIA_PERIMETRO_SEGURIDAD, evitarRecta))
    return true;
  // si no hay, intenta encontrar una dirección de escape a la que, al menos, pueda girar sin chocarse (no hay desplazamiento en vertical)
  if (encontrarDireccionEscape(direccionEscape, direccionMovimientoVertical, DISTANCIA_MINIMA_ESCAPE, evitarRecta))
    return true;  
  return false; // no hay escape, con lo que se recomienda parar
}

boolean UnidadDeteccionObstaculos::encontrarDireccionEscape(DireccionMovimientoHorizontal& direccionEscape, DireccionMovimientoVertical direccionMovimientoVertical, long distanciaPerimetro, bool evitarRecta = true) {  
  int indiceSensorEscape = -1;
  long distancia = 0;
  long distanciaSensor = 0;
  bool rectaLibre = false;

  for (int i = 0; i < NUMERO_SENSORES_US; i++) {
    if (_sensoresUS[i].getDireccionMovimientoVertical() != direccionMovimientoVertical)
      continue;

    distanciaSensor = _sensoresUS[i].getDistanciaObstaculo(); //

    if (distanciaSensor > distanciaPerimetro) {
      if (_sensoresUS[i].getDireccionMovimientoHorizontal() == DireccionMovimientoHorizontal::Recta) {
        rectaLibre = true;
        continue;    
      }

      if (_sensoresUS[i].getDireccionMovimientoHorizontal() == direccionEscape) // si la dirección que llevaba está libre, sigue con ella
        return;      

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

#ifdef TEST

void UnidadDeteccionObstaculos::reset() {
  for (int i = 0; i < NUMERO_SENSORES_US; i++)
    _sensoresUS[i].setDistanciaObstaculo(DISTANCIA_PERIMETRO_SEGURIDAD + 1);  
}

SensorUltraSonidos * UnidadDeteccionObstaculos::getSensorUltraSonidos(PosicionChasisHorizontal posicionChasisHorizontal, PosicionChasisVertical posicionChasisVertical) {
  for (int i = 0; i < NUMERO_SENSORES_US; i++)
    if (_sensoresUS[i].getPosicionChasisHorizontal() == posicionChasisHorizontal &&
        _sensoresUS[i].getPosicionChasisVertical() == posicionChasisVertical)
      return &_sensoresUS[i];

  return NULL;
}

int UnidadDeteccionObstaculos::getNumeroSensoresUltraSonidos(PosicionChasisVertical posicionChasisVertical) {
  int resultado = 0;
  
  for (int i = 0; i < NUMERO_SENSORES_US; i++)
    if (_sensoresUS[i].getPosicionChasisVertical() == posicionChasisVertical)
      resultado++;

  return resultado;
}
#endif

