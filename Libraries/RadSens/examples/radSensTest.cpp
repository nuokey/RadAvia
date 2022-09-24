#include <Arduino.h>
#include <Wire.h>
#include "radSens1v2.h"


ClimateGuard_RadSens1v2 radSens(RS_DEFAULT_I2C_ADDRESS); /*Constructor of the class ClimateGuard_RadSens1v2,
                                                           sets the address parameter of I2C sensor.
                                                           Default address: 0x66.*/


void setup() 
{
  Serial.begin(115200);  

  radSens.radSens_init(); /*Initialization function and sensor connection. 
                            Returns false if the sensor is not connected to the I2C bus.*/
  
  uint8_t sensorChipId = radSens.getChipId(); /*Returns chip id, default value: 0x7D.*/

  Serial.print("Chip id: 0x");
  Serial.println(sensorChipId, HEX);

  uint8_t firmWareVer = radSens.getFirmwareVersion(); /*Returns firmware version.*/

  Serial.print("Firmware version: ");
  Serial.println(firmWareVer);

  Serial.println("-------------------------------------");
  Serial.println("Set Sensitivity example:\n");

  uint8_t sensitivity = radSens.getSensitivity(); /*Rerutns the value coefficient used for calculating
                                                    the radiation intensity or 0 if sensor isn't connected.*/

  Serial.print("\t getSensitivity(): "); Serial.println(sensitivity);
  Serial.println("\t setSensitivity(55)... ");

  radSens.setSensitivity(55); /*Sets the value coefficient used for calculating
                                the radiation intensity*/

  sensitivity = radSens.getSensitivity();
  Serial.print("\t getSensitivity(): "); Serial.println(sensitivity);
  Serial.println("\t setSensitivity(105)... ");

  radSens.setSensitivity(105);

  Serial.print("\t getSensitivity(): "); Serial.println(radSens.getSensitivity());

  bool hvGeneratorState = radSens.getHVGeneratorState(); /*Returns state of high-voltage voltage Converter.
                                                           If return true -> on
                                                           If return false -> off or sensor isn't conneted*/

  Serial.print("\n\t HV generator state: "); Serial.println(hvGeneratorState);
  Serial.println("\t setHVGeneratorState(false)... ");

  radSens.setHVGeneratorState(false); /*Set state of high-voltage voltage Converter.
                                        if setHVGeneratorState(true) -> turn on HV generator
                                        if setHVGeneratorState(false) -> turn off HV generator*/
  
  hvGeneratorState = radSens.getHVGeneratorState();
  Serial.print("\t HV generator state: "); Serial.println(hvGeneratorState);
  Serial.println("\t setHVGeneratorState(true)... ");

  radSens.setHVGeneratorState(true);

  hvGeneratorState = radSens.getHVGeneratorState();
  Serial.print("\t HV generator state: "); Serial.print(hvGeneratorState);
  Serial.println("\n-------------------------------------");
}

void loop(){
  Serial.print("Rad intensy dyanmic: ");

  Serial.println(radSens.getRadIntensyDyanmic()); /*Returns radiation intensity (dynamic period T < 123 sec).*/

  Serial.print("Rad intensy static: ");
  
  Serial.println(radSens.getRadIntensyStatic()); /*Returns radiation intensity (static period T = 500 sec).*/

  Serial.print("Number of pulses: ");

  Serial.println(radSens.getNumberOfPulses()); /*Returns the accumulated number of pulses registered by the 
                                                 module since the last I2C data reading.*/

  delay(2000);
}
