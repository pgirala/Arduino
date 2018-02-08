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

    void inicializar(Coche &coche, ControlRemoto &controlRemoto);
    void iniciarMovimientoHaciaAdelante(Coche &coche, ControlRemoto &controlRemoto);
    bool comprobarSincronizacionMotores(Coche &coche);
  public:
    void ejecutar(Coche &coche, ControlRemoto &controlRemoto);
};

#endif
