#include "Coche.h"
#include "ControlRemoto.h"

// coche
Coche coche;

// control remoto
#define CR_PIN 31

ControlRemoto controlRemoto(CR_PIN);

//-------------------------------------------------------------------------------------------------------------------------------------

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);    // desactiva el led de prueba que, en caso contrario, quedaría encendido

  controlRemoto.inicializar();
  coche.inicializar();
  
  Serial.begin(9600);  

  while (! Serial);
  
  Serial.println("D (aDelante) T (aTrás) + (acelerar) - (frenar) I (Izquierda) R (deRecha) E (rEcto) P (Pausa /continuar) F (indeFinida) ");
}

void loop()
{
  coche.reaccionar(recibirOrden());
}

Orden recibirOrden() {
  // órdenes procedentes del puerto serie
  Orden resultado = obtenerOrdenPuertoSerie(); // para pruebas

  if (resultado == Orden::Indefinida)
    resultado = controlRemoto.obtenerOrden();

//  if (resultado != Orden::Indefinida)    // TEST
//    Serial.println(static_cast<int>(resultado));
  
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
