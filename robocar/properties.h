#ifndef properties_h
#define properties_h
 
#define TEST // activa el log

// control remoto

#define CR_PIN 31

// ultrasonidos

#define NUMERO_SENSORES_US 2
#define ECHO_PIN_DELANTERO 33
#define TRIGGER_PIN_DELANTERO 35
#define ECHO_PIN_TRASERO 37
#define TRIGGER_PIN_TRASERO 39
#define DISTANCIA_SEGURIDAD 20 // centímetros

// motores

#define NUMERO_MOTORES 4
#define TIEMPO_PROTECCION_REVERSION 100 // milisegundos
#define VELOCIDAD_MAXIMA_MOTOR 250

// movimiento

#define INCREMENTO_VELOCIDAD 25
#define VELOCIDAD_MAXIMA 200


#endif
