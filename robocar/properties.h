#ifndef properties_h
#define properties_h
 
#define TEST // TEST activa el modo de pruebas software; para trazas de ejecución poner LOG
//#define LOG

// control remoto

#define CR_PIN 31

// ultrasonidos

#define NUMERO_SENSORES_US 4
#define ECHO_PIN_DELANTERO_C 33
#define TRIGGER_PIN_DELANTERO_C 35
#define ECHO_PIN_DELANTERO_I 41
#define TRIGGER_PIN_DELANTERO_I 43
#define ECHO_PIN_DELANTERO_D 45
#define TRIGGER_PIN_DELANTERO_D 47
#define ECHO_PIN_TRASERO 37
#define TRIGGER_PIN_TRASERO 39
#define DISTANCIA_SEGURIDAD 20 // centímetros

// motores

#define NUMERO_MOTORES 4
#define TIEMPO_PROTECCION_REVERSION 100 // milisegundos
#define VELOCIDAD_MAXIMA_MOTOR 200

// equilibrado de la velocidad de los motores
#define AJUSTE_MOTOR_TRASERO_IZQUIERDO 80
#define AJUSTE_MOTOR_TRASERO_DERECHO 85
#define AJUSTE_MOTOR_DELANTERO_DERECHO 90
#define AJUSTE_MOTOR_DELANTERO_IZQUIERDO 95

// movimiento

#define INCREMENTO_VELOCIDAD 10
#define VELOCIDAD_MAXIMA 150



#endif
