#ifndef properties_h
#define properties_h
 
#define LOG // TEST activa el modo de pruebas software; para trazas de ejecución poner LOG

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
#define VELOCIDAD_MAXIMA_MOTOR 200

// equilibrado de la velocidad de los motores
#define AJUSTE_MOTOR_TRASERO_IZQUIERDO 60
#define AJUSTE_MOTOR_TRASERO_DERECHO 75
#define AJUSTE_MOTOR_DELANTERO_DERECHO 60
#define AJUSTE_MOTOR_DELANTERO_IZQUIERDO 75

// movimiento

#define INCREMENTO_VELOCIDAD 25
#define VELOCIDAD_MAXIMA 200


#endif
