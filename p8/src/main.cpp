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