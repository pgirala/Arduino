/*
 * UnidadMedicion.h - abstracción de una unidad de medición inercial (IMU)
 */

#ifndef UnidadMedicion_h
#define UnidadMedicion_h

#include "comun.h"
#include "SensorMovimiento.h"

class UnidadMedicion {
  private:
    SensorMovimiento _sensoresMovimiento[NUMERO_SENSORES_MOVIMIENTO] = {SensorMovimiento(PosicionChasisHorizontal::Izquierda, PosicionChasisVertical::Delante, SM_PIN_DELANTERO_I),
                                                                        SensorMovimiento(PosicionChasisHorizontal::Derecha, PosicionChasisVertical::Delante, SM_PIN_DELANTERO_D),
                                                                        SensorMovimiento(PosicionChasisHorizontal::Izquierda, PosicionChasisVertical::Detras, SM_PIN_TRASERO_I),
                                                                        SensorMovimiento(PosicionChasisHorizontal::Derecha, PosicionChasisVertical::Detras, SM_PIN_TRASERO_D)};
    void iniciarCuenta(int indice);
    void pararCuenta(int indice);
    long getCuentaMedia(int indice);
    long getCuentaMedia(int indice, PosicionChasisHorizontal posicionChasisHorizontal);
    double calcularDistancia(long s);
    double calcularAngulo(long s1, long s2);
 public:
    void inicializar();
    boolean preparada();
    void reset(); // inicializa el contador principal

    SensorMovimiento * getSensorMovimiento(PosicionChasisHorizontal posicionChasisHorizontal, PosicionChasisVertical posicionChasisVertical);
    
    void iniciarComputoRecorrido(); // inicializa el cálculo de distancia y ángulos recorridos
    double getDistancia(); // distancia recorrida desde el último reset
    double getAngulo(); // ángulo recorrido desde el último reset
    
    void iniciarCuentaSincronizacion();
    void pararCuentaSincronizacion();
    long getCuentaSincronizacion(PosicionChasisHorizontal posicionChasisHorizontal, PosicionChasisVertical posicionChasisVertical);
    long getCuentaMediaSincronizacion();
#ifdef LOG
    void print();
#endif
};

#endif


