/*
 * ControlRemoto.h - abstracción de un control remoto actuando sobre un sensor de infrarrojos
 */

#ifndef ControlRemoto_h
#define ControlRemoto_h

#include <IRremote.h>

#include "Arduino.h"

// Teclas del control remoto por IR

#define KEY_PLUS 0xFFA857
#define KEY_MINUS 0xFFE01F
#define KEY_PAUSE 0xFFC23D
#define KEY_REPEAT 0xFFFFFFFF

// teclas del control remoto

class ControlRemoto {
  private:
    IRrecv * _receptorIR;
  public:
    ControlRemoto(int pin);
};

#endif


