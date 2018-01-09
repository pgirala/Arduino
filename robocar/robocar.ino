#include <IRremote.h>

int US_PIN = 7;
int MOTOR_PIN = 11;
int RC_PIN = 8;

// Control remoto IR
int ACELERAR = 20655;
int FRENAR = 4335;
int PARAR_ARRANCAR = -24481;

IRrecv irrecv(RC_PIN);

// Control de velocidad
int VELOCIDAD_MAXIMA = 255;
int VARIACION_VELOCIDAD = 5;

// Control de distancia
int DISTANCIA_SEGURIDAD = 20; // centímetros

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);    // desactiva el led de prueba que, en caso contrario, quedaría encendido

  pinMode(US_PIN, INPUT);
  pinMode(MOTOR_PIN, OUTPUT);
  irrecv.enableIRIn(); // Start the receiver
  
  Serial.begin(9600);
  
  while (! Serial);
    Serial.println("Speed 0 to " + VELOCIDAD_MAXIMA);
}

void loop()
{
  ajustarVelocidad(leerVelocidad(), recibirOrdenCR());
}

int recibirOrdenCR()
{
  decode_results results;
  int ordenRC = -1;
  
  if (irrecv.decode(&results))
  {
    ordenRC = results.value;
    irrecv.resume(); // Receive the next value
  }

  return ordenRC;
}

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

void ajustarVelocidad(int velocidadSolicitada, int ordenRC)
{
  static int velocidad = 0;
  
  velocidad = determinarVelocidad(velocidad, velocidadSolicitada, ordenRC);
  analogWrite(MOTOR_PIN, (hayObstaculo() ? 0 : velocidad)); // si hay un obstaculo se para
}

int determinarVelocidad(int velocidadActual, int velocidadSolicitada, int ordenRC)
{
  if (velocidadSolicitada >= 0 && velocidadActual != velocidadSolicitada)
    return velocidadSolicitada;
  
  if (ordenRC == ACELERAR)
    return (velocidadActual + VARIACION_VELOCIDAD >= VELOCIDAD_MAXIMA ? VELOCIDAD_MAXIMA : velocidadActual + VARIACION_VELOCIDAD);
  
  if (ordenRC == FRENAR)
    return (velocidadActual - VARIACION_VELOCIDAD <= 0 ? 0 : velocidadActual - VARIACION_VELOCIDAD);

  if (ordenRC == PARAR_ARRANCAR)
    if (velocidadActual == 0)
      return VARIACION_VELOCIDAD;
    else
      return 0;
  
  return velocidadActual;
}

boolean hayObstaculo() 
{
  long cm = readUltrasonicDistanceSpace(US_PIN);
  return cm >= 0 and cm <= DISTANCIA_SEGURIDAD;
}

long readUltrasonicDistanceSpace(int pin)
{
  return 0.01723 * readUltrasonicDistanceTime(pin); // in centimeters
}

long readUltrasonicDistanceTime(int pin)
{
  pinMode(pin, OUTPUT);  // Clear the trigger
  digitalWrite(pin, LOW);
  delayMicroseconds(2);
  // Sets the pin on HIGH state for 10 micro seconds
  digitalWrite(pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(pin, LOW);
  pinMode(pin, INPUT);
  // Reads the pin, and returns the sound wave travel time in microseconds
  return pulseIn(pin, HIGH);
}
