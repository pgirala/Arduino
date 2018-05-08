/*
 * SensorUltraSonidos.cpp - abstracción de un sensor de ultrasonidos de un coche robótico
 */
 
#include "SensorUltraSonidos.h"
 
SensorUltraSonidos::SensorUltraSonidos(PosicionChasisHorizontal posicionHorizontal, PosicionChasisVertical posicionVertical, int echoPin, int triggerPin, int choquePin) : 
              _posicionHorizontal (posicionHorizontal),
              _posicionVertical (posicionVertical),
              _echoPin (echoPin),
              _triggerPin (triggerPin),
              _choquePin (choquePin) { 
}

void SensorUltraSonidos::inicializar() {
  pinMode(_triggerPin, OUTPUT); // Ultrasonidos
  pinMode(_echoPin, INPUT);
  pinMode(_choquePin, INPUT);
  _distanciaObstaculo = 0;
}

boolean SensorUltraSonidos::preparado() {
   return medirEco(1000) > 0;
}

void SensorUltraSonidos::escanearObstaculo() {
  _distanciaObstaculo = obtenerDistanciaObstaculo(DISTANCIA_PERIMETRO_SEGURIDAD + 5);
#ifdef LOG_EXTRA
  Serial.print("\t\t");
  Serial.print(posicionesChasisHorizontal[static_cast<int>(_posicionHorizontal)]);
  Serial.print(" "); Serial.print(posicionesChasisVertical[static_cast<int>(_posicionVertical)]); 
  Serial.print(" "); Serial.print(_distanciaObstaculo); Serial.print(" cm "); Serial.println(hayObstaculo() ? " (OBSTÁCULO DETECTADO)" : "");
#endif
}

boolean SensorUltraSonidos::hayColision(DireccionMovimientoVertical direccionVertical) {
  if (getDireccionMovimientoVertical() == direccionVertical)
    return hayColision();

  return false;  
}

boolean SensorUltraSonidos::hayColision() {
#ifdef TEST
  return _colision;
#endif

  if (_choquePin <= 0) // está desactivado
    return false;

  boolean resultado = digitalRead(_choquePin) == HIGH;
#ifdef LOG  
  if (resultado) {
    Serial.print("\t\t");
    Serial.print(posicionesChasisHorizontal[static_cast<int>(_posicionHorizontal)]);
    Serial.print(" "); Serial.print(posicionesChasisVertical[static_cast<int>(_posicionVertical)]); 
    Serial.print(" "); Serial.println(" (¡¡¡¡¡¡¡¡¡COLISIÓN!!!!!!!!!)"); 
    Serial.println("--------------------------------");
  }
#endif
  return resultado;
}

boolean SensorUltraSonidos::hayObstaculo(DireccionMovimientoVertical direccionVertical) 
{
  if (getDireccionMovimientoVertical() == direccionVertical)
    return hayObstaculo();

  return false;
}

boolean SensorUltraSonidos::hayObstaculo() 
{
  long cm = getDistanciaObstaculo();
  return (cm > 0 and cm <= DISTANCIA_PERIMETRO_SEGURIDAD); // se ha encontrado un obstáculo en el área de control
}

long SensorUltraSonidos::medirEco(long distanciaMaxima) {
   digitalWrite(_triggerPin, LOW);  //para generar un pulso limpio ponemos a LOW 4us
   delayMicroseconds(4);
   digitalWrite(_triggerPin, HIGH);  //generamos Trigger (disparo) de 10us
   delayMicroseconds(10);
   digitalWrite(_triggerPin, LOW);

   return pulseIn(_echoPin, HIGH, distanciaMaxima * 292 * 2 / 10);  //medimos el tiempo entre pulsos, en microsegundos evitando distancias superiores a la de seguridad
}

long SensorUltraSonidos::obtenerDistanciaObstaculo(long distanciaMaxima) {
   long duration, distanceCm;
   
   digitalWrite(_triggerPin, LOW);  //para generar un pulso limpio ponemos a LOW 4us
   delayMicroseconds(4);
   digitalWrite(_triggerPin, HIGH);  //generamos Trigger (disparo) de 10us
   delayMicroseconds(10);
   digitalWrite(_triggerPin, LOW);

   duration = medirEco(distanciaMaxima);
#ifdef TEST
   distanceCm = _distanciaObstaculo;
#else
   distanceCm = duration * 10 / 292/ 2;   //convertimos a distancia, en cm

#endif
   delayMicroseconds(ALCANCE_MAXIMO * 292 * 2 / 10); // para que no interfiera con el siguiente sensor
   return (distanceCm == 0 ? DISTANCIA_PERIMETRO_SEGURIDAD + 1 : distanceCm); // si no se ha logrado ninguna lectura se devuelve una distancia que cae fuera del ámbito de detección de obstáculos
}

DireccionMovimientoHorizontal SensorUltraSonidos::getDireccionMovimientoHorizontal() {
  DireccionMovimientoHorizontal resultado = DireccionMovimientoHorizontal::Izquierda;
  switch (_posicionHorizontal) {
    case PosicionChasisHorizontal::Izquierda:
      resultado = DireccionMovimientoHorizontal::Izquierda;
      break;
    case PosicionChasisHorizontal::Centro:
      resultado = DireccionMovimientoHorizontal::Recta;
      break;
    case PosicionChasisHorizontal::Derecha:
      resultado = DireccionMovimientoHorizontal::Derecha;
  }
  return resultado;
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

long SensorUltraSonidos::getDistanciaObstaculo() {
  return _distanciaObstaculo;
}

#ifdef TEST

void SensorUltraSonidos::setDistanciaObstaculo(long distanciaObstaculo) {
  _distanciaObstaculo = distanciaObstaculo;
}

void SensorUltraSonidos::setColision(bool colision) {
  _colision = colision;
}

PosicionChasisHorizontal SensorUltraSonidos::getPosicionChasisHorizontal() {
  return _posicionHorizontal;
}

PosicionChasisVertical SensorUltraSonidos::getPosicionChasisVertical() {
  return _posicionVertical;
}
      
#endif

