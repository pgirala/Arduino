/*
 * ControlRemoto.h - abstracción de un control remoto actuando sobre un sensor de infrarrojos
 */

#ifndef ControlRemoto_h
#define ControlRemoto_h

#include "comun.h"

#include <IRremote.h>

// Teclas del control remoto por IR

#define KEY_PLUS 0xFFA857
#define KEY_MINUS 0xFFE01F
#define KEY_PAUSE 0xFFC23D
#define KEY_REPEAT 0xFFFFFFFF
#define KEY_FORWARD 0x2FD
#define KEY_BACKWARD 0x22DD
#define KEY_CHANNEL_PLUS 0xFFFFE21D
#define KEY_CHANNEL_MINUS 0xFFFFA25D
#define KEY_CHANNEL 0x629D

class ControlRemoto {
  private:
    IRrecv * _receptorIR;
    boolean _enPausa = false;
    #ifdef TEST
      long int _key = KEY_REPEAT;
    #endif
  public:
    ControlRemoto(int pin);
    void inicializar();
    boolean preparado();
    Orden obtenerOrden(int key);
    Orden obtenerOrden();
#ifdef TEST
    void reset();
    bool setKey(long int key);
#endif
};

#endif


