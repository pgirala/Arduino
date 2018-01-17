/*
 * Motor.h - abstracción de un coche robótico
 */

#ifndef Motor_h
#define Motor_h
 
#include "Arduino.h"

//posiciones horizontales
#define IZQUIERDA 0
#define DERECHA 1

//posiciones verticales
#define DELANTE 0
#define DETRAS 1

class Motor {
  private:
    // giro
    int _velocidad = 0;
    int _ajuste = 0; // para calibrar diferencias en el comportamiento de los motores
    bool _reverso = false; // reverso implica movimiento hacia atrás
    // posicionamiento
    int _posicionHorizontal; // izquierda o derecha
    int _posicionVertical; // delante o detrás
  public:
    void setVelocidad(int velocidad);
    int getVelocidad();

    void setAjuste(int ajuste);
    int getAjuste();

    void setReverso(boolean reverso);
    boolean isReverso();

    boolean isDirecto();

    void setPosicionHorizontal(int posicionHorizontal);
    int getPosicionHorizontal();
    
    void setPosicionVertical(int posicionVertical);
    int getPosicionVertical();
};

#endif
