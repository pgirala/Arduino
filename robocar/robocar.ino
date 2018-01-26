#include "Coche.h"
#include "ControlRemoto.h"

// coche
Coche coche;

// control remoto
#define CR_PIN 31

ControlRemoto controlRemoto(CR_PIN);

// Control de distancia por ultrasonidos
#define ECHO_PIN 33
#define TRIG_PIN 35
#define MAX_DISTANCE_POSSIBLE 1000 // sets maximum useable sensor measuring distance to 1000cm
#define COLL_DIST 20 // sets distance at which the Obstacle avoiding Robot stops and reverses to 10cm
#define TURN_DIST COLL_DIST+10 // sets distance at which the Obstacle avoiding Robot looks away from object (not reverse) to 20cm (10+10)

//-------------------------------------------------------------------------------------------------------------------------------------

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);    // desactiva el led de prueba que, en caso contrario, quedaría encendido

  pinMode(TRIG_PIN, OUTPUT); // Ultrasonidos
  pinMode(ECHO_PIN, INPUT);
  
  Serial.begin(9600);  
}

void loop()
{
  coche.reaccionar(recibirOrden());
}

Orden recibirOrden() {
  // órdenes procedentes del control de infrarrojos
  return controlRemoto.obtenerOrden();
}

// Ultrasonidos

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
/*
//-------------------------------------------------------------------------------------------------------------------------------------

// Motores
//-------------------------------------------------------------------------------------------------------------------------------------
/*
void checkForward() {
  leftFrontMotor.run(FORWARD);  // ensure motors are going forward
  leftRearMotor.run(FORWARD); 
  rightFrontMotor.run(FORWARD);
  rightRearMotor.run(FORWARD);
}

//-------------------------------------------------------------------------------------------------------------------------------------

void checkBackward() {
  leftFrontMotor.run(BACKWARD);  // ensure motors are going backward
  leftRearMotor.run(BACKWARD);
  rightFrontMotor.run(BACKWARD);
  rightRearMotor.run(BACKWARD);
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
*/
//-------------------------------------------------------------------------------------------------------------------------------------
/*
void moveForward() {
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
*/
//-------------------------------------------------------------------------------------------------------------------------------------
/*
void moveBackward() {
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
*/
//-------------------------------------------------------------------------------------------------------------------------------------
/*
void turnRight() {
  leftFrontMotor.run(FORWARD);     // turn left motors forward
  leftRearMotor.run(FORWARD); 
  rightFrontMotor.run(BACKWARD);      // turn right motors backward
  rightRearMotor.run(BACKWARD); 
  delay(400); // run motors this way for 400ms
  leftFrontMotor.run(FORWARD);      // turn it on going forward
  leftRearMotor.run(FORWARD);
  rightFrontMotor.run(FORWARD); 
  rightRearMotor.run(FORWARD);
}

//-------------------------------------------------------------------------------------------------------------------------------------
void turnLeft() {
  leftFrontMotor.run(BACKWARD);     // turn left motors backward
  leftRearMotor.run(BACKWARD); 
  rightFrontMotor.run(FORWARD);      // turn right motors forward
  rightRearMotor.run(FORWARD); 
  delay(400); // run motors this way for 400ms
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
*/
//-------------------------------------------------------------------------------------------------------------------------------------


