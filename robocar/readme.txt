Robocar. Coche robótico.

Herramientas necesarias:
- Arduino IDE en local.
- Github.
- Versión online de UMLet (http://www.umlet.com/umletino/umletino.html) para diagramas UML.
- Versión ¿? para hacer diagramas físicos.

Componentes necesarios:
- Arduino Mega 2560. Dos, una instalada en el coche y otra conectada al IDE para desarrollar y hacer pruebas.
- Motor shield ¿?.
- Chasis ¿?.
- Sensores ultrasonidos ¿?.
- Sensor de infrarrojos ¿?.
- Resistencias.
- Cables.
- Pequeñas placas de pruebas.

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
	- Incorporar un acelerómetro, giroscopio y magnetómetro para permitir que el coche conozca su ubicación y por dónde se ha movido. Posibles utilidades:
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
		