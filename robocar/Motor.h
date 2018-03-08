/*
 * Motor.h - abstracción de un coche robótico
 */

#ifndef Motor_h
#define Motor_h
 
#include "comun.h"

#include <AFMotor.h>

class Motor {
  private:
    // Rotación del eje del motor
    SentidoRotacion _sentidoRotacion;
    int _velocidad = 0;
    int _ajuste = 0; // para calibrar diferencias en el comportamiento de los motores
    // posicionamiento
    PosicionChasisHorizontal _posicionHorizontal; // izquierda o derecha
    PosicionChasisVertical _posicionVertical; // delante o detrás
    // motor real
    AF_DCMotor * _motorReal;

    // obtiene el sentido de rotación a partir de una dirección vertical de movimiento
    static SentidoRotacion obtenerSentidoRotacion(DireccionMovimientoHorizontal direccionHorizontal, DireccionMovimientoVertical direccionVertical, 
                                                  PosicionChasisHorizontal posicionHorizontal, PosicionChasisVertical posicionVertical);
    // obtiene el sentido real de rotación
    static SentidoRotacion obtenerSentidoRotacionDefecto(DireccionMovimientoVertical direccionVertical);
    static SentidoRotacion obtenerSentidoRotacionContrario(SentidoRotacion sentidoRotacion);
    static int obtenerSentidoRealRotacion(SentidoRotacion sentidoRotacion);
  public:
    Motor(int numero, PosicionChasisHorizontal posicionHorizontal, PosicionChasisVertical posicionVertical, int ajuste = 0);
  
    void setSentidoRotacion(SentidoRotacion sentidoRotacion);
    SentidoRotacion getSentidoRotacion();
    
    SentidoRotacion obtenerSentidoRotacion(DireccionMovimientoHorizontal direccionHorizontal, DireccionMovimientoVertical direccionVertical);

    void setVelocidad(int velocidad);
    int getVelocidad();

    void parar();

#ifdef LOG
    void print();
#endif

#ifdef TEST
    void reset();
#endif
};

#endif
