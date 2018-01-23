/*
 * ControlRemoto.cpp - abstracción de un control remoto actuando sobre un sensor de infrarrojos
 */
 
#include "ControlRemoto.h"

ControlRemoto::ControlRemoto(int pin) {
  _receptorIR = new IRrecv(pin);
  _receptorIR->enableIRIn(); // Start the IR receiver
}

Orden ControlRemoto::obtenerOrden() {
  Orden orden = Orden::Indefinida;
  decode_results resultados;
  
  if (_receptorIR->decode(&resultados))
  {  
    switch (resultados.value)
    {
      case KEY_PLUS:
        if (!_enPausa)
          orden = Orden::Acelerar;
        break;
      case KEY_MINUS:
        if (!_enPausa)
          orden = Orden::Frenar;
        break;
      case KEY_CHANNEL_PLUS:
        if (!_enPausa)
          orden = Orden::GirarDerecha;
        break;
      case KEY_CHANNEL_MINUS:
        if (!_enPausa)
          orden = Orden::GirarIzquierda;
        break;
      case KEY_PAUSE:
        if (_enPausa)
          orden = Orden::Arrancar;
        else
          orden = Orden::Parar;
        _enPausa = !_enPausa;
        break;
      case KEY_REPEAT:
        orden = Orden::Indefinida;
     };
    _receptorIR->resume(); // Recibe el siguiente valor
  }    
  return orden;
}

