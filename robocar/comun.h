#ifndef comun_h
#define comun_h
 
#include "Arduino.h"

#include "properties.h"

// Ordenes que afectan al estado de la marcha

enum class Orden {Indefinida, Parar, Arrancar, IrAdelante, IrAtras, Recto, GirarIzquierda, GirarDerecha, Acelerar, Frenar};
#ifdef LOG
static String ordenes[] = {"Indefinida", "Parar", "Arrancar", "IrAdelante", "IrAtras", "Recto", "GirarIzquierda", "GirarDerecha", "Acelerar", "Frenar"};
#endif

// Direcciones de marcha

enum class DireccionMovimientoHorizontal {Recta, Izquierda, Derecha};
#ifdef LOG
static String direccionesMovimientoHorizontal[] = {"Recta", "Izquierda", "Derecha"};
#endif

enum class DireccionMovimientoVertical {Adelante, Atras};
#ifdef LOG
static String direccionesMovimientoVertical[] = {"Adelante", "Atras"};
#endif

// Posiciones dentro del chasis

enum class PosicionChasisHorizontal {Izquierda, Centro, Derecha};
#ifdef LOG
static String posicionesChasisHorizontal[] = {"Izquierda", "Centro", "Derecha"};
#endif

enum class PosicionChasisVertical {Delante, Detras};
#ifdef LOG
static String posicionesChasisVertical[] = {"Delante", "Detras"};
#endif

// Sentido de rotación de los motores

enum class SentidoRotacion {Indefinido, Directo, Reverso};
#ifdef LOG
static String sentidosRotacion[] = {"Indefinido", "Directo", "Reverso"};
#endif

#endif
