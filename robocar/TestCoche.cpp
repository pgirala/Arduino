#include "TestCoche.h"

#ifdef TEST

void TestCoche::ejecutar(Coche &coche, ControlRemoto &controlRemoto) {
/*  testParar(coche, controlRemoto);
  testArrancar(coche, controlRemoto);
  testAcelerar(coche, controlRemoto);
  testFrenar(coche, controlRemoto);
  testIrAdelante(coche, controlRemoto);
  testIrAtras(coche, controlRemoto); */
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
                                PosicionChasisHorizontal posicionesHorizontalesConObstaculo[],
                                DireccionMovimientoHorizontal direccionesEscapeValidas[]) {
  DireccionMovimientoHorizontal direccionEscape;

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
  for (int i = 0; i < sizeof(posicionesHorizontalesConObstaculo) / sizeof(*posicionesHorizontalesConObstaculo); i++) {
    Serial.print(" ");
    Serial.print(posicionesChasisHorizontal[static_cast<int>(posicionesHorizontalesConObstaculo[i])]);
  }
  Serial.println(" ");
#endif

  // establece los obstáculos

  coche.resetObstaculos();
  
  for (int i = 0; i < sizeof(posicionesHorizontalesConObstaculo) / sizeof(*posicionesHorizontalesConObstaculo); i++)
    establecerObstaculo(coche, posicionesHorizontalesConObstaculo[i], PosicionChasisVertical::Delante, DISTANCIA_SEGURIDAD - 1);
      
#ifdef LOG
  Serial.println("Se intenta detectar el obstáculo y decidir la nueva dirección...");
#endif
  coche.reaccionar(Orden::Indefinida); // detecta el obstáculo y prepara el cambio de dirección
#ifdef LOG
  Serial.println("Se hace efectivo el cambio de dirección...");
#endif
  coche.reaccionar(Orden::Indefinida); // lleva a cabo el cambio de dirección  
  direccionEscape = coche.getEstadoActual().getDireccionHorizontal();

  bool direccionEscapeEncontrada = false;

  for (int i = 0; i < sizeof(direccionesEscapeValidas); i++)
    direccionEscapeEncontrada = direccionEscapeEncontrada || (direccionEscape == direccionesEscapeValidas[i]);
    
  if (!direccionEscapeEncontrada) {
#ifdef LOG
    Serial.println("No se encuentra la direccion de escape esperada");
#endif
    return false;
  }

#ifdef LOG
  Serial.println("Desaparece el obstáculo...");
#endif

  coche.resetObstaculos();
  coche.reaccionar(Orden::Indefinida); // detecta el obstáculo y prepara el cambio de dirección
#ifdef LOG
  Serial.println("Se vuelve a la dirección original dirección...");
#endif
  coche.reaccionar(Orden::Indefinida); // detecta el obstáculo y prepara el cambio de dirección

  return coche.getEstadoActual().igual(estadoOriginal);
}

void TestCoche::testEvitarObstaculo(Coche &coche, ControlRemoto &controlRemoto){ // TODO refactoring, extraer un método con las pruebas
  Serial.print("\ttestEvitarObstaculo\t");
  
  PosicionChasisHorizontal posicionesHorizontalesConObstaculo[] = {PosicionChasisHorizontal::Izquierda};
  DireccionMovimientoHorizontal direccionesEscapeValidas[] = {DireccionMovimientoHorizontal::Recta, DireccionMovimientoHorizontal::Derecha};
  if (!evitarObstaculo(coche, controlRemoto, PosicionChasisVertical::Delante, posicionesHorizontalesConObstaculo,direccionesEscapeValidas))
    Serial.print("\t\tCon el obstáculo a la izquierda no se dirige al centro o a la derecha");
  
/*
#ifdef LOG
  Serial.println(""); Serial.println("Inicialización");
#endif

  iniciarMovimientoHaciaAdelante(coche, controlRemoto);
  estadoOriginal = coche.getEstadoActual();

#ifdef LOG
  Serial.println("Fin de la inicialización");
#endif
  
#ifdef LOG
  Serial.println("");
  Serial.println("Obstáculos a la izquierda y frente");
#endif

  // aparece un obstáculo a la izquierda y delante; el coche debería girar a la derecha

  if (!establecerObstaculo(coche, PosicionChasisHorizontal::Izquierda, PosicionChasisVertical::Delante, DISTANCIA_SEGURIDAD - 1) ||
      !establecerObstaculo(coche, PosicionChasisHorizontal::Centro, PosicionChasisVertical::Delante, DISTANCIA_SEGURIDAD - 1) ||
      !establecerObstaculo(coche, PosicionChasisHorizontal::Derecha, PosicionChasisVertical::Delante, DISTANCIA_SEGURIDAD + 1))
      return;
  
#ifdef LOG
  Serial.println("Se intenta detectar el obstáculo y decidir la nueva dirección...");
#endif
  coche.reaccionar(Orden::Indefinida); // detecta el obstáculo y prepara el cambio de dirección
#ifdef LOG
  Serial.println("Se hace efectivo el cambio de dirección...");
#endif
  coche.reaccionar(Orden::Indefinida); // lleva a cabo el cambio de dirección  
  direccionEscape = coche.getEstadoActual().getDireccionHorizontal();

  if (direccionEscape != DireccionMovimientoHorizontal::Derecha)
    Serial.println("Con el obstáculo a la izquierda y centro no se va a la derecha");

#ifdef LOG
  Serial.println("Desaparece el obstáculo...");
#endif

  establecerObstaculo(coche, PosicionChasisHorizontal::Izquierda, PosicionChasisVertical::Delante, DISTANCIA_SEGURIDAD + 1);
  establecerObstaculo(coche, PosicionChasisHorizontal::Centro, PosicionChasisVertical::Delante, DISTANCIA_SEGURIDAD + 1);
  coche.reaccionar(Orden::Indefinida); // detecta el obstáculo y prepara el cambio de dirección

  if (!coche.getEstadoActual().igual(estadoOriginal))
    Serial.println("No se recupera el estado original");

#ifdef LOG
  Serial.println(""); Serial.println("Inicialización");
#endif

  iniciarMovimientoHaciaAdelante(coche, controlRemoto);
  estadoOriginal = coche.getEstadoActual();

#ifdef LOG
  Serial.println("Fin de la inicialización");
#endif
  
#ifdef LOG
  Serial.println("");
  Serial.println("Obstáculo delante");
#endif

  // aparece un obstáculo delante; el coche debería girar a la izquierda o derecha

  if (!establecerObstaculo(coche, PosicionChasisHorizontal::Izquierda, PosicionChasisVertical::Delante, DISTANCIA_SEGURIDAD + 1) ||
      !establecerObstaculo(coche, PosicionChasisHorizontal::Centro, PosicionChasisVertical::Delante, DISTANCIA_SEGURIDAD - 1) ||
      !establecerObstaculo(coche, PosicionChasisHorizontal::Derecha, PosicionChasisVertical::Delante, DISTANCIA_SEGURIDAD + 1))
      return;

#ifdef LOG
  Serial.println("Se intenta detectar el obstáculo y decidir la nueva dirección...");
#endif
  coche.reaccionar(Orden::Indefinida); // detecta el obstáculo y prepara el cambio de dirección
#ifdef LOG
  Serial.println("Se hace efectivo el cambio de dirección...");
#endif
  coche.reaccionar(Orden::Indefinida); // lleva a cabo el cambio de dirección  
  direccionEscape = coche.getEstadoActual().getDireccionHorizontal();

  if (direccionEscape != DireccionMovimientoHorizontal::Izquierda and direccionEscape != DireccionMovimientoHorizontal::Derecha)
    Serial.println("Con el obstáculo en el centro no se va a la izquierda o a la derecha");

#ifdef LOG
  Serial.println("Desaparece el obstáculo...");
#endif

  establecerObstaculo(coche, PosicionChasisHorizontal::Centro, PosicionChasisVertical::Delante, DISTANCIA_SEGURIDAD + 1);
  coche.reaccionar(Orden::Indefinida); // detecta el obstáculo y prepara el cambio de dirección

  if (!coche.getEstadoActual().igual(estadoOriginal))
    Serial.println("No se recupera el estado original");

#ifdef LOG
  Serial.println(""); Serial.println("Inicialización");
#endif

  iniciarMovimientoHaciaAdelante(coche, controlRemoto);
  estadoOriginal = coche.getEstadoActual();

#ifdef LOG
  Serial.println("Fin de la inicialización");
#endif
  
#ifdef LOG
  Serial.println("");
  Serial.println("Obstáculo delante y a la derecha");
#endif

  // aparece un obstáculo a la derecha y delante; el coche debería girar a la izquierda

  if (!establecerObstaculo(coche, PosicionChasisHorizontal::Izquierda, PosicionChasisVertical::Delante, DISTANCIA_SEGURIDAD + 1) ||
      !establecerObstaculo(coche, PosicionChasisHorizontal::Centro, PosicionChasisVertical::Delante, DISTANCIA_SEGURIDAD - 1) ||
      !establecerObstaculo(coche, PosicionChasisHorizontal::Derecha, PosicionChasisVertical::Delante, DISTANCIA_SEGURIDAD - 1))
      return;
      
#ifdef LOG
  Serial.println("Se intenta detectar el obstáculo y decidir la nueva dirección...");
#endif
  coche.reaccionar(Orden::Indefinida); // detecta el obstáculo y prepara el cambio de dirección
#ifdef LOG
  Serial.println("Se hace efectivo el cambio de dirección...");
#endif
  coche.reaccionar(Orden::Indefinida); // lleva a cabo el cambio de dirección  
  direccionEscape = coche.getEstadoActual().getDireccionHorizontal();
  
  if (direccionEscape != DireccionMovimientoHorizontal::Izquierda)
    Serial.println("Con el obstáculo a la derecha y centro no se va a la izquierda");

#ifdef LOG
  Serial.println("Desaparece el obstáculo...");
#endif

  establecerObstaculo(coche, PosicionChasisHorizontal::Centro, PosicionChasisVertical::Delante, DISTANCIA_SEGURIDAD + 1);
  establecerObstaculo(coche, PosicionChasisHorizontal::Derecha, PosicionChasisVertical::Delante, DISTANCIA_SEGURIDAD + 1);
  coche.reaccionar(Orden::Indefinida); // detecta el obstáculo y prepara el cambio de dirección

  if (!coche.getEstadoActual().igual(estadoOriginal))
    Serial.println("No se recupera el estado original");

#ifdef LOG
  Serial.println(""); Serial.println("Inicialización");
#endif

  iniciarMovimientoHaciaAdelante(coche, controlRemoto);
  estadoOriginal = coche.getEstadoActual();

#ifdef LOG
  Serial.println("Fin de la inicialización");
#endif
  
#ifdef LOG
  Serial.println("");
  Serial.println("Obstáculo a la izquierda, delante y a la derecha");
#endif

  // aparece un obstáculo a la derecha, izquierda y delante; el coche debería parar TODO el coche debería buscar hacia atrás

  if (!establecerObstaculo(coche, PosicionChasisHorizontal::Izquierda, PosicionChasisVertical::Delante, DISTANCIA_SEGURIDAD - 1) ||
      !establecerObstaculo(coche, PosicionChasisHorizontal::Centro, PosicionChasisVertical::Delante, DISTANCIA_SEGURIDAD - 1) ||
      !establecerObstaculo(coche, PosicionChasisHorizontal::Derecha, PosicionChasisVertical::Delante, DISTANCIA_SEGURIDAD - 1))
      return;

#ifdef LOG
  Serial.println("Se intenta detectar el obstáculo y decidir la nueva dirección...");
#endif
  coche.reaccionar(Orden::Indefinida); // detecta el obstáculo y prepara el cambio de dirección
#ifdef LOG
  Serial.println("Se hace efectivo el cambio de dirección...");
#endif
  coche.reaccionar(Orden::Indefinida); // lleva a cabo el cambio de dirección
    
  if (coche.getEstadoActual().getVelocidad() > 0)
    Serial.print("El coche no para");
  else */ if (comprobarSincronizacionMotores(coche))
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
