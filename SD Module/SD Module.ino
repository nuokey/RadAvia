#include <SPI.h>
#include <SD.h>

File file;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // pinMode(10, OUTPUT);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  if (SD.begin(10)) {
    Serial.println("Done");

    file = SD.open("/test.txt", FILE_WRITE);
    Serial.println(file.print("Hello again"));
    file.close();
  }
  else {
    Serial.println("F***");
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
