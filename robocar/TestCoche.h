#ifndef TestCoche_h
#define TestCoche_h
 
#include "comun.h"
#include "Coche.h"

class TestCoche {
  private:
    void testParar(Coche *coche);
    void testArrancar(Coche *coche);
    void testAcelerar(Coche *coche);
  public:
    void ejecutar(Coche *coche);
};

#endif
