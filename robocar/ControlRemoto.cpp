/*
 * ControlRemoto.cpp - abstracción de un control remoto actuando sobre un sensor de infrarrojos
 */
 
#include "ControlRemoto.h"

ControlRemoto::ControlRemoto(int pin) {
  _receptorIR = new IRrecv(pin);
  _receptorIR->enableIRIn(); // Start the IR receiver
}

