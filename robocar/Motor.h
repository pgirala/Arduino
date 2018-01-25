/*
 * Motor.h - abstracción de un coche robótico
 */

#ifndef Motor_h
#define Motor_h
 
#include "Arduino.h"
#include <AFMotor.h>

#include "EstadoMarcha.h"

enum class PosicionChasisHorizontal {Indiferente, Izquierda, Derecha};
enum class PosicionChasisVertical {Indiferente, Delante, Detras};
enum class SentidoRotacion {Directo, Reverso};

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
  public:
    Motor(int numero, PosicionChasisHorizontal posicionHorizontal, PosicionChasisVertical posicionVertical, int ajuste = 0);
  
    void setSentidoRotacion(SentidoRotacion sentidoRotacion);
    SentidoRotacion getSentidoRotacion();
    
    // obtiene el sentido de rotación a partir de una dirección vertical de movimiento
    static SentidoRotacion obtenerSentidoRotacion(DireccionMovimientoVertical direccionVertical);

    // obtiene el sentido real de rotación
    static int obtenerSentidoRealRotacion(SentidoRotacion sentidoRotacion);

    void setVelocidad(int velocidad);
    int getVelocidad();

    boolean isColocado(PosicionChasisHorizontal posicionHorizontal, PosicionChasisVertical posicionVertical);

    void parar();
};

#endif
