/*
 * EstadoMarca.h - el estado de marcha del coche (real o solicitado)
 */

#ifndef EstadoMarcha_h
#define EstadoMarcha_h

#include "Arduino.h"

// movimiento

#define INCREMENTO_VELOCIDAD 25
#define VELOCIDAD_MAXIMA 200

// Ordenes que afectan al estado de la marcha

enum class Orden {Indefinida, Parar, Arrancar, IrAdelante, IrAtras, Recto, GirarIzquierda, GirarDerecha, Acelerar, Frenar};

enum class DireccionMovimientoHorizontal {Recta, Izquierda, Derecha};
enum class DireccionMovimientoVertical {Adelante, Atras};

class EstadoMarcha {
  private:
    int _velocidad = 0;
    DireccionMovimientoHorizontal _direccionHorizontal = DireccionMovimientoHorizontal::Recta;
    DireccionMovimientoVertical _direccionVertical = DireccionMovimientoVertical::Adelante;
    int _velocidadPreviaParada = 0; // velocidad previa a la petición de una parada y a la que se reanuda la marcha
  public:
    void setVelocidad(int velocidad);
    int getVelocidad();

    void setDireccionHorizontal(DireccionMovimientoHorizontal direccionHorizontal);
    DireccionMovimientoHorizontal getDireccionHorizontal();

    void setDireccionVertical(DireccionMovimientoVertical direccionVertical);
    DireccionMovimientoVertical getDireccionVertical();

    void actualizar(Orden orden);

    bool igual(EstadoMarcha otroEstado);

    void copiar(EstadoMarcha otroEstado);

    void print();
};

#endif
