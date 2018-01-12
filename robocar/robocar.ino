#include <IRremote.h>

// Control remoto IR
const int RC_PIN = 31;
IRrecv irrecv(RC_PIN);
const int KEY_PLUS = 0xFFA857;
const int KEY_MINUS = 0xFFE01F;
const int KEY_PAUSE = 0xFFC23D;
const int KEY_REPEAT = 0xFFFFFFFF;

// Control de velocidad
const int VELOCIDAD_MAXIMA = 255;
const int VARIACION_VELOCIDAD = 5;

// Control de distancia
const int ECHO_PIN= 33;
const int TRIGGER_PIN = 35;
const int DISTANCIA_SEGURIDAD = 20; // centímetros

// Motor
const int SEGUIR = 0;
const int ACELERAR = 1;
const int FRENAR = 2;
const int PARAR_ARRANCAR = 3;
const int MOTOR_PIN = 4;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);    // desactiva el led de prueba que, en caso contrario, quedaría encendido

  pinMode(TRIGGER_PIN, OUTPUT); // Ultrasonidos
  pinMode(ECHO_PIN, INPUT);
  
  pinMode(MOTOR_PIN, OUTPUT); // Motor
  
  irrecv.enableIRIn(); // Start the IR receiver
  
  Serial.begin(9600);
  
  while (! Serial);
    Serial.println("Speed 0 to 255");
}

void loop()
{
  ajustarVelocidad(leerVelocidad(), recibirOrdenCR());
}

int recibirOrdenCR()
{
  decode_results results;
  
  int ordenRC = SEGUIR;
  
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
        ordenRC = SEGUIR;
        break;
    }
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
  velocidad = (hayObstaculo() ? 0 : determinarVelocidad(velocidad, velocidadSolicitada, ordenRC));
Serial.println(velocidad);
  analogWrite(MOTOR_PIN, velocidad); // si hay un obstaculo se para
}

int determinarVelocidad(int velocidadActual, int velocidadSolicitada, int ordenRC)
{
  if (velocidadSolicitada >= 0 && velocidadActual != velocidadSolicitada)
    return velocidadSolicitada;

  if (ordenRC == SEGUIR)
    return velocidadActual;
  
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

// Ultrasonidos

boolean hayObstaculo() 
{
  long cm = ping(TRIGGER_PIN, ECHO_PIN);
  return cm >= 0 and cm <= DISTANCIA_SEGURIDAD;
}

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
