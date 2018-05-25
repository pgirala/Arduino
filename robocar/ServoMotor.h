/*
 * Servo.h - abstracción de un servo motor
 */

#ifndef ServoMotor_h
#define ServoMotor_h
 
#include "comun.h"

#include <Servo.h>

class ServoMotor {
  private:
    // Rotación del eje del motor
    SentidoRotacion _sentidoRotacion;
    int _angulo = 0;
    // Servo real
    Servo * _servoReal;
    void setAngulo(int angulo);
    void setSentidoRotacion(SentidoRotacion sentidoRotacion);
    SentidoRotacion getSentidoRotacion();
  public:
    ServoMotor();
    int getAngulo();
    void inicializar();
    void girar();

#ifdef LOG
    void print();
#endif
};

#endif
