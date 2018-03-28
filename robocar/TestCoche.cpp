#include "TestCoche.h"

#ifdef TEST

void TestCoche::ejecutar(Coche &coche, ControlRemoto &controlRemoto) {
  testParar(coche, controlRemoto);
  testArrancar(coche, controlRemoto);
  testAcelerar(coche, controlRemoto);
  testFrenar(coche, controlRemoto);
  testIrAdelante(coche, controlRemoto);
  testIrAtras(coche, controlRemoto); 
  testEvitarObstaculo(coche, controlRemoto);
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

  iniciarMovimientoHaciaAdelante(coche, controlRemoto);
  
  int velocidadAnterior = coche.getEstadoActual().getVelocidad();

  coche.reaccionar(Orden::Acelerar);

  if (coche.getEstadoActual().getVelocidad() <= velocidadAnterior)
    Serial.println("El coche no acelera");
  else if (comprobarSincronizacionMotores(coche))
    Serial.println("OK");
}

void TestCoche::testFrenar(Coche &coche, ControlRemoto &controlRemoto) {
  Serial.print("\ttestFrenar\t");

  iniciarMovimientoHaciaAdelante(coche, controlRemoto);
  coche.reaccionar(Orden::Acelerar);
  
  int velocidadAnterior = coche.getEstadoActual().getVelocidad();

  coche.reaccionar(Orden::Frenar);

  if (coche.getEstadoActual().getVelocidad() >= velocidadAnterior)
    Serial.println("El coche no acelera");
  else if (comprobarSincronizacionMotores(coche))
    Serial.println("OK");
}

void TestCoche::testIrAdelante(Coche &coche, ControlRemoto &controlRemoto) {
  Serial.print("\ttestIrAdelante\t");

  iniciarMovimientoHaciaAdelante(coche, controlRemoto);
  coche.reaccionar(Orden::GirarDerecha);

  if (coche.getEstadoActual().getDireccionVertical() != DireccionMovimientoVertical::Adelante)
    Serial.println("El coche ha cambiado de sentido de marcha");
  else if (coche.getEstadoActual().getDireccionHorizontal() != DireccionMovimientoHorizontal::Derecha)
    Serial.println("El coche no gira a la derecha");
  else 
    comprobarSincronizacionMotores(coche);

  coche.reaccionar(Orden::GirarIzquierda);

  if (coche.getEstadoActual().getDireccionVertical() != DireccionMovimientoVertical::Adelante)
    Serial.println("El coche ha cambiado de sentido de marcha");
  else if (coche.getEstadoActual().getDireccionHorizontal() != DireccionMovimientoHorizontal::Izquierda)
    Serial.println("El coche no gira a la izquierda");
  else 
    comprobarSincronizacionMotores(coche);
    
  coche.reaccionar(Orden::Recto);

  if (coche.getEstadoActual().getDireccionVertical() != DireccionMovimientoVertical::Adelante)
    Serial.println("El coche ha cambiado de sentido de marcha");
  else if (coche.getEstadoActual().getDireccionHorizontal() != DireccionMovimientoHorizontal::Recta)
    Serial.println("El coche no se endereza");
  else if (comprobarSincronizacionMotores(coche))
    Serial.println("OK");
}

void TestCoche::testIrAtras(Coche &coche, ControlRemoto &controlRemoto) {
  Serial.print("\ttestIrAtras\t");

  iniciarMovimientoHaciaAdelante(coche, controlRemoto);

  int velocidadAnterior = coche.getEstadoActual().getVelocidad();
  
  coche.reaccionar(Orden::IrAtras);

  if (coche.getEstadoActual().getDireccionVertical() != DireccionMovimientoVertical::Atras)
    Serial.println("El coche no ha cambiado de sentido de marcha");
  else if (coche.getEstadoActual().getVelocidad() != velocidadAnterior)
    Serial.println("El coche no mantiene la velocidad");
  else if (coche.getEstadoActual().getDireccionHorizontal() != DireccionMovimientoHorizontal::Recta)
    Serial.println("El coche no se mantiene recto");
  else 
    comprobarSincronizacionMotores(coche);

  coche.reaccionar(Orden::GirarIzquierda);

  if (coche.getEstadoActual().getDireccionVertical() != DireccionMovimientoVertical::Atras)
    Serial.println("El coche ha cambiado de sentido de marcha");
  else if (coche.getEstadoActual().getDireccionHorizontal() != DireccionMovimientoHorizontal::Izquierda)
    Serial.println("El coche no gira a la izquierda");
  else 
    comprobarSincronizacionMotores(coche);
    
  coche.reaccionar(Orden::Recto);

  if (coche.getEstadoActual().getDireccionVertical() != DireccionMovimientoVertical::Atras)
    Serial.println("El coche ha cambiado de sentido de marcha");
  else if (coche.getEstadoActual().getDireccionHorizontal() != DireccionMovimientoHorizontal::Recta)
    Serial.println("El coche no se endereza");
  else if (comprobarSincronizacionMotores(coche))
    Serial.println("OK");
}

bool TestCoche::evitarObstaculo(Coche &coche, ControlRemoto &controlRemoto, 
                                PosicionChasisVertical posicionVerticalConObstaculo, 
                                PosicionChasisHorizontal posicionesHorizontalesConObstaculo[], int numeroPosicionesHorizontalesConObstaculo,
                                DireccionMovimientoHorizontal direccionesEscapeValidas[], int numeroDireccionesEscapeValidas,
                                DireccionMovimientoVertical direccionEscapeValida) {
  DireccionMovimientoHorizontal direccionEscapeHorizontal;

#ifdef LOG
  Serial.println(""); Serial.println("Inicialización");
#endif

  iniciarMovimientoHaciaAdelante(coche, controlRemoto);
  EstadoMarcha estadoOriginal = coche.getEstadoActual();
  
#ifdef LOG
  Serial.println("Fin de la inicialización");
#endif

#ifdef LOG
  Serial.println("");
  Serial.print("Obstáculos: ");
  for (int i = 0; i < numeroPosicionesHorizontalesConObstaculo; i++) {
    Serial.print(" ");
    Serial.print(posicionesChasisHorizontal[static_cast<int>(posicionesHorizontalesConObstaculo[i])]);
  }
  Serial.println(" ");
#endif

  // establece los obstáculos

  coche.resetObstaculos();
  
  for (int i = 0; i < numeroPosicionesHorizontalesConObstaculo; i++)
    establecerObstaculo(coche, posicionesHorizontalesConObstaculo[i], PosicionChasisVertical::Delante, DISTANCIA_SEGURIDAD - 1);

#ifdef LOG
  Serial.println("Se intenta detectar el obstáculo y decidir la nueva dirección...");
#endif
  coche.reaccionar(Orden::Indefinida); // detecta el obstáculo y prepara el cambio de dirección
#ifdef LOG
  Serial.println("Se hace efectivo el cambio de dirección...");
#endif
  coche.reaccionar(Orden::Indefinida); // lleva a cabo el cambio de dirección  

  if (direccionEscapeValida != coche.getEstadoActual().getDireccionVertical()) {
#ifdef LOG
    Serial.println("No se encuentra la direccion de escape vertical esperada");
#endif
    return false;
  }

  direccionEscapeHorizontal = coche.getEstadoActual().getDireccionHorizontal();

  bool direccionEscapeEncontrada = false;

  for (int i = 0; i < numeroDireccionesEscapeValidas; i++)
    direccionEscapeEncontrada = direccionEscapeEncontrada || (direccionEscapeHorizontal == direccionesEscapeValidas[i]);
    
  if (!direccionEscapeEncontrada) {
#ifdef LOG
    Serial.println("No se encuentra la direccion de escape horizontal esperada");
#endif
    return false;
  }

#ifdef LOG
  Serial.println("Desaparece el obstáculo...");
#endif

  coche.resetObstaculos();
  coche.reaccionar(Orden::Indefinida); // detecta el obstáculo y prepara el cambio de dirección
#ifdef LOG
  Serial.println("Se vuelve a la dirección original...");
#endif
  coche.reaccionar(Orden::Indefinida); // detecta el obstáculo y prepara el cambio de dirección

  if (numeroPosicionesHorizontalesConObstaculo == coche.getNumeroSensoresUltraSonidos(posicionVerticalConObstaculo)) // había un bloqueo total
    estadoOriginal.setDireccionHorizontal(coche.getEstadoActual().getDireccionHorizontal());
    
  return coche.getEstadoActual().igual(estadoOriginal);
}

void TestCoche::testEvitarObstaculo(Coche &coche, ControlRemoto &controlRemoto){
  Serial.print("\ttestEvitarObstaculo\t");
  
  PosicionChasisHorizontal* posicionesHorizontalesConObstaculo;
  DireccionMovimientoHorizontal* direccionesEscapeValidas;
  
  posicionesHorizontalesConObstaculo = new PosicionChasisHorizontal[1] {PosicionChasisHorizontal::Izquierda};
  direccionesEscapeValidas= new DireccionMovimientoHorizontal[2] {DireccionMovimientoHorizontal::Recta, DireccionMovimientoHorizontal::Derecha};
  
  if (!evitarObstaculo(coche, controlRemoto, PosicionChasisVertical::Delante, posicionesHorizontalesConObstaculo, 1, direccionesEscapeValidas, 2, DireccionMovimientoVertical::Adelante)) {
    Serial.println("\t\tCon el obstáculo a la izquierda no se dirige al centro o a la derecha");
    return;
  }

  posicionesHorizontalesConObstaculo = new PosicionChasisHorizontal[2] {PosicionChasisHorizontal::Izquierda, PosicionChasisHorizontal::Centro};
  direccionesEscapeValidas = new DireccionMovimientoHorizontal[1] {DireccionMovimientoHorizontal::Derecha};
  if (!evitarObstaculo(coche, controlRemoto, PosicionChasisVertical::Delante, posicionesHorizontalesConObstaculo, 2, direccionesEscapeValidas, 1, DireccionMovimientoVertical::Adelante)) {
    Serial.println("\t\tCon el obstáculo a la izquierda y en el centro no se dirige a la derecha");
    return;
  }
  
  posicionesHorizontalesConObstaculo = new PosicionChasisHorizontal[1] {PosicionChasisHorizontal::Derecha};
  direccionesEscapeValidas = new DireccionMovimientoHorizontal[2] {DireccionMovimientoHorizontal::Izquierda, DireccionMovimientoHorizontal::Recta, };
  if (!evitarObstaculo(coche, controlRemoto, PosicionChasisVertical::Delante, posicionesHorizontalesConObstaculo, 1, direccionesEscapeValidas, 2, DireccionMovimientoVertical::Adelante)) {
    Serial.println("\t\tCon el obstáculo a la derecha no se dirige al centro o la izquierda");
    return;
  }

  posicionesHorizontalesConObstaculo = new PosicionChasisHorizontal[2] {PosicionChasisHorizontal::Derecha, PosicionChasisHorizontal::Centro};
  direccionesEscapeValidas = new DireccionMovimientoHorizontal[1] {DireccionMovimientoHorizontal::Izquierda};
  if (!evitarObstaculo(coche, controlRemoto, PosicionChasisVertical::Delante, posicionesHorizontalesConObstaculo, 2, direccionesEscapeValidas, 1,DireccionMovimientoVertical::Adelante)) {
    Serial.println("\t\tCon el obstáculo a la derecha y en el centro no se dirige a la izquierda");
    return;
  }

  posicionesHorizontalesConObstaculo = new PosicionChasisHorizontal[3] {PosicionChasisHorizontal::Izquierda, PosicionChasisHorizontal::Derecha, PosicionChasisHorizontal::Centro};
  direccionesEscapeValidas = new DireccionMovimientoHorizontal[1] {DireccionMovimientoHorizontal::Recta};
  if (!evitarObstaculo(coche, controlRemoto, PosicionChasisVertical::Delante, posicionesHorizontalesConObstaculo, 3, direccionesEscapeValidas, 1, DireccionMovimientoVertical::Atras)) {
    Serial.println("\t\tCon todo obstaculizado por delante no se dirige a izquierda o derecha tras ir un trecho hacia atrás");
    return;
  }

  if (comprobarSincronizacionMotores(coche))
    Serial.println("OK");

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

bool TestCoche::establecerObstaculo(Coche &coche, PosicionChasisHorizontal posicionChasisHorizontal, PosicionChasisVertical posicionChasisVertical, long distancia) {
 SensorUltraSonidos * sensorUS = coche.getSensorUltraSonidos(posicionChasisHorizontal, posicionChasisVertical);

  if (sensorUS == NULL) {
    Serial.println("No se encuentra el sensor delantero izquierdo");
    return false;
  }

  sensorUS->setDistanciaObstaculo(distancia);
  return true;
 }

#endif
