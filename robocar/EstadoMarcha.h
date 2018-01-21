/*
 * EstadoMarca.h - el estado de marcha del coche (real o solicitado)
 */

#ifndef EstadoMarcha_h
#define EstadoMarcha_h

class EstadoMarcha {
  private:
    int _velocidad;
    int _direccionHorizontal;
    int _direccionVertical;
  public:
    void setVelocidad(int velocidad);
    int getVelocidad();

    void setDireccionHorizontal(int direccionHorizontal);
    int getDireccionHorizontal();

    void setDireccionVertical(int direccionVertical);
    int getDireccionVertical();
};

#endif
