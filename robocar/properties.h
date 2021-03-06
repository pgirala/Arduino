#ifndef properties_h
#define properties_h
 
//#define TEST // TEST activa el modo de pruebas software; para trazas de ejecución poner LOG; para trazas muy detalladas LOG_EXTRA (además de LOG)
//#define LOG
//#define LOG_EXTRA

// control remoto

#define CR_PIN 53

// servo
#define SERVO_MOTOR_PIN 9 // asocia el servo al pin 9 (SERVO_2 en el Motor Drive Shield)
#define PASO_SERVO_MOTOR 10

// ultrasonidos

#define NUMERO_SENSORES_US 6

#define ECHO_PIN_DELANTERO_C 46
#define TRIGGER_PIN_DELANTERO_C 47
#define CHOQUE_PIN_DELANTERO_C 22

#define ECHO_PIN_DELANTERO_I 48
#define TRIGGER_PIN_DELANTERO_I 49
#define CHOQUE_PIN_DELANTERO_I 23

#define ECHO_PIN_DELANTERO_D 50
#define TRIGGER_PIN_DELANTERO_D 51
#define CHOQUE_PIN_DELANTERO_D 25

#define ECHO_PIN_TRASERO_C 40
#define TRIGGER_PIN_TRASERO_C 41
#define CHOQUE_PIN_TRASERO_C -1 // desactivado

#define ECHO_PIN_TRASERO_I 38
#define TRIGGER_PIN_TRASERO_I 39
#define CHOQUE_PIN_TRASERO_I 27 

#define ECHO_PIN_TRASERO_D 36 
#define TRIGGER_PIN_TRASERO_D 37
#define CHOQUE_PIN_TRASERO_D 24 

#define ALCANCE_MAXIMO 500 // centímetros
#define DISTANCIA_PERIMETRO_SEGURIDAD 25 // centímetros
#define DISTANCIA_MINIMA_ESCAPE 5 // distancia mínima para permitir el escape por esa vía

// motores

#define NUMERO_MOTORES 4
#define TIEMPO_PROTECCION_REVERSION 100 // milisegundos
#define VELOCIDAD_MAXIMA_MOTOR 200
#define PERIODO_SINCRONIZACION 1000 // milisegundos

// movimiento

#define INCREMENTO_VELOCIDAD 10
#define VELOCIDAD_MAXIMA 150

// sensores de movimiento (los PIN se corresponden con las interrupciones INT2, INT3, INT4, INT5 de MEGA 2560 (21, 20, 19, 18)

#define NUMERO_SENSORES_MOVIMIENTO 4
#define SM_PIN_TRASERO_I A14  // evita el uso del pin 20 necesario para el LIDAR
#define SM_PIN_TRASERO_D A15  // idem para el 21
#define SM_PIN_DELANTERO_D 19
#define SM_PIN_DELANTERO_I 18
#define RADIO_RUEDA 5 // TODO medirlo
#define RADIOS_RUEDA 20
#define NUMERO_CUENTAS_MOVIMIENTO 2
#define CUENTA_SINCRONIZACION 0
#define CUENTA_DISTANCIA 1

#endif
