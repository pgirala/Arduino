#include <IRremote.h>
#include <AFMotor.h>
#include "Coche.h"

// Teclas del control remoto por IR
#define RC_PIN 31
#define KEY_PLUS 0xFFA857
#define KEY_MINUS 0xFFE01F
#define KEY_PAUSE 0xFFC23D
#define KEY_REPEAT 0xFFFFFFFF

IRrecv irrecv(RC_PIN);

// Coche
Coche coche;

// Control de distancia por ultrasonidos
#define ECHO_PIN 33
#define TRIG_PIN 35
#define MAX_DISTANCE_POSSIBLE 1000 // sets maximum useable sensor measuring distance to 1000cm
#define COLL_DIST 20 // sets distance at which the Obstacle avoiding Robot stops and reverses to 10cm
#define TURN_DIST COLL_DIST+10 // sets distance at which the Obstacle avoiding Robot looks away from object (not reverse) to 20cm (10+10)

// Motor
#define MAX_SPEED 120  // sets speed of DC traction motors to 120/256 or about 47% of full speed - to reduce power draining.
#define MOTORS_CALIBRATION_OFFSET 3 // this sets offset to allow for differences between the DC motors
#define VARIACION_VELOCIDAD 5

// Ordenes
#define IR_ADELANTE 0
#define IR_ATRAS 1
#define PARAR_ARRANCAR 2 // para si está en funcionamiento o arranca si está parado
#define GIRAR_IZDA 3
#define GIRAR_DCHA 4
#define ACELERAR 5
#define FRENAR 6

AF_DCMotor leftRearMotor(1, MOTOR34_1KHZ); // create motor #1 using M1 output on Motor Drive Shield, set to 1kHz PWM frequency
AF_DCMotor rightRearMotor(2, MOTOR34_1KHZ); // create motor #2 using M2 output on Motor Drive Shield, set to 1kHz PWM frequency
AF_DCMotor rightFrontMotor(3, MOTOR34_1KHZ); // create motor #3 using M3 output on Motor Drive Shield, set to 1kHz PWM frequency
AF_DCMotor leftFrontMotor(4, MOTOR34_1KHZ); // create motor #4 using M4 output on Motor Drive Shield, set to 1kHz PWM frequency

int ordenActiva;
int velocidadActiva;

//-------------------------------------------------------------------------------------------------------------------------------------

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);    // desactiva el led de prueba que, en caso contrario, quedaría encendido

  pinMode(TRIG_PIN, OUTPUT); // Ultrasonidos
  pinMode(ECHO_PIN, INPUT);
  
  irrecv.enableIRIn(); // Start the IR receiver
  
  Serial.begin(9600);
  
  while (! Serial);
    Serial.println("Speed 0 to 255");

  // inicia los motores
  ordenActiva = IR_ADELANTE;
  velocidadActiva = 0;
  moveForward(); // parado con tendencia a moverse hacia adelante
}

void loop()
{
  ajustarVelocidad(leerVelocidad(), recibirOrdenCR());
}

//-------------------------------------------------------------------------------------------------------------------------------------

// Puerto serie

int leerVelocidad()
{
  if (Serial.available()) // se ha suministrado una nueva velocidad
  {
    int nuevaVelocidad = Serial.parseInt();

    if (nuevaVelocidad >= 0 && nuevaVelocidad <= 255) 
      return nuevaVelocidad;
  }  
  return -1;
}

//-------------------------------------------------------------------------------------------------------------------------------------

// Ultrasonidos

int recibirOrdenCR()
{
  decode_results results;
  
  int ordenRC = IR_ADELANTE;
  
  if (irrecv.decode(&results))
  {
    int valorDevuelto = results.value;
    
    switch (valorDevuelto)
    {
      case KEY_PLUS:
        ordenRC = ACELERAR;
        break;
      case KEY_MINUS:
        ordenRC = FRENAR;
        break;
      case KEY_PAUSE:
        ordenRC = PARAR_ARRANCAR;
        break;
      case KEY_REPEAT:
        ordenRC = IR_ADELANTE;
        break;
    }
    irrecv.resume(); // Receive the next value
  }

  return ordenRC;
}

//-------------------------------------------------------------------------------------------------------------------------------------

boolean hayObstaculo() 
{
  long cm = ping(TRIG_PIN, ECHO_PIN);
  return cm >= 0 and cm <= COLL_DIST;
}

//-------------------------------------------------------------------------------------------------------------------------------------

int ping(int TriggerPin, int EchoPin) {
   long duration, distanceCm;
   
   digitalWrite(TriggerPin, LOW);  //para generar un pulso limpio ponemos a LOW 4us
   delayMicroseconds(4);
   digitalWrite(TriggerPin, HIGH);  //generamos Trigger (disparo) de 10us
   delayMicroseconds(10);
   digitalWrite(TriggerPin, LOW);
   
   duration = pulseIn(EchoPin, HIGH);  //medimos el tiempo entre pulsos, en microsegundos
   
   distanceCm = duration * 10 / 292/ 2;   //convertimos a distancia, en cm
   return distanceCm;
}

//-------------------------------------------------------------------------------------------------------------------------------------

// Motores

void ajustarVelocidad(int velocidadSolicitada, int ordenRC)
{
  static int velocidad = 0;
  velocidad = (hayObstaculo() ? 0 : determinarVelocidad(velocidad, velocidadSolicitada, ordenRC));
Serial.println(velocidad);
  setSpeed(velocidad);
}

//-------------------------------------------------------------------------------------------------------------------------------------

int determinarVelocidad(int velocidadActual, int velocidadSolicitada, int ordenRC)
{
  if (velocidadSolicitada >= 0 && velocidadActual != velocidadSolicitada)
    return velocidadSolicitada;

  if (ordenRC == IR_ADELANTE)
    return velocidadActual;
  
  if (ordenRC == ACELERAR)
    return (velocidadActual + VARIACION_VELOCIDAD >= MAX_SPEED ? MAX_SPEED : velocidadActual + VARIACION_VELOCIDAD);
  
  if (ordenRC == FRENAR)
    return (velocidadActual - VARIACION_VELOCIDAD <= 0 ? 0 : velocidadActual - VARIACION_VELOCIDAD);

  if (ordenRC == PARAR_ARRANCAR)
    if (velocidadActual == 0)
      return VARIACION_VELOCIDAD;
    else
      return 0;
  
  return velocidadActual;
}

//-------------------------------------------------------------------------------------------------------------------------------------

void checkForward() {
  if (ordenActiva == IR_ADELANTE) {
    leftFrontMotor.run(FORWARD);  // ensure motors are going forward
    leftRearMotor.run(FORWARD); 
    rightFrontMotor.run(FORWARD);
    rightRearMotor.run(FORWARD);
  }
}

//-------------------------------------------------------------------------------------------------------------------------------------

void checkBackward() {
  if (ordenActiva == IR_ATRAS) {
    leftFrontMotor.run(BACKWARD);  // ensure motors are going backward
    leftRearMotor.run(BACKWARD);
    rightFrontMotor.run(BACKWARD);
    rightRearMotor.run(BACKWARD);
  }
}

//-------------------------------------------------------------------------------------------------------------------------------------

void moveStop() {
  leftFrontMotor.run(RELEASE);  // stop the motors.
  leftRearMotor.run(RELEASE);  // stop the motors.
  rightFrontMotor.run(RELEASE);
  rightRearMotor.run(RELEASE);
}

//-------------------------------------------------------------------------------------------------------------------------------------

void setSpeed(int speedSet) {
  leftFrontMotor.setSpeed(speedSet);
  leftRearMotor.setSpeed(speedSet);
  rightFrontMotor.setSpeed(speedSet);
  rightRearMotor.setSpeed(speedSet);
}

//-------------------------------------------------------------------------------------------------------------------------------------

void moveForward() {
  ordenActiva = IR_ADELANTE;
  leftFrontMotor.run(FORWARD);      // turn it on going forward
  leftRearMotor.run(FORWARD);      // turn it on going forward
  rightFrontMotor.run(FORWARD);      // turn it on going forward
  rightRearMotor.run(FORWARD);      // turn it on going forward

  for (int speedSet = 0; speedSet < velocidadActiva; speedSet += 2) // slowly bring the speed up to avoid loading down the batteries too quickly
  {
    setSpeed(speedSet);
    delay(5);
  }
}

//-------------------------------------------------------------------------------------------------------------------------------------

void moveBackward() {
  ordenActiva = IR_ATRAS;
  leftFrontMotor.run(BACKWARD);      // turn it on going forward
  leftRearMotor.run(BACKWARD);      // turn it on going forward
  rightFrontMotor.run(BACKWARD);     // turn it on going forward
  rightRearMotor.run(BACKWARD);     // turn it on going forward
  
  for (int speedSet = 0; speedSet < velocidadActiva; speedSet += 2) // slowly bring the speed up to avoid loading down the batteries too quickly
  {
    setSpeed(speedSet);
    delay(5);
  }
}

//-------------------------------------------------------------------------------------------------------------------------------------

void turnRight() {
  ordenActiva = GIRAR_DCHA;
  leftFrontMotor.run(FORWARD);     // turn left motors forward
  leftRearMotor.run(FORWARD); 
  rightFrontMotor.run(BACKWARD);      // turn right motors backward
  rightRearMotor.run(BACKWARD); 
  delay(400); // run motors this way for 400ms
  ordenActiva = IR_ADELANTE;
  leftFrontMotor.run(FORWARD);      // turn it on going forward
  leftRearMotor.run(FORWARD);
  rightFrontMotor.run(FORWARD); 
  rightRearMotor.run(FORWARD);
}

//-------------------------------------------------------------------------------------------------------------------------------------
void turnLeft() {
  ordenActiva = GIRAR_IZDA;
  leftFrontMotor.run(BACKWARD);     // turn left motors backward
  leftRearMotor.run(BACKWARD); 
  rightFrontMotor.run(FORWARD);      // turn right motors forward
  rightRearMotor.run(FORWARD); 
  delay(400); // run motors this way for 400ms
  ordenActiva = IR_ADELANTE;
  leftFrontMotor.run(FORWARD);      // turn it on going forward
  leftRearMotor.run(FORWARD);
  rightFrontMotor.run(FORWARD); 
  rightRearMotor.run(FORWARD);
}

//-------------------------------------------------------------------------------------------------------------------------------------

void lookRight() {
  rightFrontMotor.run(BACKWARD);  // looking right? set right motor backwards for 400ms
  rightRearMotor.run(BACKWARD);
  delay(400);
  rightFrontMotor.run(FORWARD);
  rightRearMotor.run(FORWARD);
}

//-------------------------------------------------------------------------------------------------------------------------------------

void lookLeft() {
  leftFrontMotor.run(BACKWARD);  // looking left? set left motor backwards for 400ms
  leftRearMotor.run(BACKWARD);
  delay(400);
  leftFrontMotor.run(FORWARD);
  leftRearMotor.run(FORWARD);
}

//-------------------------------------------------------------------------------------------------------------------------------------


