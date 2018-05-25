#include "comun.h"

// tratamiento de interrupciones
// habilitación de interrupciones diferentes a las de por defecto
#define EI_NOTINT0
#define EI_NOTINT1
#define EI_NOTINT2
#define EI_NOTINT3
#define EI_NOTINT4
#define EI_NOTINT5
#define EI_NOTINT6
#define EI_NOTINT7
#include "EnableInterrupt.h"

// tratamiento de threads
#include <Thread.h>
#include <ThreadController.h>
ThreadController controladorHilos = ThreadController();
Thread hiloGiroUnidadDeteccionObstaculos = Thread();

// servo de la unidad de detección de obstáculos

#include "ServoMotor.h"

ServoMotor servoMotor;

// coche

#include "Coche.h"
#include "ControlRemoto.h"

Coche coche;
ControlRemoto controlRemoto(CR_PIN);

//-------------------------------------------------------------------------------------------------------------------------------------
#ifdef TEST

#include "TestCoche.h"

TestCoche testCoche;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);    // desactiva el led de prueba que, en caso contrario, quedaría encendido
  
  Serial.begin(9600);  

  while (! Serial);
  
  Serial.println("-----COMIENZO DE LAS PRUEBAS-----");
  testCoche.ejecutar(coche, controlRemoto);
  Serial.println("-------FINAL DE LAS PRUEBAS------");
}

void loop() {
}

#else

//-------------------------------------------------------------------------------------------------------------------------------------

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);    // desactiva el led de prueba que, en caso contrario, quedaría encendido

  Serial.begin(9600);  

  while (! Serial);

  // manejo de interrupciones asociadas a los sensores de movimiento; se usan los pines A14 y A15 para no interferir con el protocolo usado por el sensor LIDAR que usa el 20 y 21
  enableInterrupt(SM_PIN_TRASERO_I, actualizarContadorSMTI, RISING);
  enableInterrupt(SM_PIN_TRASERO_D, actualizarContadorSMTD, RISING);
  attachInterrupt(digitalPinToInterrupt(SM_PIN_DELANTERO_D), actualizarContadorSMDD, RISING);
  attachInterrupt(digitalPinToInterrupt(SM_PIN_DELANTERO_I), actualizarContadorSMDI, RISING);

  controlRemoto.inicializar();
  servoMotor.inicializar();
  coche.inicializar();
  
  // configurar hilo de detección de obstaculos
  hiloGiroUnidadDeteccionObstaculos.onRun(girarUnidadDeteccionObstaculos);
  hiloGiroUnidadDeteccionObstaculos.setInterval(150);
  controladorHilos.add(&hiloGiroUnidadDeteccionObstaculos);
  
  // chequeo final
  chequear();

  Serial.println("D (aDelante) T (aTrás) + (acelerar) - (frenar) I (Izquierda) R (deRecha) E (rEcto) P (Pausa /continuar) F (indeFinida) ");
}

void chequear() {
#ifdef LOG
  Serial.println(">>> Chequeo...");
#endif
  // chequeo básico
  if (!coche.preparado() || !controlRemoto.preparado()) {
#ifdef LOG
    Serial.println(">>> Chequeo fallido.");
#endif
    while (true) {
      digitalWrite(LED_BUILTIN, HIGH); // hay un problema, el led se queda parpadeando
      delay(1000);
      digitalWrite(LED_BUILTIN, LOW);
      delay(500);
    }
  }  
#ifdef LOG
    Serial.println(">>> Chequeo OK.");
#endif
}

void loop()
{
  controladorHilos.run();
  coche.reaccionar(recibirOrden());
}

#endif

Orden recibirOrden() {
  // órdenes procedentes del puerto serie
  Orden resultado = obtenerOrdenPuertoSerie(); // para pruebas

  if (resultado == Orden::Indefinida)
    resultado = controlRemoto.obtenerOrden();

  return resultado;
}

Orden obtenerOrdenPuertoSerie() {
  static bool enPausa = false;
  
  if (Serial.available()) // se ha suministrado una nueva velocidad
  {
    char valorDevuelto = toupper(Serial.read());

    switch (valorDevuelto)
    {
    case 'D':
      return Orden::IrAdelante;
    case 'T':
      return Orden::IrAtras;
    case '+':
      return Orden::Acelerar;
    case '-':
      return Orden::Frenar;
    case 'R':
      return Orden::GirarDerecha;
    case 'I':
      return Orden::GirarIzquierda;
    case 'E':
      return Orden::Recto;
    case 'P':
      if (enPausa) {
        enPausa = false;
        return Orden::Arrancar;
      } else {
        enPausa = true;
        return Orden::Parar;
      };
     case 'F':
      return Orden::Indefinida;
    };    
  }
  return Orden::Indefinida; 
}

// manejadores de interrupciones

void actualizarContadorSMTI() {
  coche.getSistemaNavegacion()->getUnidadMedicion()->getSensorMovimiento(PosicionChasisHorizontal::Izquierda, PosicionChasisVertical::Detras)->incrementarContador();
}

void actualizarContadorSMTD() {
  coche.getSistemaNavegacion()->getUnidadMedicion()->getSensorMovimiento(PosicionChasisHorizontal::Derecha, PosicionChasisVertical::Detras)->incrementarContador();
}

void actualizarContadorSMDD() {
  coche.getSistemaNavegacion()->getUnidadMedicion()->getSensorMovimiento(PosicionChasisHorizontal::Derecha, PosicionChasisVertical::Delante)->incrementarContador();
}

void actualizarContadorSMDI() {
  coche.getSistemaNavegacion()->getUnidadMedicion()->getSensorMovimiento(PosicionChasisHorizontal::Izquierda, PosicionChasisVertical::Delante)->incrementarContador();
}

// manejadores de eventos asociados a hilos
void girarUnidadDeteccionObstaculos() {
  servoMotor.girar();
}

