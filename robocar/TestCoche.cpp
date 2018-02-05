#include "TestCoche.h"

void TestCoche::ejecutar(Coche *coche) {
  testParar(coche);
  testArrancar(coche);
  testAcelerar(coche);
}

void TestCoche::testParar(Coche *coche) {
  Serial.print("\ttestParar\t");
  desactivarSensores(coche);
  coche ->reaccionar(Orden::Parar);
  
  if (coche->getEstadoActual().getVelocidad() != 0)
    Serial.println("El coche no para");
  else
    Serial.println("OK");
}

void TestCoche::testArrancar(Coche *coche) {
  Serial.print("\ttestArrancar\t");
  desactivarSensores(coche);
  int velocidadAnterior = coche->getEstadoActual().getVelocidad();
  coche ->reaccionar(Orden::Parar);
  coche ->reaccionar(Orden::Arrancar);
  
  if (coche->getEstadoActual().getVelocidad() != velocidadAnterior)
    Serial.println("El coche no recupera la velocidad anterior");
  else
    Serial.println("OK");
}

void TestCoche::testAcelerar(Coche *coche) {
  Serial.print("\ttestAcelerar\t");
  desactivarSensores(coche);
  coche->pararMotores(); // partimos de un estado controlado
  coche->reaccionar(Orden::Arrancar);
  int velocidadAnterior = coche->getEstadoActual().getVelocidad();
  coche ->reaccionar(Orden::Acelerar);

  if (coche->getEstadoActual().getVelocidad() <= velocidadAnterior)
    Serial.println("El coche no acelera");
  else
    Serial.println("OK");
}

void TestCoche::desactivarSensores(Coche *coche) {
  for (int i = 0; i < NUMERO_SENSORES_US; i++)
    coche->getSensoresUS()[i].setHayObstaculo(false);
}

