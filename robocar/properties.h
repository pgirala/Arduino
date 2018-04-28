#ifndef properties_h
#define properties_h
 
//#define TEST // TEST activa el modo de pruebas software; para trazas de ejecución poner LOG; para trazas muy detalladas LOG_EXTRA (además de LOG)
#define LOG
//#define LOG_EXTRA

// control remoto

#define CR_PIN 31

// ultrasonidos

#define NUMERO_SENSORES_US 6
#define ECHO_PIN_DELANTERO_C 33
#define TRIGGER_PIN_DELANTERO_C 35
#define CHOQUE_PIN_DELANTERO_C 51
#define ECHO_PIN_DELANTERO_I 41
#define TRIGGER_PIN_DELANTERO_I 43
#define CHOQUE_PIN_DELANTERO_I 53
#define ECHO_PIN_DELANTERO_D 45
#define TRIGGER_PIN_DELANTERO_D 47
#define CHOQUE_PIN_DELANTERO_D 49
#define ECHO_PIN_TRASERO_C 37
#define TRIGGER_PIN_TRASERO_C 39
#define CHOQUE_PIN_TRASERO_C 24
#define ECHO_PIN_TRASERO_I 27
#define TRIGGER_PIN_TRASERO_I 29
#define CHOQUE_PIN_TRASERO_I 22
#define ECHO_PIN_TRASERO_D 23
#define TRIGGER_PIN_TRASERO_D 25
#define CHOQUE_PIN_TRASERO_D 52

#define ALCANCE_MAXIMO 500 // centímetros
#define DISTANCIA_PERIMETRO_SEGURIDAD 25 // centímetros
#define DISTANCIA_MINIMA_ESCAPE 5 // distancia mínima para permitir el escape por esa vía

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

// sensores de movimiento (los PIN se corresponden con las interrupciones INT2, INT3, INT4, INT5 de MEGA 2560 (21, 20, 19, 18)

#define NUMERO_SENSORES_MOVIMIENTO 4
#define SM_PIN_TRASERO_I 21
#define SM_PIN_TRASERO_D 20
#define SM_PIN_DELANTERO_D 19
#define SM_PIN_DELANTERO_I 18

#endif
