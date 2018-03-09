/*
 * SensorUltraSonidos.cpp - abstracción del motor de un coche robótico
 */
 
#include "SensorUltraSonidos.h"
 
SensorUltraSonidos::SensorUltraSonidos(PosicionChasisVertical posicionVertical, int echoPin, int triggerPin) : 
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
  for (int i = 0; i < 5; i++) { // mide hasta cinco veces consecutivas para evitar falsos positivos
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
   
   duration = pulseIn(_echoPin, HIGH);  //medimos el tiempo entre pulsos, en microsegundos
   
   distanceCm = duration * 10 / 292/ 2;   //convertimos a distancia, en cm
   return distanceCm;
}

#ifdef TEST
bool SensorUltraSonidos::setHayObstaculo(bool hayObs) {
  _hayObstaculo = hayObs;
}
#endif

