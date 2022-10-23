const uint8_t pinRX = 8;
const uint8_t pinTX = 9;

#include <iarduino_GPS_NMEA.h>
#include <SoftwareSerial.h>
#define THREE_PIN 4

#include <Wire.h>
#include "radSens1v2.h"

iarduino_GPS_NMEA gps;
SoftwareSerial    SerialGPS(pinRX, pinTX);

ClimateGuard_RadSens1v2 radSens(RS_DEFAULT_I2C_ADDRESS);

void setup(){
  // GPS start
  Serial.begin(9600);
  SerialGPS.begin(9600);
  gps.begin(SerialGPS);

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
}



void loop() {
  // GPS data
  gps.read();

  Serial.print(gps.latitude);
  Serial.print(" ");  
  Serial.print(gps.longitude);

  // RadSense data
  radSens.get();

  Serial.print(" ");
  Serial.print(radSens.IntensyDyanmic);
  Serial.print(" ");
  Serial.print(radSens.IntensyStatic);

  Serial.print("\r\n");

  
}