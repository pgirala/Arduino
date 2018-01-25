/*
 * EstadoMarca.h - el estado de marcha del coche (real o solicitado)
 */

#ifndef EstadoMarcha_h
#define EstadoMarcha_h

// movimiento

#define INCREMENTO_VELOCIDAD 10
#define VELOCIDAD_MINIMA 0
#define VELOCIDAD_MAXIMA 200

// Ordenes que afectan al estado de la marcha

enum class Orden {Indefinida, Parar, Arrancar, IrAdelante, IrAtras, GirarIzquierda, GirarDerecha, Acelerar, Frenar};

enum class DireccionMovimientoHorizontal {Nula, Izquierda, Derecha};
enum class DireccionMovimientoVertical {Adelante, Atras};

class EstadoMarcha {
  private:
    int _velocidad = 0;
    DireccionMovimientoHorizontal _direccionHorizontal = DireccionMovimientoHorizontal::Nula;
    DireccionMovimientoVertical _direccionVertical = DireccionMovimientoVertical::Adelante;
  public:
    void setVelocidad(int velocidad);
    int getVelocidad();

    void setDireccionHorizontal(DireccionMovimientoHorizontal direccionHorizontal);
    DireccionMovimientoHorizontal getDireccionHorizontal();

    void setDireccionVertical(DireccionMovimientoVertical direccionVertical);
    DireccionMovimientoVertical getDireccionVertical();

    void actualizar(Orden orden);

    bool igual(EstadoMarcha otroEstado);
};

#endif
