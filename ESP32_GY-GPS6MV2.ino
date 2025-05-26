#include <TinyGPS++.h>
#include <HardwareSerial.h>

// Crear una instancia del GPS
TinyGPSPlus gps;

// Usa HardwareSerial (puede ser Serial1 en ESP32)
HardwareSerial gpsSerial(1); // UART1

void setup() {
  Serial.begin(115200);        // Monitor serial
  gpsSerial.begin(9600, SERIAL_8N1, 16, 17); // TX=16, RX=17

  Serial.println("Iniciando módulo GPS...");
}

void loop() {
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());

    if (gps.location.isUpdated()) {
      Serial.print("Latitud: ");
      Serial.println(gps.location.lat(), 6);
      Serial.print("Longitud: ");
      Serial.println(gps.location.lng(), 6);
      Serial.print("Altitud: ");
      Serial.print(gps.altitude.meters());
      Serial.println(" m");
      Serial.print("Satélites: ");
      Serial.println(gps.satellites.value());
      Serial.print("Fecha: ");
      if (gps.date.isValid()) {
        Serial.print(gps.date.day());
        Serial.print("/");
        Serial.print(gps.date.month());
        Serial.print("/");
        Serial.println(gps.date.year());
      } else {
        Serial.println("Fecha no válida");
      }
      Serial.print("Hora: ");
      if (gps.time.isValid()) {
        Serial.print(gps.time.hour());
        Serial.print(":");
        Serial.print(gps.time.minute());
        Serial.print(":");
        Serial.println(gps.time.second());
      } else {
        Serial.println("Hora no válida");
      }

      Serial.println("------------------------");
    }
  }
}
