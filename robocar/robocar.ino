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

// Ordenes
#define INDEFINIDA 0
#define PARAR 1 
#define ARRANCAR 2 
#define IR_ADELANTE 3
#define IR_ATRAS 4
#define GIRAR_IZDA 5
#define GIRAR_DCHA 6
#define ACELERAR 7
#define FRENAR 8

//-------------------------------------------------------------------------------------------------------------------------------------

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);    // desactiva el led de prueba que, en caso contrario, quedaría encendido

  pinMode(TRIG_PIN, OUTPUT); // Ultrasonidos
  pinMode(ECHO_PIN, INPUT);
  
//  irrecv.enableIRIn(); // Start the IR receiver
  
  Serial.begin(9600);
  
  // recibir orden (por IR, teclado o cualquier otro medio; método de este módulo; habrá un conjunto de órdenes; para el sensor de IR se necesitará un método que transforme las teclas pulsadas en órdenes)
  // obedecer orden (método de Coche)
  //    1. obtener el estado solicitado aplicando la orden al actual estado solicitado.
  //    2. sincronizar el estado solicitado respecto al estado actual. Provocará tomar acciones:
  //        2.1. Parar motor, girar izquierda, girar derecha, ir hacia adelante, ir hacia atrás (cada una de ellas usará los métodos de Motor para que se lleven a cabo). Cuando se cumplimente una acción se actualizará el estado actual.
  //        2.2. Las acciones que provoquen movimiento (es decir, todas salvo parar) comprobarán que no haya un obstáculo consultando el sensor de obstáculos que controle su existencia en el sentido de la marcha. Como todavía no hay sensor trasero siempre impedirá el movimiento hacia atrás.
  //
  // hay que hacer una prueba, para ello:
  //    1. Probará que se dan las órdenes adecuadas a los motores según las situaciones posibles que se pueden dar.
  //    2. Cuando se ejecute en modo prueba se desactivarán totalmente los motores (accionadores) y los sensores tomarán los valores establecidos por la prueba, es decir, el código deberá tener directivas que se aplicarán en función del modo de ejecución.
}

void loop()
{
  coche.funcionar(recibirOrden());
}

int recibirOrden() {
  // órdenes procedentes del control de infrarrojos
  return INDEFINIDA;
}

// Ultrasonidos
/*
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
//      case KEY_PAUSE:
//        ordenRC = PARAR_ARRANCAR;
        break;
      case KEY_REPEAT:
        ordenRC = IR_ADELANTE;
        break;
    }
    irrecv.resume(); // Receive the next value
  }

  return ordenRC;
}
*/
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
    if (velocidadActual != 0)
      return VARIACION_VELOCIDAD;
    else
      return 0;
  
  return velocidadActual;
}*/

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


