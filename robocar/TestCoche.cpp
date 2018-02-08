#include "TestCoche.h"

void TestCoche::ejecutar(Coche &coche, ControlRemoto &controlRemoto) {
  testParar(coche, controlRemoto);
  testArrancar(coche, controlRemoto);
  testAcelerar(coche, controlRemoto);
}

void TestCoche::testParar(Coche &coche, ControlRemoto &controlRemoto) {
  Serial.print("\ttestParar\t");
  inicializar(coche, controlRemoto);
  
  EstadoMarcha estadoInicial = coche.getEstadoActual();
  
  coche.reaccionar(Orden::Acelerar);

  if (coche.getEstadoActual().getVelocidad() == 0) {
    Serial.println("El coche no acelera");
    return;
  }
  
  coche.reaccionar(Orden::Parar);
  
  if (!coche.getEstadoActual().igual(estadoInicial))
    Serial.println("El coche no para");
  else if (comprobarSincronizacionMotores(coche))
    Serial.println("OK");
}

void TestCoche::testArrancar(Coche &coche, ControlRemoto &controlRemoto) {
  Serial.print("\ttestArrancar\t");
  iniciarMovimientoHaciaAdelante(coche, controlRemoto);
  EstadoMarcha estadoInicial = coche.getEstadoActual();
  
  coche.reaccionar(Orden::Parar);
  coche.reaccionar(Orden::Arrancar);
  
  if (!coche.getEstadoActual().igual(estadoInicial))
    Serial.println("El coche no arranca bien");
  else if (comprobarSincronizacionMotores(coche))
    Serial.println("OK");
}

void TestCoche::testAcelerar(Coche &coche, ControlRemoto &controlRemoto) {
  Serial.print("\ttestAcelerar\t");
  inicializar(coche, controlRemoto);
  
  coche.reaccionar(Orden::Acelerar);
  
  int velocidadAnterior = coche.getEstadoActual().getVelocidad();

  coche.reaccionar(Orden::Acelerar);

  if (coche.getEstadoActual().getVelocidad() > velocidadAnterior)
    Serial.println("OK");
  else if (comprobarSincronizacionMotores(coche))
    Serial.println("El coche no acelera");
}

void TestCoche::inicializar(Coche &coche, ControlRemoto &controlRemoto) {
  coche.reset();
  controlRemoto.reset();
}

void TestCoche::iniciarMovimientoHaciaAdelante(Coche &coche, ControlRemoto &controlRemoto) {
  inicializar(coche, controlRemoto);
  coche.reaccionar(Orden::Acelerar);  
  if (coche.getEstadoActual().getVelocidad() == 0) {
    Serial.println("El coche no acelera");
    return;
  }
}

boolean TestCoche::comprobarSincronizacionMotores(Coche &coche) {
  int numeroMotor = coche.comprobarSincronizacionMotores();

  if (numeroMotor > 0) {
    Serial.print("El motor "); Serial.print(numeroMotor); Serial.println(" no está bien sincronizado");
    return false;
  }

  return true;
}


