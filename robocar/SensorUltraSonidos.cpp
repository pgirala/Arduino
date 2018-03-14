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
  if (_posicionVertical == PosicionChasisVertical::Delante
      && direccionVertical == DireccionMovimientoVertical::Adelante)
    return hayObstaculo();
      
  if (_posicionVertical == PosicionChasisVertical::Detras
      && direccionVertical == DireccionMovimientoVertical::Atras)
    return hayObstaculo();
  return false;
}

boolean SensorUltraSonidos::hayObstaculo() 
{
#ifdef TEST
  return _hayObstaculo;
#endif
  long cm = 0;
  for (int i = 0; i < 3; i++) { // varias veces consecutivas para evitar falsos positivos
    cm = ping();
    if (cm > 0 and cm <= DISTANCIA_SEGURIDAD)
      return true;
  }
  return false;
}

long SensorUltraSonidos::ping() {
   long duration, distanceCm;
   
   digitalWrite(_triggerPin, LOW);  //para generar un pulso limpio ponemos a LOW 4us
   delayMicroseconds(4);
   digitalWrite(_triggerPin, HIGH);  //generamos Trigger (disparo) de 10us
   delayMicroseconds(10);
   digitalWrite(_triggerPin, LOW);
   
   duration = pulseIn(_echoPin, HIGH, (DISTANCIA_SEGURIDAD + 1) * 292);  //medimos el tiempo entre pulsos, en microsegundos evitando distancias superiores a la de seguridad
   
   distanceCm = duration * 10 / 292/ 2;   //convertimos a distancia, en cm
   return (distanceCm == 0 ? DISTANCIA_SEGURIDAD + 1 : distanceCm);
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
bool SensorUltraSonidos::setHayObstaculo(bool hayObs) {
  _hayObstaculo = hayObs;
}
#endif

