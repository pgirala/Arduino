
/*
 * EstadoMarca.h - el estado de marcha del coche (real o solicitado)
 */

#ifndef EstadoMarcha_h
#define EstadoMarcha_h

#include "comun.h"

class EstadoMarcha {
  private:
    int _velocidad = 0;
    DireccionMovimientoHorizontal _direccionHorizontal = DireccionMovimientoHorizontal::Recta;
    DireccionMovimientoVertical _direccionVertical = DireccionMovimientoVertical::Adelante;
    int _velocidadPreviaParada = 0; // velocidad previa a la petición de una parada y a la que se reanuda la marcha
  public:
    EstadoMarcha();
    EstadoMarcha(int velocidad, DireccionMovimientoHorizontal direccionHorizontal, DireccionMovimientoVertical direccionVertical);
  
    void setVelocidad(int velocidad);
    int getVelocidad();

    void setDireccionHorizontal(DireccionMovimientoHorizontal direccionHorizontal);
    DireccionMovimientoHorizontal getDireccionHorizontal();

    void setDireccionVertical(DireccionMovimientoVertical direccionVertical);
    DireccionMovimientoVertical getDireccionVertical();

    DireccionMovimientoVertical getDireccionVerticalOpuesta();    

    void actualizar(Orden orden);

    bool igual(EstadoMarcha otroEstado);

    void copiar(EstadoMarcha otroEstado);

#ifdef LOG
    void print();
#endif

#ifdef TEST
    void reset();
#endif
};

#endif
