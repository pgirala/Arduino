Robocar. Coche robótico.

Proyecto en el que está basado: http://sribasu.com/programming-tutorials/creating-an-obstacle-avoiding-robot-with-arduino-adafruit-motor-shield-v1-and-ultra-sonic-sensor.html

Herramientas necesarias:
- Arduino IDE en local.
- Gestor de configuraciones: Github.
- Modelo lógico: versión online de UMLet (http://www.umlet.com/umletino/umletino.html) para diagramas UML.
- Modelo físico: fritzing.org

Componentes necesarios:
- Arduino Mega 2560 (o compatible). Dos, una instalada en el coche y otra conectada al IDE para desarrollar y hacer pruebas.
- Motor shield para cuatro motores DC https://diotronic.com/producte.aspx?nom=arduino-motor-servo-stepper&referencia=27406 (clon del original Adafruit v1)
- Chasis YIKESHU 4WD Smart Motor Robot.
- Sensores ultrasonidos HC-SR04. 4 (3 frontales y 1 trasero).
- Sensor de infrarrojos Velleman IO 1838 37.9 khz y mando.
- Cables (varios tamaños y conectores: macho-macho, macho-hembra).
- Pequeñas placas de pruebas de 55 pines (Velleman Hobby set of mini breadbroads).
- Caja de baterias keesin 3.7 V 18650 con interruptor y tapa. Se necesitan 2.
- Baterías de litio recargables EBL 4 unidades 18650 B2300mAh 3.7V de baja autodescarga.
- Cargador de baterías para cargar 1-4 baterías de litio 18650 EBL 996 
- Opcional: lápiz de pintura conductiva "BARE conductive electric paint" de 10 ml (evita soldaduras)

Próximas acciones:

- Reorganizar el código:
	- Test en su propia carpeta.

- Documentación del proyecto:
	- Modelos en su propia carpeta:
		- Carpeta con el modelo lógico:
			- Completar el diagrama de secuencia.
		- Carpeta con el modelo físico:
			- Conexiones con alguna herramienta que permita realizar diagramas físicos.

- Evolución del proyecto:
	- Mejorar el algoritmo para evitar obstáculos:
		- Permitir, en casos extremos, el avance hacia adelante (cuando no sea posible girar en ningún lado, es decir, el giro tiene preferencia).
		- Ante imposibilidad de avance, ir hacia atrás y encontrar otra vía.
	- Incorporar fotointerruptores (uno por motor) y giróscopos para permitir que el coche conozca su ubicación y por dónde se ha movido. Posibles utilidades:
		- Calibración automática de motores.
		- Evitar obstáculos y retornar a la dirección que se llevaba.
		- Volver al punto inicial (esto será util en el futuro para recargar baterías).
	- Incorporar bocina.
	- Incorporar un LCD frontal ("expresiones faciales").
	- Detección de nivel bajo de baterías.
	- Recarga automática de baterías (combinado con la detección de nivel bajo de baterías y retorno al punto de recarga).
	- Incorporar algunas luces de posición (para verlo si va a oscuras).
	- Captación de imágenes.
	- Detección de órdenes analizando la voz.
		