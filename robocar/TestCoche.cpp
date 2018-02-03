#include "TestCoche.h"

void TestCoche::ejecutar(Coche *coche) {
  testParar(coche);
  testArrancar(coche);
  testAcelerar(coche);
}

void TestCoche::testParar(Coche *coche) {
  Serial.print("\ttestParar\t");
  coche ->reaccionar(Orden::Parar);
  
  if (coche->getEstadoActual().getVelocidad() != 0)
    Serial.println("El coche no para");
  else
    Serial.println("OK");
}

void TestCoche::testArrancar(Coche *coche) {
  Serial.print("\ttestArrancar\t");
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

  coche ->pararMotores(); // partimos de un estado controlado
  coche ->reaccionar(Orden::Arrancar);
  int velocidadAnterior = coche->getEstadoActual().getVelocidad();
  coche ->reaccionar(Orden::Acelerar);

  if (coche->getEstadoActual().getVelocidad() <= velocidadAnterior)
    Serial.println("El coche no acelera");
  else
    Serial.println("OK");
}
