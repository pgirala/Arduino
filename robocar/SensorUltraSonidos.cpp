/*
 * SensorUltraSonidos.cpp - abstracción del motor de un coche robótico
 */
 
#include "SensorUltraSonidos.h"
 
SensorUltraSonidos::SensorUltraSonidos(PosicionChasisHorizontal posicionHorizontal, PosicionChasisVertical posicionVertical, int echoPin, int triggerPin) : 
              _posicionHorizontal (posicionHorizontal),
              _posicionVertical (posicionVertical),
              _echoPin (echoPin),
              _triggerPin (triggerPin) { 
}

void SensorUltraSonidos::inicializar() {
  pinMode(_triggerPin, OUTPUT); // Ultrasonidos
  pinMode(_echoPin, INPUT);
}

// Ultrasonidos

boolean SensorUltraSonidos::hayObstaculo(DireccionMovimientoVertical direccionVertical) 
{
  if (getDireccionMovimientoVertical() == direccionVertical)
    return hayObstaculo();

  return false;
}

boolean SensorUltraSonidos::hayObstaculo() 
{
  long cm = obtenerDistanciaObstaculo(DISTANCIA_SEGURIDAD + 5);
  return (cm > 0 and cm <= DISTANCIA_SEGURIDAD); // se ha encontrado un obstáculo en el área de control
}

long SensorUltraSonidos::obtenerDistanciaObstaculo(long distanciaMaxima) {
   long duration, distanceCm;
   
   digitalWrite(_triggerPin, LOW);  //para generar un pulso limpio ponemos a LOW 4us
   delayMicroseconds(4);
   digitalWrite(_triggerPin, HIGH);  //generamos Trigger (disparo) de 10us
   delayMicroseconds(10);
   digitalWrite(_triggerPin, LOW);

   duration = pulseIn(_echoPin, HIGH, distanciaMaxima * 292);  //medimos el tiempo entre pulsos, en microsegundos evitando distancias superiores a la de seguridad

#ifdef TEST
   distanceCm = _distanciaObstaculo;
#else
   distanceCm = duration * 10 / 292/ 2;   //convertimos a distancia, en cm
#endif

   return (distanceCm == 0 ? DISTANCIA_SEGURIDAD + 1 : distanceCm); // si no se ha logrado ninguna lectura se devuelve una distancia que cae fuera del ámbito de detección de obstáculos
}

DireccionMovimientoHorizontal SensorUltraSonidos::getDireccionMovimientoHorizontal() {
  switch (_posicionHorizontal) {
    case PosicionChasisHorizontal::Izquierda:
      return DireccionMovimientoHorizontal::Izquierda;
    case PosicionChasisHorizontal::Centro:
      return DireccionMovimientoHorizontal::Recta;
    case PosicionChasisHorizontal::Derecha:
      return DireccionMovimientoHorizontal::Derecha;
    default:
      return DireccionMovimientoHorizontal::Izquierda;
  }
}

DireccionMovimientoVertical SensorUltraSonidos::getDireccionMovimientoVertical() {
  switch (_posicionVertical) {
    case PosicionChasisVertical::Delante:
      return DireccionMovimientoVertical::Adelante;
    case PosicionChasisVertical::Detras:
      return DireccionMovimientoVertical::Atras;
    default:
      return DireccionMovimientoVertical::Adelante;
  }
}

#ifdef TEST

void SensorUltraSonidos::setDistanciaObstaculo(long distanciaObstaculo) {
  _distanciaObstaculo = distanciaObstaculo;
}

PosicionChasisHorizontal SensorUltraSonidos::getPosicionChasisHorizontal() {
  return _posicionHorizontal;
}

PosicionChasisVertical SensorUltraSonidos::getPosicionChasisVertical() {
  return _posicionVertical;
}
      
#endif

