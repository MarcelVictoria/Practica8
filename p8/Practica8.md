# PRACTICA 8 : Buses de comunicación IV (uart) 
<div align=right>
Victòria Blanco Bosch 
<div>
<div align=right>
Marcel Farelo de la Orden
<div> 
<div align="justify">

***
El objetivo de la practica es **comprender el funcionamiento de la comunicacion serie asincrona usart**.
Esta comunicacion es muy utilizada de hecho en todas las practicas las estamos usando cuando nos referimos a la impresora serie Serial.println("").
Este tipo de protocolo dispone de muchos perifericos y por tanto la comprension de
su funcionamiento es basica para cualquier ingeniero electronico.
En la practica de hoy veremos dos ejemplos de uso. La conexion a un modulo GPS de
donde visualizaremos la posicion , velocidad y hora actual y una conexion a internet
mediante un modem GSM/ GPRS.

## Introducción teórica
La nomenclatura **uart (Universal Asyncronous Receiver Transmiter)** se refiere a modulos dentro de microprocesador que tienen la capacidad de realizar
comunicacion asincrona full duplex **emision y recepcion simultanea**. Habremos observado que hay modulos que indican tambien **usart** en este caso el modulo
tambien tene la posibilidad de realizar comunicacion sincrona (Universal Syncronous Asyncronous Receiver Transmiter). Que son las comunicaciones que hemos visto en las practicas anteriores donde se utiliza una señal de clock para sincronizar.

***

## uart en ESP32


![](https://circuits4you.com/wp-content/uploads/2018/12/ESP32-Pinout.jpg)

Hay tres puertos serie del ESP32 conocidos como U0UXD, U1UXD y U2UXD todo el trabajo en 3.3V Nivel TTL . Hay tres interfaces seriales compatibles con hardware en el ESP32 conocidas como UART0, UART1 y UART2. Como todos los periféricos, los pines de los UART se pueden asignar lógicamente a cualquiera de los pines disponibles en el ESP32. Sin embargo, los UART también pueden tener acceso directo, lo que mejora marginalmente el rendimiento. La tabla de asignación de pines para esta asistencia de hardware es la siguiente.

|UART| RX IO |	TX IO|	CTS|	RTS|
|--|--|--|--|--|
|UART0|	GPIO3|	GPIO1|	N / A|	N / A|
|UART1|	GPIO9|	GPIO10|	GPIO6|	GPIO11|
|UART2|	GPIO16|	GPIO17|	GPIO8|	GPIO7|


## Material
- ESP32

  
## Objetivo
Realizar un bucle de comunicacion de forma que los datos que se
manden por el terminal rxd0 se redirijan a la uart 2 txd2 ( que debe estar conectado a rxd2 ) y la recepcion de los datos de la uart2 se reenvien de nuevo a la salida txd0
para que aparezcan en la pantalla del terminal




## Programa



### Librerias

```cpp
#include <Arduino.h>
#include <HardwareSerial.h>
```

- Se asignan valores a los pines RXD0, TXD0, RXD2 y TXD2.

```cpp

#define RXD0 3
#define TXD0 1
#define RXD2 16
#define TXD2 17
```

- Creamos las instancias de HardwareSerial para los puertos UART
```cpp
HardwareSerial SerialUART0(0); // Puerto UART 0
HardwareSerial SerialUART2(2); // Puerto UART 2
```
### Setup

- Dentro de la función **setup( )**, las tres líneas establecen la velocidad para la comunicación serie y configuran los pines RXD0, TXD0, RXD2 y TXD2 para la comunicación serial utilizando las funciones **Serial.begin( )**, **serialUART2.begin( )** .
```cpp
void setup() {
  // Inicializar los puertos UART
  Serial.begin(115200); // Puerto UART 0
  SerialUART2.begin(115200, SERIAL_8E1, RXD2, TXD2); // Puerto UART 2
}
```
### Loop

Dentro de la función **loop()**, las dos declaraciones *if* verifican si hay datos disponibles en la comunicación serial. En el primer if se leerá si el canal "Serial" está disponible, si lo está se escribirán sus datos en el "SerialUART2". En el segundo if,  veremos si el "SerialUART2" está disponible, y si lo está, escribiremos sus datos en el "Serial" y haremos un "printf("Datos")" para ver los datos por el terminal.
```cpp
void loop() {
  // Leer datos del puerto UART 0 y enviarlos al puerto UART 2
  if (Serial.available()) {
    char data = Serial.read();
    SerialUART2.write(data);
  }
  
  // Leer datos del puerto UART 2 y enviarlos al puerto UART 0
  if (SerialUART2.available()) {
    char data = SerialUART2.read();
    Serial.write(data);
    serial.printf("datos");
  }
}
```


## Código entero
```cpp
#include <Arduino.h>
#include <HardwareSerial.h>

// Definir los pines UART a utilizar
#define RXD0 3
#define TXD0 1
#define RXD2 16
#define TXD2 17

// Crear instancias de HardwareSerial para los puertos UART
HardwareSerial SerialUART0(0); // Puerto UART 0
HardwareSerial SerialUART2(2); // Puerto UART 2

void setup() {
  // Inicializar los puertos UART
  Serial.begin(115200); // Puerto UART 0
  SerialUART2.begin(115200, SERIAL_8E1, RXD2, TXD2); // Puerto UART 2
}

void loop() {
  // Leer datos del puerto UART 0 y enviarlos al puerto UART 2
  if (Serial.available()) {
    char data = Serial.read();
    SerialUART2.write(data);
  }
  
  // Leer datos del puerto UART 2 y enviarlos al puerto UART 0
  if (SerialUART2.available()) {
    char data = SerialUART2.read();
    Serial.write(data);
  }
}