int RXPin = 2;                          // Указываем вывод подключения RX  
int TXPin = 3;                          // Указываем вывод подключения TX
 
int GPSBaud = 9600;

#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#define THREE_PIN 4

#include <Wire.h>
#include "radSens1v2.h"

#include <SPI.h>
#include <SD.h>

File file;

TinyGPSPlus gps;                        // Создание объекта 
SoftwareSerial gpsSerial(RXPin, TXPin);

ClimateGuard_RadSens1v2 radSens(RS_DEFAULT_I2C_ADDRESS);

void setup(){
  // GPS start
  Serial.begin(9600);             // Запускаем последовательный порт с ПК на скорости 9600
  gpsSerial.begin(GPSBaud);

  pinMode(THREE_PIN, OUTPUT);
  analogWrite(THREE_PIN, 170);
  // RadSens start
  radSens.radSens_init();
  
  uint8_t sensorChipId = radSens.getChipId();



  uint8_t sensitivity = radSens.getSensitivity();

  radSens.setSensitivity(55);

  sensitivity = radSens.getSensitivity();

  radSens.setSensitivity(105);

  radSens.setHVGeneratorState(true);
  if (SD.begin(7)) {
    Serial.println("Done");

    file = SD.open("/test.txt", FILE_WRITE);
    Serial.println(file.print("Hello again"));
    file.close();

    
  }
  else {
    Serial.println("SD-card was not read");
  }
}



void loop() {
  

  while (gpsSerial.available() > 0)
    if (gps.encode(gpsSerial.read()))
      displayInfo();
 
  // Если нет данных в течении 5000 миллисекунд, пишем сообщение об ошибки
  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println("No GPS detected");
    while(true);
  }

  
  // RadSense data
  // radSens.get();

  // Serial.print(" ");
  // Serial.print(radSens.IntensyDyanmic);
  // Serial.print(" ");
  // Serial.print(radSens.IntensyStatic);

  // Serial.print("\r\n");

  // file.print(gps.location.lat(), 6);
  // file.print(" ");
  // file.print(gps.location.lng(), 6);
  // file.print(" ");
  // file.print(radSens.IntensyDyanmic);
  // file.print(" ");
  // file.print(radSens.IntensyStatic);

  // file.print("\r\n");

  // file.close();
  
}

void displayInfo()
{
  // GPS data
  file = SD.open("/data.txt", FILE_WRITE);
  radSens.get();

  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(" ");
    Serial.print(gps.location.lng(), 6);

    file.print(gps.location.lat(), 6);
    file.print(" ");
    file.print(gps.location.lng(), 6);
    file.print(" ");
    file.print(radSens.IntensyDyanmic);
    file.print(" ");
    file.print(radSens.IntensyStatic);

    file.print("\r\n");
  }
  else
  {
    Serial.println("Location: Not Available");
  }
  
  Serial.print(" ");
    Serial.print(radSens.IntensyDyanmic);
    Serial.print(" ");
    Serial.print(radSens.IntensyStatic);

  delay(1000);
  Serial.print("\r\n");
  file.close();
}