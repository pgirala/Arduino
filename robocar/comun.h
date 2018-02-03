#ifndef comun_h
#define comun_h
 
#include "Arduino.h"

#include "properties.h"

// Ordenes que afectan al estado de la marcha

enum class Orden {Indefinida, Parar, Arrancar, IrAdelante, IrAtras, Recto, GirarIzquierda, GirarDerecha, Acelerar, Frenar};

// Direcciones de marcha

enum class DireccionMovimientoHorizontal {Recta, Izquierda, Derecha};
enum class DireccionMovimientoVertical {Adelante, Atras};

// Posiciones dentro del chasis

enum class PosicionChasisHorizontal {Izquierda, Derecha};
enum class PosicionChasisVertical {Delante, Detras};

// Sentido de rotación de los motores

enum class SentidoRotacion {Indefinido, Directo, Reverso};


#endif
