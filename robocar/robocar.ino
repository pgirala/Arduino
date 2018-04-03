#include "comun.h"

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

  controlRemoto.inicializar();
  coche.inicializar();
  
  // manejo de interrupciones asociadas a los sensores de movimiento
  attachInterrupt( digitalPinToInterrupt(D21), actualizarContadorSMTI, RISING);
  attachInterrupt( digitalPinToInterrupt(D20), actualizarContadorSMTD, RISING);
  attachInterrupt( digitalPinToInterrupt(D19), actualizarContadorSMDD, RISING);
  attachInterrupt( digitalPinToInterrupt(D18), actualizarContadorSMDI, RISING);
  
  Serial.begin(9600);  

  while (! Serial);
  
  Serial.println("D (aDelante) T (aTrás) + (acelerar) - (frenar) I (Izquierda) R (deRecha) E (rEcto) P (Pausa /continuar) F (indeFinida) ");
}

void loop()
{
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
  coche.getSensorMovimiento(PosicionChasisHorizontal::Izquierda, PosicionChasisVertical::Detras)->incrementarContador();
}

void actualizarContadorSMTD() {
  coche.getSensorMovimiento(PosicionChasisHorizontal::Derecha, PosicionChasisVertical::Detras)->incrementarContador();
}

void actualizarContadorSMDD() {
  coche.getSensorMovimiento(PosicionChasisHorizontal::Derecha, PosicionChasisVertical::Delante)->incrementarContador();
}

void actualizarContadorSMDI() {
  coche.getSensorMovimiento(PosicionChasisHorizontal::Izquierda, PosicionChasisVertical::Delante)->incrementarContador();
}

