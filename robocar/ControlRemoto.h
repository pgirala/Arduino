/*
 * ControlRemoto.h - abstracción de un control remoto actuando sobre un sensor de infrarrojos
 */

#ifndef ControlRemoto_h
#define ControlRemoto_h

#include <IRremote.h>

#include "Arduino.h"
#include "Coche.h"

// Teclas del control remoto por IR

#define KEY_PLUS 0xFFA857
#define KEY_MINUS 0xFFE01F
#define KEY_PAUSE 0xFFC23D
#define KEY_REPEAT 0xFFFFFFFF
#define KEY_FORWARD 0x2FD
#define KEY_BACKWARD 0x22DD
#define KEY_CHANNEL_PLUS 0xFFFFE21D
#define KEY_CHANNEL_MINUS 0xFFFFA25D


// teclas del control remoto

class ControlRemoto {
  private:
    IRrecv * _receptorIR;
    boolean _enPausa = false;
  public:
    ControlRemoto(int pin);
    void inicializar();
    Orden obtenerOrden();
};

#endif


