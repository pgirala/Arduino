//#include <IRremote.h>

// Control remoto IR
const int RC_PIN = 8;
const int ACELERAR = 20655;
const int FRENAR = 4335;
const int PARAR_ARRANCAR = -24481;

//IRrecv irrecv(RC_PIN);

// Control de velocidad
const int VELOCIDAD_MAXIMA = 255;
const int VARIACION_VELOCIDAD = 5;

// Control de distancia
const int ECHO_PIN= 5;
const int TRIGGER_PIN = 6;
const int DISTANCIA_SEGURIDAD = 20; // centímetros

// Motor
const int MOTOR_PIN = 11;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);    // desactiva el led de prueba que, en caso contrario, quedaría encendido

  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(MOTOR_PIN, OUTPUT);
  
//  irrecv.enableIRIn(); // Start the receiver
  
  Serial.begin(9600);
  
  while (! Serial);
    Serial.println("Speed 0 to 255");
}

void loop()
{
  Serial.println(hayObstaculo());
  ajustarVelocidad(leerVelocidad(), recibirOrdenCR());
}

int recibirOrdenCR()
{
  return FRENAR;
/*  decode_results results;
  int ordenRC = -1;
  
  if (irrecv.decode(&results))
  {
    ordenRC = results.value;
    irrecv.resume(); // Receive the next value
  }

  return ordenRC;*/
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
