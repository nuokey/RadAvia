const uint8_t pinRX = 8;
const uint8_t pinTX = 9;

#include <iarduino_GPS_NMEA.h>
#include <SoftwareSerial.h>
#define THREE_PIN 4

iarduino_GPS_NMEA gps;
SoftwareSerial    SerialGPS(pinRX, pinTX);

void setup(){
     Serial.begin(9600);
     SerialGPS.begin(9600);
     gps.begin(SerialGPS);

     pinMode(THREE_PIN, OUTPUT);
     analogWrite(THREE_PIN, 170);
}                  

void loop() {
  gps.read();

  Serial.print(gps.latitude);
  Serial.print(" ");  
  Serial.print(gps.longitude);
  Serial.print(" ");  
  Serial.print(gps.Hours);
  Serial.print(" ");
  Serial.print(gps.minutes);
  Serial.print(" ");
  Serial.print(gps.seconds);
  Serial.print("\r\n");
}