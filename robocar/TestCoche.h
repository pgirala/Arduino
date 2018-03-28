#ifndef TestCoche_h
#define TestCoche_h
 
#include "comun.h"
#include "Coche.h"
#include "ControlRemoto.h"

class TestCoche {
  private:
    void testParar(Coche &coche, ControlRemoto &controlRemoto);
    void testArrancar(Coche &coche, ControlRemoto &controlRemoto);
    void testAcelerar(Coche &coche, ControlRemoto &controlRemoto);
    void testFrenar(Coche &coche, ControlRemoto &controlRemoto);
    void testIrAdelante(Coche &coche, ControlRemoto &controlRemoto);
    void testIrAtras(Coche &coche, ControlRemoto &controlRemoto);
    void testEvitarObstaculo(Coche &coche, ControlRemoto &controlRemoto);

    void inicializar(Coche &coche, ControlRemoto &controlRemoto);
    void iniciarMovimientoHaciaAdelante(Coche &coche, ControlRemoto &controlRemoto);
    bool comprobarSincronizacionMotores(Coche &coche);
    bool establecerObstaculo(Coche &coche, PosicionChasisHorizontal posicionChasisHorizontal, PosicionChasisVertical posicionChasisVertical, long distancia);
    bool evitarObstaculo(Coche &coche, ControlRemoto &controlRemoto, 
                                PosicionChasisVertical posicionVerticalConObstaculo, 
                                PosicionChasisHorizontal posicionesHorizontalesConObstaculo[], int numeroPosicionesHorizontalesConObstaculo,
                                DireccionMovimientoHorizontal direccionesEscapeValidas[], int numeroDireccionesEscapeValidas,
                                DireccionMovimientoVertical direccionEscapeValida);
  public:
    void ejecutar(Coche &coche, ControlRemoto &controlRemoto);
};

#endif
